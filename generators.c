#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// random seed for new sudoku
void seed(int (*sudoku)[9])
{
    // initialize random number generator
    srand(time(NULL));

    // generate 3 seperate squares
    for (int y = 3; y < 10; y += 3)
    {
        // fill values and avoid duplicates
        while (sudoku[y - 1][y - 1] == 0)
        {
            // values for squares
            int square[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

            // columns
            for (int x = y - 3; x < y; x++)
            {
                // rows
                for (int i = y - 3; i < y; i++)
                {
                    // fill current field with random number
                    while (sudoku[x][i] == 0)
                    {
                        // random number
                        int number = rand() % 9;

                        // check if number is already in square
                        if (square[number] != 0)
                        {
                            sudoku[x][i] = square[number];
                            square[number] = 0;
                        }
                    }
                }
            }
        }
    }
}

int checkRow(int (*sudoku)[9], int x, int number)
{
    // check if number is already in row
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[x][i] == number)
        {
            return 0;
        }
    }
    return 1;
}

int checkColumn(int (*sudoku)[9], int y, int number)
{
    // check if number is already in column
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[i][y] == number)
        {
            return 0;
        }
    }
    return 1;
}

int checkSquare(int (*sudoku)[9], int x, int y, int number)
{
    // check if number is already in square
    for (int i = x - x % 3; i < x - x % 3 + 3; i++)
    {
        for (int j = y - y % 3; j < y - y % 3 + 3; j++)
        {
            if (sudoku[i][j] == number)
            {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int (*sudoku)[9], int x, int y)
{
    // rows
    for (; x < 9; x++)
    {
        // columns
        for (; y < 9; y++)
        {
            // only fill empty fields or when next field failed to be filled
            if (sudoku[x][y] == 0)
            {
                // numbers 1-9
                for (int number = 1; number < 10; number++)
                {
                    // if number is available in row, column and square set it
                    if (checkRow(sudoku, x, number) && checkColumn(sudoku, y, number) && checkSquare(sudoku, x, y, number))
                    {
                        // set field to number
                        sudoku[x][y] = number;

                        // if next field can be filled, return 1
                        if (solve(sudoku, x, y + 1) == 1)
                        {
                            return 1;
                        }
                        else
                        {
                            // if next field can't be filled, set number to 0 and continue
                            sudoku[x][y] = 0;
                        }
                    }
                }
                // if no number is available in row, column and square return 0
                return 0;
            }
        }
        // reset column
        y = 0;
    }
    // return 1 if sudoku is solved
    return 1;
}

void saveSudoku(int (*sudoku)[9])
{
    // open file
    FILE *file = fopen("sudoku.txt", "w");

    // write sudoku to file
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            fprintf(file, "%d ", sudoku[x][y]);
        }
        fprintf(file, "\n");
    }

    // close file
    fclose(file);
}

void loadSudoku(int (*sudoku)[9])
{
    // open file
    FILE *file = fopen("sudoku.txt", "r");

    // read sudoku from file
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            fscanf(file, "%d", &sudoku[x][y]);
        }
    }

    // close file
    fclose(file);
}

void generatePuzzle(int (*sudoku)[9], int difficulty) {

    // initialize random number generator
    srand(time(NULL));

    //counter for number of empty fields
    int i = 0;

    //set random fields to 0
    while (i < difficulty)
    {
        int x = rand() % 9;
        int y = rand() % 9;

        if (sudoku[x][y] != 0)
        {
            sudoku[x][y] = 0;
            i++;
        }  
    }

}

void giveHint(int (*sudoku)[9], int hint [3])
{
 for (int x = 0; x < 9; x++)
    {
        // columns
        for (int y = 0; y < 9; y++)
        {
            // next empty field
            if (sudoku[x][y] == 0)
            {
                // numbers 1-9
                for (int number = 1; number < 10; number++)
                {
                    // if number is available in row, column and square set it
                    if (checkRow(sudoku, x, number) && checkColumn(sudoku, y, number) && checkSquare(sudoku, x, y, number))
                    {
                        // set field to number
                        sudoku[x][y] = number;

                        // if next field can be filled, return number and position
                        if (solve(sudoku, x, y + 1) == 1)
                        {   
                            sudoku[x][y] = 0;
                            hint[0] = number;
                            hint[1] = x;
                            hint[2] = y;
                            break;
                        }
                        else
                        {
                            // if next field can't be filled give the player a hint to delete a number
                            hint[0] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int getSudokuStatus(int (*sudoku)[9])
{
    // check if sudoku is solved
    for (int x = 0; x < 9; x++)
    {
        // columns
        for (int y = 0; y < 9; y++)
        {
            if (sudoku[x][y] == 0)
            {
                printf("Sudoku is not solved!\n");
                return 0;
            }
        }
    }
    printf("Sudoku is solved!\n");
    return 1;
}


int main(int argc, char *argv[])
{
    // initialize sudoku
    int sudoku[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    //helper array for hints
    int hint[3] = {0, 0, 0};

    //state of sudoku
    int status = 0;

    //numbers of empty fields
    int difficulty = 5;

    // seed sudoku
    seed(sudoku);

    printf("\nPreview of Sudoku seed\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            printf("%d  ", sudoku[rows][columns]);
        }
        printf("\n");
    }

    // commit sudoku
    solve(sudoku, 0, 0);

    printf("\nDisplaying the solved Sudoku\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            printf("%d  ", sudoku[rows][columns]);
        }
        printf("\n");
    }

    // save sudoku to file
    saveSudoku(sudoku);

    //reset
    printf("\nResetting the Sudoku\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            sudoku[rows][columns] = 0;
        }
    }

    //load sudoku from file
    loadSudoku(sudoku);

    printf("\nDisplaying the loaded Sudoku\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            printf("%d  ", sudoku[rows][columns]);
        }
        printf("\n");
    }

    // generate puzzle from solved sudoku
    generatePuzzle(sudoku, difficulty);

    printf("\nDisplaying the Puzzle\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            printf("%d  ", sudoku[rows][columns]);
        }
        printf("\n");
    }

    // give hint for next field
    giveHint(sudoku, hint);

    printf("\nDisplaying Hint\n");
    for (int x = 0; x < 3; x++)
    {
        printf("%d  ", hint[x]);
    }
    printf("\n");

    status = getSudokuStatus(sudoku);

    printf("\nSolving the Sudoku...\n");
    solve(sudoku, 0, 0);

    status = getSudokuStatus(sudoku);
}
