#include <stdio.h>
#include <stdlib.h>

void printCube(char cube[6][3][3]);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Insufficient number of arguments\n");
        return 0;
    }

    char cube[6][3][3] = {0};
    int i = 0,j,k;

    // File i/o
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL) {
        printf("An error has occured\n");
        return 1;
    }
    while(!feof(fp)){
        fscanf(fp,"%c%c%c\n",&(cube[i][0][0]), &(cube[i][0][1]), &(cube[i][0][2]));
        fscanf(fp,"%c%c%c\n",&(cube[i][1][0]), &(cube[i][1][1]), &(cube[i][1][2]));
        fscanf(fp,"%c%c%c\n",&(cube[i][2][0]), &(cube[i][2][1]), &(cube[i][2][2]));
        i++;
    }
    fclose(fp);




    printCube(cube);

    return 0;
}

void printCube(char cube[6][3][3]) {
    int i,j,k;
    for(j = 0; j < 3; j++) {
        for(k = 0; k < 3; k++)
            printf("  ");
        for(k = 0; k < 3; k++)
            printf("%c ",cube[0][j][k]);
        printf("\n");
    }
    for(j = 0; j < 3; j++) {
        for(i = 1; i <= 4; i++) {
            for(k = 0; k < 3; k++)
                printf("%c ",cube[i][j][k]);
        }
        printf("\n");
    }
    for(j = 0; j < 3; j++) {
        for(k = 0; k < 3; k++)
            printf("  ");
        for(k = 0; k < 3; k++)
            printf("%c ",cube[5][j][k]);
        printf("\n");
    }
}