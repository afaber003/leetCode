#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>

using namespace std;

class Solution {
    typedef vector<vector<char>> Board;

    struct Move {
        int row, column;
        char value;
        Move() { row = -1; column = -1; value = '-'; }
        Move(const char value, const int row, const int column): row(row), column(column), value(value) {}
    };

    struct BoardState {
        Move moveMade;
        unordered_set<char> otherMovesForChangedSquare = {};
        BoardState* prevBoardState = nullptr;
    };

public:
    void solveSudoku(Board& board) {
        auto* currentState = new BoardState();
        bool goingBack = false;
        while (goingBack || !isSolved(board)) {

            // Check for returned item condition
            if (goingBack) {
                if (!currentState->otherMovesForChangedSquare.empty()) {
                    char valToApply = *currentState->otherMovesForChangedSquare.begin();
                    currentState->otherMovesForChangedSquare.erase(valToApply);

                    board[currentState->moveMade.row][currentState->moveMade.column] = valToApply;
                    currentState->moveMade.value = valToApply;

                    // Copy new board and move on to next move
                    auto* nextBoardState = new BoardState();
                    nextBoardState->prevBoardState = currentState;
                    currentState = nextBoardState;
                    goingBack = false;
                } else {
                    auto* boardToRemove = currentState;
                    currentState = currentState->prevBoardState;
                    board[boardToRemove->moveMade.row][boardToRemove->moveMade.column] = '.';
                    delete boardToRemove;
                }
                continue;
            }

            auto optionsForBoard = getAllAvailableOptions(board);

            Move* easyMove = checkForEasyMove(optionsForBoard);
            if (easyMove != nullptr) { // Easy way
                currentState->moveMade = *easyMove;
                board[easyMove->row][easyMove->column] = easyMove->value;
                delete easyMove;

                // Copy new board and move on to next move
                auto* nextBoardState = new BoardState();
                nextBoardState->prevBoardState = currentState;
                currentState = nextBoardState;
            } else { // Hard way
                bool foundANextMove = false;
                // Find the "best" option ranked by lowest other options for a move since we have to guess
                for (int smallestOptionsCount = 2; smallestOptionsCount < 9; smallestOptionsCount++) {
                    for (auto row = 0; row < 9; row++) {
                        for (auto col = 0; col < 9; col++) {
                            if (optionsForBoard[row][col].size() == smallestOptionsCount) {
                                auto optionsForRowCol = optionsForBoard[row][col];
                                char valToApply = *optionsForRowCol.begin();
                                optionsForRowCol.erase(valToApply);

                                board[row][col] = valToApply;
                                currentState->moveMade = Move(valToApply, row, col);
                                currentState->otherMovesForChangedSquare = optionsForRowCol;

                                // Copy new board and move on to next move
                                auto* nextBoardState = new BoardState();
                                nextBoardState->prevBoardState = currentState;
                                currentState = nextBoardState;
                                foundANextMove = true;
                                goto afterLoop;
                            }
                        }
                    }
                }
                afterLoop:
                if (!foundANextMove) {
                    auto* boardToRemove = currentState;
                    currentState = currentState->prevBoardState;
                    delete boardToRemove;
                    goingBack = true;
                }
            }
        }
    }

private:


    static Move* checkForEasyMove(const vector<vector<unordered_set<char>>>& optionsList) {
        for (auto row = 0; row < 9; row++) {
            for (auto col = 0; col < 9; col++) {
                if (optionsList[row][col].size() == 1) { // sure move
                    Move* move = new Move();
                    move->row = row;
                    move->column = col;
                    move->value = *optionsList[row][col].begin();
                    return move;
                }
            }
        }
        return nullptr;
    }

    static vector<vector<unordered_set<char>>> getAllAvailableOptions(const Board& board) {
        vector<vector<unordered_set<char>>> optionsList(9);
        for (auto row = 0; row < 9; row++) {
            for (auto col = 0; col < 9; col++) {
                if (board[row][col] != '.') {
                    optionsList[row].emplace_back();
                } else {
                    optionsList[row].push_back(getAvailableOptions(board, row, col));
                }
            }
        }
        return optionsList;
    }

    static unordered_set<char> getAvailableOptions(const Board& board, const int& row, const int& col) {
        unordered_set itemsLeft = { '9', '1', '2', '3', '4', '5', '6', '7', '8' };

        unordered_set<char> itemsUsed = charsInSquare(board, posToSquare(row, col));
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        if (itemsLeft.size() <= 1) return itemsLeft;

        itemsUsed = charsInRow(board, row);
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        if (itemsLeft.size() <= 1) return itemsLeft;

        itemsUsed = charsInColumn(board, col);
        for (auto& item : itemsUsed) {
            itemsLeft.erase(item);
        }
        return itemsLeft;
    }

    static int posToSquare(const int& row, const int& col) {
        static vector<vector<int>> rowToColMap = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 } };
        return rowToColMap[row / 3][col / 3];
    }

    static bool isSolved(const Board& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '.') {
                    return false;
                }
            }
        }
        for (int index = 0; index < 9; index++) {
            if (!isRowSolved(board, index) || !isColumnSolved(board, index) || !isSquareSolved(board, index)) {
                return false;
            }
        }
        return true;
    }

    static bool isSquareSolved(const Board& board, int squareNumber) {
        return charsInSquare(board, squareNumber).size() == 9;
    }

    static unordered_set<char> charsInSquare(const Board& board, int squareNumber) {
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

    static bool isRowSolved(const Board& board, int rowNumber) {
        return charsInRow(board, rowNumber).size() == 9;
    }

    static unordered_set<char> charsInRow(const Board& board, const int& rowNumber) {
        static auto cols = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        return charsIncludedInSelection(board, { rowNumber }, cols);
    }

    static bool isColumnSolved(const Board& board, const int& columnNumber) {
        return charsInColumn(board, columnNumber).size() == 9;
    }

    static unordered_set<char> charsInColumn(const Board& board, const int columnNumber) {
        static auto rows = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        return charsIncludedInSelection(board, rows, { columnNumber });
    }

    static unordered_set<char> charsIncludedInSelection(const Board& board, const vector<int>& rows, const vector<int>& columns) {
        unordered_set<char> included = {};
        for (const auto& row : rows) {
            for (const auto& col : columns) {
                if (board[row][col] == '.') continue;
                included.insert(board[row][col]);
            }
        }
        return included;
    }
};

int main() {
    // vector<vector<char>> board = {
    //     {'5','3','.','.','7','.','.','.','.'},
    //     {'6','.','.','1','9','5','.','.','.'},
    //     {'.','9','8','.','.','.','.','6','.'},
    //     {'8','.','.','.','6','.','.','.','3'},
    //     {'4','.','.','8','.','3','.','.','1'},
    //     {'7','.','.','.','2','.','.','.','6'},
    //     {'.','6','.','.','.','.','2','8','.'},
    //     {'.','.','.','4','1','9','.','.','5'},
    //     {'.','.','.','.','8','.','.','7','9'}
    // };

    // vector<vector<char>> board = {
    //     {'5','3','4','6','7','8','9','1','2'},
    //     {'6','7','2','1','9','5','3','4','8'},
    //     {'1','9','8','3','4','2','5','6','7'},
    //     {'8','5','9','7','6','1','4','2','3'},
    //     {'4','2','6','8','5','3','7','9','1'},
    //     {'7','1','3','9','2','4','8','5','6'},
    //     {'9','6','1','5','3','7','2','8','4'},
    //     {'2','8','7','4','1','9','6','3','5'},
    //     {'3','4','5','2','8','6','1','7','.'} // missing one value
    // };

    // vector<vector<char>> board = {
    //     {'.','.','9','7','4','8','.','.','.'},
    //     {'7','.','.','.','.','.','.','.','.'},
    //     {'.','2','.','1','.','9','.','.','.'},
    //     {'.','.','7','.','.','.','2','4'index,'.'},
    //     {'.','6','4','.','1','.','5','9','.'},
    //     {'.','9','8','.','.','.','3','.','.'},
    //     {'.','.','.','8','.','3','.','2','.'},
    //     {'.','.','.','.','.','.','.','.','6'},
    //     {'.','.','.','2','7','5','9','.','.'}
    // };


    // vector<vector<char>> board = {
    //     {'.','.','.','2','.','.','.','6','3'},
    //     {'3','.','.','.','.','5','4','.','1'},
    //     {'.','.','1','.','.','3','9','8','.'},
    //     {'.','.','.','.','.','.','.','9','.'},
    //     {'.','.','.','5','3','8','.','.','.'},
    //     {'.','3','.','.','.','.','.','.','.'},
    //     {'.','2','6','3','.','.','5','.','.'},
    //     {'5','.','3','7','.','.','.','.','8'},
    //     {'4','7','.','.','.','1','.','.','.'}
    // };

    vector<vector<char>> board = {
        {'.','.','.','.','.','.','.','.','.'},
        {'.','9','.','.','1','.','.','3','.'},
        {'.','.','6','.','2','.','7','.','.'},
        {'.','.','.','3','.','4','.','.','.'},
        {'2','1','.','.','.','.','.','9','8'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','2','5','.','6','4','.','.'},
        {'.','8','.','.','.','.','.','1','.'},
        {'.','.','.','.','.','.','.','.','.'}
    };

    auto start = chrono::high_resolution_clock::now();
    Solution().solveSudoku(board);
    chrono::milliseconds duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    printf("\n%ld milliseconds (%f seconds)\n", duration.count(), duration.count() / 1000.0f);
}