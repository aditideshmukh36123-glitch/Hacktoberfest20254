#include <stdio.h>

#define N 9

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

// Check if num can be placed at board[row][col]
int isSafe(int board[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (board[row][x] == num || board[x][col] == num)
            return 0;

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

// Solve Sudoku using backtracking
int solveSudoku(int board[N][N]) {
    int row, col;
    int empty = 0;

    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                empty = 1;
                goto FIND_EMPTY; // break out of nested loop
            }
        }
    }
FIND_EMPTY:

    if (!empty)
        return 1; // No empty cell left, solved

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board))
                return 1;

            board[row][col] = 0; // backtrack
        }
    }
    return 0; // trigger backtracking
}

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board))
        printBoard(board);
    else
        printf("No solution exists.\n");

    return 0;
}
