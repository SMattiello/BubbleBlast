
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS_NUM 5
#define COLS_NUM 6

void showMenu();
void setUpMatrix(int matrix[ROWS_NUM][COLS_NUM]);
int soluzione(int matrix[ROWS_NUM][COLS_NUM]);
void esplosione(int griglia[ROWS_NUM][COLS_NUM], int rig, int col);
void esplosioneSu(int griglia[ROWS_NUM][COLS_NUM], int rig, int col);
void esplosioneGiu(int griglia[ROWS_NUM][COLS_NUM], int rig, int col);
void esplosioneDx(int griglia[ROWS_NUM][COLS_NUM], int rig, int col);
void esplosioneSx(int griglia[ROWS_NUM][COLS_NUM], int rig, int col);

int main(int argc, char const *argv[])
{
    showMenu();
    int matrix[ROWS_NUM][COLS_NUM];
    setUpMatrix(matrix);
    int res = soluzione(matrix);
    printf("\n Mosse diponibili %d", res);

    return 0;
}


void showMenu()
{
    printf("\tB U B B L E\t B L A S T");
    printf("\nBenvenuto!\n\n");
    printf("Regole: fai esplodere tutte le bolle prima di terminare i tentativi\n");
    printf("I tipi di bolle che puoi trovare sono 3:\n \t 1) Bolla in procinto di esplodere;\n\t 2) Bolla gonfia a meta';\n\t 3) Bolla sgonfia.\n");
    printf("Quando colpirai una bolla essa si gonfiera' (se 3 -> 2, se 2 -> 1, se 1 -> 0 [esplode])\n\n");
    printf("La bolla di tipo 1 se colpita crea esplosione che coinvolgera' le bolle nelle quattro direzioni rispetto a quella da te colpita.\n\n");
    printf("Le matrici partono da zero quindi se vuoi selezionare la prima colonna o la prima riga dovrai inserire 0 e non 1!\n\n");
    printf("Vinci quando fai esplodere tutte le bolle presenti sulla griglia, perdi se non riesci nei tentativi possibili.\n\nINIZIAMO!\n\n");
}


void setUpMatrix(int matrix[ROWS_NUM][COLS_NUM])
{
    srand(time(NULL));
    for (int i = 0; i < ROWS_NUM; i++)
    {
        for (int j = 0; j < COLS_NUM; j++)
        {
            matrix[i][j] = (int)(rand() % 4);
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int soluzione(int matrix[ROWS_NUM][COLS_NUM])
{
    int moves = 0; // contatore che contiene le mosse da battere
    bool end;      // operatore usato come condizione nel ciclo per sapere quando fermarsi

    do
    {
        end = true;
        for (int r = 0; r < ROWS_NUM; r++)
        {
            for (int c = 0; c < COLS_NUM; c++)
            {
                if (matrix[r][c] == 1)
                {
                    matrix[r][c]--;
                    esplosione(matrix, r, c);
                    moves++;
                    end = false;
                }
                else if (matrix[r][c] == 2 || matrix[r][c] == 3)
                {
                    matrix[r][c]--;
                    moves++;
                    end = false;
                }
            }
        }
    } while (end == false);
    return moves;
}

/*
int soluzione(int computerGameField [ROWS_NUM][COLS_NUM]) {

    int countMoveMachine = 0;
    bool conditionToContinue;
    do {
        conditionToContinue = true;
        for (int i = 0; i < ROWS_NUM; i++) {
            for (int j = 0; j < COLS_NUM; ++j) {
                if (computerGameField[i][j] == 3 || computerGameField[i][j] == 2) {
                    computerGameField[i][j]++;
                    conditionToContinue = false;
                    countMoveMachine++;
                } else if (computerGameField[i][j] == 1) {
                    computerGameField[i][j] = 0;
                    esplosione(computerGameField, i,j);
                    conditionToContinue = false;
                    countMoveMachine++;
                }
            }
        }
    } while (conditionToContinue == false);
    return countMoveMachine;
}
*/

void esplosione(int griglia[ROWS_NUM][COLS_NUM], int rig, int col)
{
    // funzione che innesca l'esplosione sulle 4 coordinate rispetto alla cella selezionata
    esplosioneDx(griglia, rig, col);
    esplosioneSx(griglia, rig, col);
    esplosioneSu(griglia, rig, col);
    esplosioneGiu(griglia, rig, col);
}

void esplosioneSu(int griglia[ROWS_NUM][COLS_NUM], int rig, int col)
{
    bool bordoSu = false;

    if (rig > 0)
    {
        rig--;
        do
        {
            if (griglia[rig][col] != 0)
            {
                bordoSu = true;
                if (griglia[rig][col] == 1)
                {
                    griglia[rig][col]--;
                    esplosione(griglia, rig++, col);
                }
                else
                {
                    griglia[rig][col]--;
                }
            }
            else
                rig--;
            if (rig < 0)
                bordoSu = true;
        } while (bordoSu != true);
    }
    else
        return;
}

void esplosioneGiu(int griglia[ROWS_NUM][COLS_NUM], int rig, int col)
{
    bool bordoGiu = false;

    if (rig < ROWS_NUM - 1)
    {
        rig++;
        do
        {
            if (griglia[rig][col] != 0)
            {
                bordoGiu = true;
                if (griglia[rig][col] == 1)
                {
                    griglia[rig][col]--;
                    esplosione(griglia, rig--, col);
                }
                else
                    griglia[rig][col]--;
            }
            else
                rig++;
            if (rig == ROWS_NUM)
                bordoGiu = true;
        } while (bordoGiu != true);
    }
    else
        return;
}

void esplosioneDx(int griglia[ROWS_NUM][COLS_NUM], int rig, int col)
{
    bool bordoDestra = false;

    if (rig < COLS_NUM - 1)
    {          // se la cella non è nel bordo destro
        col++; // fai partire la ricerca di un elemento diverso da 0 aumentano l'indice di colonna
        do
        {
            if (griglia[rig][col] != 0)
            {
                bordoDestra = true; // se l'elemento non è 0 controlliamo se è 1 o 2 o 3
                if (griglia[rig][col] == 1)
                {
                    griglia[rig][col]--;
                    esplosione(griglia, rig, col--);
                } // caso colpito un 1
                else
                    griglia[rig][col]--; // caso colpito 2/3
            }
            else
                col++; // se non è ne 1 ne 2 ne 3 aumenta l'indice di colonna per vedere la prossima colonna
            if (col == COLS_NUM)
                bordoDestra = true;    // se la cella dopo aver aumentato il contatore è sul bordo destro
        } while (bordoDestra != true); // esci da ciclo di ricerca
    }
    else
        return; // se la cella è nel bordo destro esce dalla funzione
}

void esplosioneSx(int griglia[ROWS_NUM][COLS_NUM], int rig, int col)
{
    bool bordoSinistra = false;

    if (rig > 0)
    {
        col--;
        do
        {
            if (griglia[rig][col] != 0)
            {
                bordoSinistra = true;
                if (griglia[rig][col] == 1)
                {
                    griglia[rig][col]--;
                    esplosione(griglia, rig, col++);
                }
                else
                    griglia[rig][col]--;
            }
            else
                col--;
            if (col < 0)
                bordoSinistra = true;
        } while (bordoSinistra != true);
    }
    else
        return;
}