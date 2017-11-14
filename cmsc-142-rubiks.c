#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define RED 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define YELLOW 5
#define CLOCKWISE 0

void printCube(char cube[6][3][3]);
void rotateCube(char (*c)[][3][3], int color, int orientation);

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

    rotateCube(&cube, 0, 1);

    printCube(cube);

    return 0;
}

void rotateCube(char (*c)[][3][3], int color, int orientation) {
    int temp[3][3];
    int temp2[3];
    int temp3[3];

    memcpy(temp, (*c)[color], sizeof(temp));
    
    if(orientation) { //CLOCKWISE
        //switch elements inside the 3x3 matrix first
        for(int i = 0; i < 3; i++) {
            (*c)[color][i][2] = temp[0][i];
            (*c)[color][2][i] = temp[i][2];
            (*c)[color][i][0] = temp[2][i];
            (*c)[color][0][i] = temp[i][0];
        }

        // for(int j = 0; j < 4; j++) {
        //     switch(color) {
        //         case 0 :    //IF WHITE == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //GREEN TO ORANGE
        //                 temp2[i] = (*c)[3][0][i];
        //                 (*c)[3][0][i] = (*c)[4][0][i];
        //                 //ORANGE TO BLUE
        //                 temp3[i] = (*c)[2][0][i];
        //                 (*c)[2][0][i] = temp2[i];
        //                 //BLUE TO RED
        //                 temp2[i] = (*c)[1][0][i];
        //                 (*c)[1][0][i] = temp3[i];
        //                 //RED TO GREEN
        //                 (*c)[4][0][i] = temp2[i];
        //             }
        //             break;
        //         case 1 :    //IF RED == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //WHITE TO BLUE
        //                 temp2[i] = (*c)[2][i][0];
        //                 (*c)[2][i][0] = (*c)[0][i][0];
        //                 //BLUE TO YELLOW
        //                 temp3[i] = (*c)[5][i][2];
        //                 (*c)[5][abs(i-2)][2] = temp2[i];
        //                 //YELLOW TO GREEN
        //                 temp2[i] = (*c)[4][i][2];
        //                 (*c)[4][i][2] = temp3[i];
        //                 //GREEN TO WHITE
        //                 (*c)[0][abs(i-2)][0] = temp2[i];
        //             }
        //             break;
        //         case 2 :    //IF BLUE == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //WHITE TO ORANGE
        //                 temp2[i] = (*c)[3][i][0];
        //                 (*c)[3][i][0] = (*c)[0][2][i];
        //                 //ORANGE TO YELLOW
        //                 temp3[i] = (*c)[5][2][i];
        //                 (*c)[5][2][i] = temp2[i];
        //                 //YELLOW TO RED
        //                 temp2[i] = (*c)[1][i][2];
        //                 (*c)[1][abs(i-2)][2] = temp3[i];
        //                 //RED TO WHITE
        //                 (*c)[0][2][abs(i-2)] = temp2[i];
        //             }
        //             break;
        //         case 3 :    //IF ORANGE == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //WHITE TO GREEN
        //                 temp2[i] = (*c)[4][i][0];
        //                 (*c)[4][i][0] = (*c)[0][abs(i-2)][2];
        //                 //GREEN TO YELLOW
        //                 temp3[i] = (*c)[5][i][0];
        //                 (*c)[5][i][0] = temp2[i];
        //                 //YELLOW TO BLUE
        //                 temp2[i] = (*c)[2][i][2];
        //                 (*c)[2][abs(i-2)][2] = temp3[i];
        //                 //BLUE TO WHITE
        //                 (*c)[0][i][2] = temp2[i];
        //             }
        //             break;
        //         case 4 :    //IF GREEN == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //WHITE TO RED
        //                 temp2[i] = (*c)[1][i][0];
        //                 (*c)[1][i][0] = (*c)[0][0][abs(i-2)];
        //                 //RED TO YELLOW
        //                 temp3[i] = (*c)[5][i][0];
        //                 (*c)[5][abs(i-2)][0] = temp2[i];
        //                 //YELLOW TO ORANGE
        //                 temp2[i] = (*c)[2][i][2];
        //                 (*c)[2][i][2] = temp3[i];
        //                 //ORANGE TO WHITE
        //                 (*c)[0][i][2] = temp2[i];
        //             }
        //             break;
        //         case 5 :    //IF YELLOW == FACE
        //             for(int i = 0; i < 3; i++) {
        //                 //GREEN TO RED
        //                 temp2[i] = (*c)[1][2][i];
        //                 (*c)[1][2][i] = (*c)[4][2][i];
        //                 //RED TO BLUE
        //                 temp3[i] = (*c)[2][2][i];
        //                 (*c)[2][2][i] = temp2[i];
        //                 //BLUE TO ORANGE
        //                 temp2[i] = (*c)[3][2][i];
        //                 (*c)[3][2][i] = temp3[i];
        //                 //ORANGE TO GREEN
        //                 (*c)[4][2][i] = temp2[i];
        //             }
        //             break;
        //     }
        // }
    } else {
    }
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