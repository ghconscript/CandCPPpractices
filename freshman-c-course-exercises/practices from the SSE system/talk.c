#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void print(int sudoku[9][9])  //打印
{
    for (int i = 0; i < 9; i++) 
	{
        for (int j = 0; j < 9; j++) 
		{
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

bool is_unique_in_row_and_column(int sudoku[9][9], int row, int col, int value)   //检查行列
{
    for (int i = 0; i < 9; i++) 
	{
        if (sudoku[row][i] == value || sudoku[i][col] == value) 
		{
            return false;
        }
    }
    return true;
}

bool is_correct_in_3x3_box(int sudoku[9][9], int row, int col, int value)         //检查3*3子矩阵
{
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) 
	{
        for (int j = 0; j < 3; j++)
		{
            if (sudoku[startRow + i][startCol + j] == value) 
			{
                return false;
            }
        }
    }
    return true;
}

bool can_place(int sudoku[9][9], int row, int col, int value)                 //汇总检查结果
{
    return is_unique_in_row_and_column(sudoku, row, col, value) &&
           is_correct_in_3x3_box(sudoku, row, col, value);
}

void fill_randomly(int sudoku[9][9]) 
{
    for (int i = 0; i < 9; i++) 
	{
        for (int j = 0; j < 9; j++) 
		{
            bool placed = false;
            while (!placed) 
			{
                int value = rand() % 9 + 1;
                if (can_place(sudoku, i, j, value)) 
				{
                    sudoku[i][j] = value;
                    placed = true;
                }
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