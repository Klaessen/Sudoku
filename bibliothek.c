#include <stdio.h>
#include <conio.h>
#include "./Headers/bibliothek.h"
#include "./generators.c"

int buildSudoku() {
    int arrSudoku[9][9] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    loadSudoku(arrSudoku);

    printf("%d", arrSudoku[1][3]);

    for (int i = 0; i < 9; i++)
    {
        if(i % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (int j = 0; j < 9; j += 3) {
            if (j == 0) {
                printf("|");
            }
            printf(" %d %d %d |", arrSudoku[i][j], arrSudoku[i][j + 1], arrSudoku[i][j + 2]);
            // printf("sd");
        }
        printf("\n");
    }
    printf("+-------+-------+-------+\n");

    while(1)
    {
        switch(getch())
        {
            case 119:
                printf("UP\n");
                break;
            case 115:
                printf("DOWN\n");
                break;
            case 100:
                printf("RIGHT\n");
                break;
            case 97:
                printf("LEFT\n");
                break;
        }
    }

    return 0;

}