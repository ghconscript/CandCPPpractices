#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 打印数独矩阵的函数
void print(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

// 检查数字在指定行列是否唯一
bool is_unique_in_row_and_column(int sudoku[9][9], int row, int col, int value) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == value || sudoku[i][col] == value) {
            return false;
        }
    }
    return true;
}

// 检查数字在指定3x3子矩阵是否正确（是否唯一）
bool is_correct_in_3x3_box(int sudoku[9][9], int row, int col, int value) {
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == value) {
                return false;
            }
        }
    }
    return true;
}

// 汇总检查结果，判断数字能否放置在指定位置
bool can_place(int sudoku[9][9], int row, int col, int value) {
    return is_unique_in_row_and_column(sudoku, row, col, value) &&
           is_correct_in_3x3_box(sudoku, row, col, value);
}

// 随机填充数独矩阵的函数，添加计数器避免死循环
void fill_randomly(int sudoku[9][9]) {
    const int MAX_TRY_TIMES = 100;  // 每个位置最大尝试次数，可根据实际情况调整
    int row = 0, col = 0;
    while (row < 9 && col < 9) {
        bool placed = false;
        int try_times = 0;
        while (!placed && try_times < MAX_TRY_TIMES) {
            int value = rand() % 9 + 1;
            if (can_place(sudoku, row, col, value)) {
                sudoku[row][col] = value;
                placed = true;
            }
            try_times++;
        }
        if (!placed) {
            // 若当前位置填充失败，回溯到上一个已填充的位置
            bool found = false;
            for (int r = row; r >= 0; r--) {
                for (int c = (r == row? col - 1 : 8); c >= 0; c--) {
                    if (sudoku[r][c]!= 0) {
                        row = r;
                        col = c;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                // 如果没有可回溯的已填充位置，说明整个数独填充失败，重新开始填充
                row = 0;
                col = 0;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        sudoku[i][j] = 0;
                    }
                }
            }
            continue;
        }
        col++;
        if (col == 9) {
            col = 0;
            row++;
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