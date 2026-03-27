#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    typedef vector<vector<char>> Board;

public:
    void solveSudoku(Board& board) {



    }

private:

    static bool isSolved(const Board& board) {
        for (int index = 0; index < 9; index++) {
            if (!isSquareSolved(board, index) || !isRowSolved(board, index) || !isColumnSolved(board, index)) {
                return false;
            }
        }
        return true;
    }

    static bool isSquareSolved(const Board& board, int squareNumber) {
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

        return charsIncludedInSelection(board, rows, columns).size() == 9;
    }

    static bool isRowSolved(const Board& board, int rowNumber) {
        return charsIncludedInSelection(board, { rowNumber }, { 0, 1, 2, 3, 4, 5, 6, 7, 8 }).size() == 9;
    }

    static bool isColumnSolved(const Board& board, int columnNumber) {
        return charsIncludedInSelection(board, { 0, 1, 2, 3, 4, 5, 6, 7, 8 }, { columnNumber }).size() == 9;
    }

    static unordered_set<char> charsIncludedInSelection(const Board& board, const vector<int>& rows, const vector<int>& columns) {
        unordered_set<char> included;
        for (auto row : rows) {
            for (auto col : columns) {
                if (board[row][col] == '.') continue;
                included.insert(board[row][col]);
            }
        }
        return included;
    }
};