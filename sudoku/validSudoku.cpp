#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    typedef vector<vector<char>> Board;
    bool isValidSudoku(Board& board) {
        return isSolved(board);
    }

    private:

    static unordered_set<char> getAvailableOptions(const Board& board, const int& row, const int& col) {
        unordered_set<char> itemsLeft = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };

        unordered_set<char> itemsUsed = charsInSquare(board, posToSquare(row, col));
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        if (itemsLeft.empty() || itemsLeft.size() == 1) return itemsLeft;

        itemsUsed = charsInRow(board, row);
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        if (itemsLeft.empty() || itemsLeft.size() == 1) return itemsLeft;

        itemsUsed = charsInColumn(board, col);
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        return itemsLeft;
    }

    static int posToSquare(const int& row, const int& col) {
        const vector<vector<int>> rowToColMap = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 } };
        return rowToColMap[row / 3][col / 3];
    }

    static bool isSolved(const Board& board) {
        for (int index = 0; index < 9; index++) {
            if (!isSquareSolved(board, index) || !isRowSolved(board, index) || !isColumnSolved(board, index)) {
                return false;
            }
        }
        return true;
    }

    static bool isSquareSolved(const Board& board, const int squareNumber) {
        return charsInSquare(board, squareNumber).size() == 9;
    }

    static unordered_set<char> charsInSquare(const Board& board, const int squareNumber) {
        vector<int> rows, columns;

        // rows
        switch (squareNumber) {
            case 0:
            case 1:
            case 2:
                rows = { 0, 1, 2 };
                break;
            case 3:
            case 4:
            case 5:
                rows = { 3, 4, 5 };
                break;
            default: // cases for squares 6-8
                rows = { 6, 7, 8 };
        }

        // columns
        switch (squareNumber) {
            case 0:
            case 3:
            case 6:
                columns = { 0, 1, 2 };
                break;
            case 1:
            case 4:
            case 7:
                columns = { 3, 4, 5 };
                break;
            default: // cases for squares 2, 5, 8
                columns = { 6, 7, 8 };
        }

        return charsIncludedInSelection(board, rows, columns);
    }

    static bool isRowSolved(const Board& board, const int& rowNumber) {
        return charsInRow(board, rowNumber).size() == 9;
    }

    static unordered_set<char> charsInRow(const Board& board, const int& rowNumber) {
        return charsIncludedInSelection(board, { rowNumber }, { 0, 1, 2, 3, 4, 5, 6, 7, 8 });
    }

    static bool isColumnSolved(const Board& board, int columnNumber) {
        return charsInColumn(board, columnNumber).size() == 9;
    }

    static unordered_set<char> charsInColumn(const Board& board, const int columnNumber) {
        return charsIncludedInSelection(board, { 0, 1, 2, 3, 4, 5, 6, 7, 8 }, { columnNumber });
    }

    static unordered_set<char> charsIncludedInSelection(const Board& board, const vector<int>& rows, const vector<int>& columns) {
        unordered_set<char> included;
        for (const auto row : rows) {
            for (const auto col : columns) {
                if (board[row][col] == '.') continue;
                included.insert(board[row][col]);
            }
        }
        return included;
    }
};