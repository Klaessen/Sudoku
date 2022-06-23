#include <stdio.h>
#include <stdlib.h>
#include "./bibliothek.c"

int main() {
    int menuPoint = 0;
    int viable = 0;

    printf("Sudoku!!?!\n\n");
    printf("1 - Random Sudoku\n");
    printf("2 - Load Sudoku\n\n");

    do {
        printf("Select Menu Point\n");
        scanf("%d", &menuPoint);

        switch(menuPoint) {
            case 1:
                buildSudoku();
                viable = 1;
                break;
            case 2:
                viable = 1;
                break;
            default:
                viable = 0;
                break;
        }
    } while(viable != 3);
}
