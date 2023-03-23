#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>

#define DEBUG false

#define ROWS_NUM 6
#define COLS_NUM 5

void showMenu();
void setUpMatrix(int[ROWS_NUM][COLS_NUM]);
int solution(int[ROWS_NUM][COLS_NUM]);
bool solver(int[ROWS_NUM][COLS_NUM], int);
void copyMatrix(int[ROWS_NUM][COLS_NUM], int[ROWS_NUM][COLS_NUM]);
bool endCheck(int[ROWS_NUM][COLS_NUM]);
void printMatrix(int[ROWS_NUM][COLS_NUM]);
void explode(int[ROWS_NUM][COLS_NUM], int, int);
void explodeUp(int[ROWS_NUM][COLS_NUM], int, int);
void explodeDown(int[ROWS_NUM][COLS_NUM], int, int);
void explodeDx(int[ROWS_NUM][COLS_NUM], int, int);
void explodeSx(int[ROWS_NUM][COLS_NUM], int, int);
void fillMatrix(int[ROWS_NUM][COLS_NUM]);

int main(int argc, char const *argv[])
{
    int matrix[ROWS_NUM][COLS_NUM];
    int row, col, steps;

    showMenu();

    if(DEBUG) fillMatrix(matrix);
    else setUpMatrix(matrix);

    printf("\n\n");

    int sol = solution(matrix);
    if(sol >= 0)
    {
        do
        {
            printMatrix(matrix);
            printf("Remaining Moves -> %d", sol - steps);
            printf("\n");
            printf("Select the bubble to be changed\n");
            printf("Insert row number: ");
            scanf("%d", &row);
            printf("Insert column number: ");
            scanf("%d", &col);
            printf("\n");
            printf("You have selected the bubble in row %d and column %d\n", row, col);
            printf("\n");

            explode(matrix, row, col);

            steps++;
            system("cls");
        } while (endCheck(matrix) == false && steps < sol);
    }
    else
    {
        printf("\nThe grid is unsolvable\n");
    }

    if(endCheck(matrix) == true) printf("YOU WIN!!\n");
    else printf("YOU LOST\n");

    system("PAUSE");

    return 0;
}

void showMenu()
{
    printf("\tB U B B L E\t B L A S T");
    printf("\nWelcome!\n\n");
    printf("Rules: burst all the bubbles before finishing the attempts\n");    
    printf("The types of bubbles you can find are 3:\n \t 1) Bubble about to explode;\t 2) Bubble half inflated;\t 3) Bubble deflated.\n");
    printf("When you hit a bubble it will inflate (if 3 -> 2, if 2 -> 1, if 1 -> 0 [explode])\n\n");
    printf("The bubble of type 1 if hit creates an explosion that will involve bubbles in the four directions relative to the one you hit.\n\n");
    printf("Matrices start from zero so if you want to select the first column or the first row you will have to enter 0 and not 1!\n\n");
    printf("You win when you make all the bubbles on the grid explode, you lose if you fail on all possible attempts.\n\Let us begin!\n\n");
}

void setUpMatrix(int matrix[ROWS_NUM][COLS_NUM])
{
    srand(time(NULL));
    for (int i = 0; i < ROWS_NUM; i++)
    {
        for (int j = 0; j < COLS_NUM; j++)
        {
            matrix[i][j] = (int)(rand() % 4);
        }
    }
}

int solution(int matrix[ROWS_NUM][COLS_NUM])
{
    int moves = 1; // counter containing the moves to be beaten
    bool res;
    do
    {
        res = solver(matrix, moves);
        if(!res)
        {
            moves ++;
        }
        if(moves > 100)
            return -1;
    } while (!res);
    return moves;
}

bool solver(int matrix[ROWS_NUM][COLS_NUM], int remain)
{
    if(endCheck(matrix))
    {
        return true;
    }
    if(remain > 0)
    {
        for(int r = 0; r < ROWS_NUM; r++)
        {
            for(int c = 0; c < COLS_NUM; c++)
            {
                if(matrix[r][c] == 0){ continue; }

                int (*copy)[COLS_NUM] = malloc(sizeof(int)*ROWS_NUM*COLS_NUM);
                copyMatrix(copy, matrix);
                explode(copy, r, c);
                //printMatrix(copy);
                if(endCheck(copy))
                {
                    if(DEBUG)
                    {
                        printMatrix(copy);
                        printf("Colpito: %d, %d \n\n", r, c);
                        endCheck(matrix);
                    }
                    free(copy);
                    return true;
                }
                else
                {
                    bool res = solver(copy, remain - 1);

                    if(res)
                    {
                        if (DEBUG)
                        {
                            printf("Colpito: %d, %d \n\n", r, c);
                            printMatrix(matrix);
                        }
                        free(copy);
                        return true;
                    }
                    else free(copy);
                }
            }
        }
    }
    return false;
}

void copyMatrix(int dest[ROWS_NUM][COLS_NUM], int orig[ROWS_NUM][COLS_NUM])
{
    memcpy(dest, orig, sizeof(int)*ROWS_NUM*COLS_NUM);
}

void printMatrix(int matrix[ROWS_NUM][COLS_NUM])
{
    for(int i = 0; i < ROWS_NUM; i++)
    {
        for(int j = 0; j < COLS_NUM; j++)
        {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

bool endCheck(int matrix[ROWS_NUM][COLS_NUM])
{
    for(int i = 0; i < ROWS_NUM; i++)
    {
        for(int j = 0; j < COLS_NUM; j++)
        {
            if(matrix[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void explode(int matrix[ROWS_NUM][COLS_NUM], int row, int col)
{
    // function that triggers the explosion on the 4 co-ordinates with respect to the selected cell
    if(matrix[row][col] > 0)
    {
        matrix[row][col]--;

        if (matrix[row][col] == 0) {
            explodeDx(matrix, row, col);
            explodeSx(matrix, row, col);
            explodeUp(matrix, row, col);
            explodeDown(matrix, row, col);
        }
    }
}

void explodeUp(int matrix[ROWS_NUM][COLS_NUM], int row, int col)
{
    bool end = false;

    while (row > 0 && !end)
    {
        row--;
        if(matrix[row][col] != 0)
        {
            end = true;
        }
    }

    if(end)
    {
        explode(matrix, row, col);
    }
}

void explodeDown(int matrix[ROWS_NUM][COLS_NUM], int row, int col)
{
    bool end = false;

    while (row < ROWS_NUM - 1 && !end)
    {
        row++;
        if(matrix[row][col] != 0)
        {
            end = true;
        }
    }

    if(end)
    {
        explode(matrix, row, col);
    }
}

void explodeDx(int matrix[ROWS_NUM][COLS_NUM], int row, int col)
{
    bool end = false;

    while (col < COLS_NUM - 1 && !end)
    {
        col++;
        if(matrix[row][col] != 0)
        {
            end = true;
        }
    }
    if(end)
    {
        explode(matrix, row, col);
    }
}

void explodeSx(int matrix[ROWS_NUM][COLS_NUM], int row, int col)
{
    bool end = false;

    while (col > 0 && !end)
    {
        col--;
        if(matrix[row][col] != 0)
        {
            end = true;
        }
    }
    if(end)
    {
        explode(matrix, row, col);
    }
}

/*
void fillMatrix(int matrix[ROWS_NUM][COLS_NUM])
{
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 2;
    matrix[0][3] = 2;
    matrix[0][4] = 1;
    matrix[1][0] = 2;
    matrix[1][1] = 4;
    matrix[1][2] = 3;
    matrix[1][3] = 4;
    matrix[1][4] = 2;
    matrix[2][0] = 2;
    matrix[2][1] = 2;
    matrix[2][2] = 2;
    matrix[2][3] = 2;
    matrix[2][4] = 2;
    matrix[3][0] = 2;
    matrix[3][1] = 2;
    matrix[3][2] = 2;
    matrix[3][3] = 2;
    matrix[3][4] = 2;
    matrix[4][0] = 1;
    matrix[4][1] = 2;
    matrix[4][2] = 2;
    matrix[4][3] = 2;
    matrix[4][4] = 1;
    matrix[5][0] = 1;
    matrix[5][1] = 2;
    matrix[5][2] = 1;
    matrix[5][3] = 2;
    matrix[5][4] = 1;
}
*/