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
                    //fill current field with random number
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

    // seed sudoku
    seed(sudoku);

    // preview seed
    printf("Printing the Sudoku\n");
    for (int rows = 0; rows < 9; rows++)
    {
        for (int columns = 0; columns < 9; columns++)
        {
            printf("%d  ", sudoku[rows][columns]);
        }
        printf("\n");
    }
}
