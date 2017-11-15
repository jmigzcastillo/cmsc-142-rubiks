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
    if(argc != 4) {
        // printf("Insufficient number of arguments\n");
        printf("To use: ./a.out <input file> <number for rotation> <clockwise(1) or counter (0)>\n");
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

    rotateCube(&cube, atoi(argv[2]), atoi(argv[3]));

    printCube(cube);

    return 0;
}

void rotateCube(char (*c)[][3][3], int color, int orientation) {
    int temp[3][3];
    int temp2[3];
    int temp3[3];
    int temp4[3];
    int temp5[3];
    int i,j;

    for(i=0;i<3;i++) {
        for(j=0;j<3;j++)
            temp[i][j] = (*c)[color][i][j];
    }

    printf("\n\n");
    // for(i=0;i<3;i++) {
    //     for(j=0;j<3;j++)
    //         printf("%2c",temp[i][j]);
    //     printf("\n");
    // }
    // printf("\n\n");

    if(orientation) { //CLOCKWISE
        //switch elements inside the 3x3 matrix first
        (*c)[color][0][0] = temp[2][0];
        (*c)[color][0][1] = temp[1][0];
        (*c)[color][0][2] = temp[0][0];
        (*c)[color][1][0] = temp[2][1];
        (*c)[color][1][2] = temp[0][1];
        (*c)[color][2][0] = temp[2][2];
        (*c)[color][2][1] = temp[1][2];
        (*c)[color][2][2] = temp[0][2];

        switch(color) {
            case 0 :    //IF WHITE == FACE
                for(int i = 0; i < 3; i++) {
                    //GREEN TO ARRAY
                    temp2[i] = (*c)[4][0][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[3][0][i];
                    //BLUE TO ARRAY
                    temp4[i] = (*c)[2][0][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[1][0][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO GREEN
                    (*c)[4][0][i] = temp5[i];
                    //ARRAY TO ORANGE
                    (*c)[3][0][i] = temp2[i];
                    //ARRAY TO BLUE
                    (*c)[2][0][i] = temp3[i];
                    //ARRAY TO RED
                    (*c)[1][0][i] = temp4[i];
                }
                break;
            case 1 :    //IF RED == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][i][0];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][i][0];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][abs(i-2)][0];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][abs(i-2)][2];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][i][0] = temp5[i];
                    //ARRAY TO BLUE
                    (*c)[2][i][0] = temp2[i];
                    //ARRAY TO YELLOW
                    (*c)[5][i][0] = temp3[i];
                    //ARRAY TO GREEN
                    (*c)[4][i][2] = temp4[i];
                }
                break;
            case 2 :    //IF BLUE == FACE
                for(int i = 0; i < 3; i++) {
                    //YELLOW TO ARRAY
                    temp2[i] = (*c)[5][0][i];
                    //ORRANGE TO ARRAY
                    temp3[i] = (*c)[3][abs(i-2)][0];
                    //WHITE TO ARRAY
                    temp4[i] = (*c)[0][2][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[1][abs(i-2)][2];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO YELLOW
                    (*c)[5][0][i] = temp3[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][i][0] = temp4[i];
                    //ARRAY TO WHITE
                    (*c)[0][2][i] = temp5[i];
                    //ARRAY TO RED
                    (*c)[1][i][2] = temp2[i];
                }
                break;
            case 3 :    //IF ORANGE == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][abs(i-2)][2];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][i][2];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][i][2];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][abs(i-2)][0];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][i][2] = temp4[i];
                    //ARRAY TO BLUE
                    (*c)[2][i][2] = temp5[i];
                    //ARRAY TO YELLOW
                    (*c)[5][i][2] = temp2[i];
                    //ARRAY TO GREEN
                    (*c)[4][i][0] = temp3[i];
                }
                break;
            case 4 :    //IF GREEN == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][0][i];
                    //RED TO ARRAY
                    temp3[i] = (*c)[1][i][0];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][2][abs(i-2)];
                    //ORRANGE TO ARRAY
                    temp5[i] = (*c)[3][i][2];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][0][i] = temp5[i];
                    //ARRAY TO RED
                    (*c)[1][i][0] = temp2[i];
                    //ARRAY TO YELLOW
                    (*c)[5][2][i] = temp3[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][i][2] = temp4[i];
                }
                break;
            case 5 :    //IF YELLOW == FACE
               for(int i = 0; i < 3; i++) {
                    //RED TO ARRAY
                    temp2[i] = (*c)[1][2][i];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][2][i];
                    //ORRANGE TO ARRAY
                    temp4[i] = (*c)[3][2][i];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][2][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO RED
                    (*c)[1][2][i] = temp5[i];
                    //ARRAY TO BLUE
                    (*c)[2][2][i] = temp2[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][2][i] = temp3[i];
                    //ARRAY TO GREEN
                    (*c)[4][2][i] = temp4[i];
                }
                break;
        }
    } else {
        // counter-clockwise
        (*c)[color][0][0] = temp[0][2];
        (*c)[color][0][1] = temp[1][2];
        (*c)[color][0][2] = temp[2][2];
        (*c)[color][1][0] = temp[0][1];
        (*c)[color][1][2] = temp[2][1];
        (*c)[color][2][0] = temp[0][0];
        (*c)[color][2][1] = temp[1][0];
        (*c)[color][2][2] = temp[2][0];

        switch(color) {
            case 0 :    //IF WHITE == FACE
                for(int i = 0; i < 3; i++) {
                    //GREEN TO ARRAY
                    temp2[i] = (*c)[3][0][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[2][0][i];
                    //BLUE TO ARRAY
                    temp4[i] = (*c)[1][0][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[4][0][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO GREEN
                    (*c)[4][0][i] = temp2[i];
                    //ARRAY TO ORANGE
                    (*c)[3][0][i] = temp3[i];
                    //ARRAY TO BLUE
                    (*c)[2][0][i] = temp4[i];
                    //ARRAY TO RED
                    (*c)[1][0][i] = temp5[i];
                }
                break;
            case 1 :    //IF RED == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[2][i][0];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[5][abs(i-2)][0];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[4][abs(i-2)][2];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[0][i][0];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][i][0] = temp2[i];
                    //ARRAY TO BLUE
                    (*c)[2][i][0] = temp3[i];
                    //ARRAY TO YELLOW
                    (*c)[5][i][0] = temp4[i];
                    //ARRAY TO GREEN
                    (*c)[4][i][2] = temp5[i];
                }
                break;
            case 2 :    //IF BLUE == FACE
                for(int i = 0; i < 3; i++) {
                    //YELLOW TO ARRAY
                    temp2[i] = (*c)[3][abs(i-2)][0];
                    //ORRANGE TO ARRAY
                    temp3[i] = (*c)[0][2][i];
                    //WHITE TO ARRAY
                    temp4[i] = (*c)[1][abs(i-2)][2];
                    //RED TO ARRAY
                    temp5[i] = (*c)[5][0][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO YELLOW
                    (*c)[5][0][i] = temp4[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][i][0] = temp3[i];
                    //ARRAY TO WHITE
                    (*c)[0][2][i] = temp2[i];
                    //ARRAY TO RED
                    (*c)[1][i][2] = temp5[i];
                }
                break;
            case 3 :    //IF ORANGE == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[2][i][2];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[5][i][2];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[4][abs(i-2)][0];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[0][abs(i-2)][2];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][i][2] = temp4[i];
                    //ARRAY TO BLUE
                    (*c)[2][i][2] = temp5[i];
                    //ARRAY TO YELLOW
                    (*c)[5][i][2] = temp2[i];
                    //ARRAY TO GREEN
                    (*c)[4][i][0] = temp3[i];
                }
                break;
            case 4 :    //IF GREEN == FACE
                for(int i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[1][i][0];
                    //RED TO ARRAY
                    temp3[i] = (*c)[5][2][abs(i-2)];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[3][i][2];
                    //ORRANGE TO ARRAY
                    temp5[i] = (*c)[0][0][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][0][i] = temp2[i];
                    //ARRAY TO RED
                    (*c)[1][i][0] = temp3[i];
                    //ARRAY TO YELLOW
                    (*c)[5][2][i] = temp4[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][i][2] = temp5[i];
                }
                break;
            case 5 :    //IF YELLOW == FACE
               for(int i = 0; i < 3; i++) {
                    //RED TO ARRAY
                    temp2[i] = (*c)[2][2][i];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[3][2][i];
                    //ORRANGE TO ARRAY
                    temp4[i] = (*c)[4][2][i];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[1][2][i];
                }
                for(int i = 0; i < 3; i++) {
                    //ARRAY TO RED
                    (*c)[1][2][i] = temp2[i];
                    //ARRAY TO BLUE
                    (*c)[2][2][i] = temp3[i];
                    //ARRAY TO ORRANGE
                    (*c)[3][2][i] = temp4[i];
                    //ARRAY TO GREEN
                    (*c)[4][2][i] = temp5[i];
                }
                break;
        }
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