#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void print(int sudoku[9][9]) {
	int i,j; 
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}


bool is_unique_in_row_and_column(int sudoku[9][9], int row, int col, int value) {
	int i;
    for (i = 0; i < 9; i++) {
        if (sudoku[row][i] == value || sudoku[i][col] == value) {
            return false;
        }
    }
    return true;
}


bool is_correct_in_3x3_box(int sudoku[9][9], int row, int col, int value) {
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    int i,j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == value) {
                return false;
            }
        }
    }
    return true;
}


bool can_place(int sudoku[9][9], int row, int col, int value) {
    return is_unique_in_row_and_column(sudoku, row, col, value) &&
           is_correct_in_3x3_box(sudoku, row, col, value);
}

void fill_randomly(int sudoku[9][9]) {
    const int MAX_TRY_TIMES = 100; 
    int i,j=0;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            bool placed = false;
            int try_times = 0;
            while (!placed && try_times < MAX_TRY_TIMES) {
                int value = rand() % 9 + 1;
                if (can_place(sudoku, i, j, value)) {
                    sudoku[i][j] = value;
                    placed = true;
                }
                try_times++;
            }
            if (!placed) {
              	int k;
                for (k = 0; k < 9; k++) {
                    sudoku[i][k] = 0;
                }
                j = 0;
            }
        }
    }
}

int main() {
    int sudoku[9][9] = {0};
    srand(time(0));
    fill_randomly(sudoku);
    print(sudoku);
    return 0;
}
