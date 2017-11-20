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
void solve(char (*c)[][3][3]);
int isCubeSolved(char (*c)[][3][3]);

int main(int argc, char **argv) {
    // if(argc != 4) {
    //     // printf("Insufficient number of arguments\n");
    //     printf("To use: ./a.out <input file> <number for rotation> <clockwise(1) or counter (0)>\n");
    //     return 0;
    // }

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

    // rotateCube(&cube, 3, 0);
    // rotateCube(&cube, 4, 1);
    // rotateCube(&cube, 5, 0);
    // rotateCube(&cube, 1, 1);
    // rotateCube(&cube, 3, 0);
    solve(&cube);

    //printf("is solved: %d\n", isCubeSolved(&cube));
    if(isCubeSolved(&cube)){
        printCube(cube);
        
    }

    return 0;
}

int isCubeSolved(char (*c)[][3][3]) {
    int i, j, k;
    char color[6] = {'W', 'R', 'B', 'O', 'G', 'Y'};
    int solved = 1;

    for(i=0; i<6; i++){
        for(j=0; j<3; j++){
            for(k=0; k<3; k++){
                //printf("[%d][%d] ->%c     ->%c\n", i, j, (*c)[i][j][k], color[i]);
                if((*c)[i][j][k] != color[i]){
                   return 0;
                } 
                //printf("%c ", (*c)[i][j][k]);
            }
            //printf("\n");
        }
    }

    return 1;
}

void solve(char (*c)[][3][3]) {
    int N = 10;
    int start, move;
    int nopts[N+2]; //array top of stacks
    int option[N+2][N+2]; //array stacks of options
    int i, checkpoint;
    int candidate[12] = {00, 01, 10, 11, 20, 21, 30, 31, 40, 41, 50, 51};
    int solved = 0;
    int end;

    move = start = 0; 
    nopts[start]= 1;
    checkpoint = 1;

    while (!solved){
        while (nopts[start] >0){
            if(nopts[move]>0){
                move++;
                nopts[move]=0; //initialize new move

                //print - solution found!
                if(move==N+1){
                    for(i=checkpoint;i<move;i++){
                        if (isCubeSolved(c)){
                            solved = 1;
                            end = i;
                            break;
                        }
                        switch(option[i][nopts[i]]) {
                            case 0: //white counter-clockwise
                                rotateCube(c, 0, 0);
                                break;
                            case 1: //white clockwise
                                rotateCube(c, 0, 1);
                                break;
                            case 10: //red counter-clockwise
                                rotateCube(c, 1, 0);
                                break;
                            case 11: //red clockwise
                                rotateCube(c, 1, 1);
                                break;
                            case 20: //blue counter-clockwise
                                rotateCube(c, 2, 0);
                                break;
                            case 21: //blue clockwise
                                rotateCube(c, 2, 1);
                                break;
                            case 30: //orange counter-clockwise
                                rotateCube(c, 3, 0);
                                break;
                            case 31: //orange clockwise
                                rotateCube(c, 3, 1);
                                break;
                            case 40: //green counter-clockwise
                                rotateCube(c, 4, 0);
                                break;
                            case 41: //greem clockwise
                                rotateCube(c, 4, 1);
                                break;
                            case 50: //yellow counter-clockwise
                                rotateCube(c, 5, 0);
                                break;
                            case 51: //yellow clockwise
                                rotateCube(c, 5, 1);
                                break;
                        }
                        if (isCubeSolved(c)){
                            solved = 1;
                            end = i;
                            break;
                        }

                        // printf("\n\n--- rotate %d\n", option[i][nopts[i]]);
                        // printCube(*c);
                        if(solved){
                            break;
                        }
                    }

                    if(solved){
                        break;
                    }
                }
                //populate
                else {
                    for(i=11; i >=0; i--) {
                        nopts[move]++;
                        option[move][nopts[move]] = candidate[i];
                    } 
                }
            }
            else 
            {
                //backtrack
                move--;
                //reverse back to previous pattern
                if(nopts[move] != 0){
                    switch(option[move][nopts[move]]){
                        case 00:
                            rotateCube(c, 0, 1);
                            break;
                        case 01:
                            rotateCube(c, 0, 0);
                            break;
                        case 10:
                            rotateCube(c, 1, 1);
                            break;
                        case 11:
                            rotateCube(c, 1, 0);
                            break;
                        case 20:
                            rotateCube(c, 2, 1);
                            break;
                        case 21:
                            rotateCube(c, 2, 0);
                            break;
                        case 30:
                            rotateCube(c, 3, 1);
                            break;
                        case 31:
                            rotateCube(c, 3, 0);
                            break;
                        case 40:
                            rotateCube(c, 4, 1);
                            break;
                        case 41:
                            rotateCube(c, 4, 0);
                            break;
                        case 50:
                            rotateCube(c, 5, 1);
                            break;
                        case 51:
                            rotateCube(c, 5, 0);
                            break;
                    }
                }
                // printf("\n--- backtrack \n");
                // printCube(*c);
                nopts[move]--;
                checkpoint = move;
            }
        }
    }

    printf("solution:\n");
    for(i=1; i<=end; i++){
        printf("%d\n", option[i][nopts[i]]);
    }
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

    // printf("\n\n");
    // for(i=0;i<3;i++) {
    //     for(j=0;j<3;j++)
    //         printf("%2c",temp[i][j]);
    //     printf("\n");
    // }
    // printf("\n\n");
    if(orientation > 1) {
        printf("Invalid orientation value!\n");
        exit(0);
    }

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
                for(i = 0; i < 3; i++) {
                    //GREEN TO ARRAY
                    temp2[i] = (*c)[4][0][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[3][0][i];
                    //BLUE TO ARRAY
                    temp4[i] = (*c)[2][0][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[1][0][i];
                }
                for(i = 0; i < 3; i++) {
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
                for(i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][i][0];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][i][0];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][abs(i-2)][0];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][abs(i-2)][2];
                }
                for(i = 0; i < 3; i++) {
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
                for(i = 0; i < 3; i++) {
                    //YELLOW TO ARRAY
                    temp2[i] = (*c)[5][0][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[3][abs(i-2)][0];
                    //WHITE TO ARRAY
                    temp4[i] = (*c)[0][2][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[1][abs(i-2)][2];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO YELLOW
                    (*c)[5][0][i] = temp3[i];
                    //ARRAY TO ORANGE
                    (*c)[3][i][0] = temp4[i];
                    //ARRAY TO WHITE
                    (*c)[0][2][i] = temp5[i];
                    //ARRAY TO RED
                    (*c)[1][i][2] = temp2[i];
                }
                break;
            case 3 :    //IF ORANGE == FACE
                for(i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][abs(i-2)][2];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][i][2];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][i][2];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][abs(i-2)][0];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][i][2] = temp3[i];
                    //ARRAY TO BLUE
                    (*c)[2][i][2] = temp4[i];
                    //ARRAY TO YELLOW
                    (*c)[5][i][2] = temp5[i];
                    //ARRAY TO GREEN
                    (*c)[4][i][0] = temp2[i];
                }
                break;
            case 4 :    //IF GREEN == FACE
                for(i = 0; i < 3; i++) {
                    //WHITE TO ARRAY
                    temp2[i] = (*c)[0][0][abs(i-2)];
                    //RED TO ARRAY
                    temp3[i] = (*c)[1][i][0];
                    //YELLOW TO ARRAY
                    temp4[i] = (*c)[5][2][abs(i-2)];
                    //ORANGE TO ARRAY
                    temp5[i] = (*c)[3][i][2];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][0][i] = temp5[i];
                    //ARRAY TO RED
                    (*c)[1][i][0] = temp2[i];
                    //ARRAY TO YELLOW
                    (*c)[5][2][i] = temp3[i];
                    //ARRAY TO ORANGE
                    (*c)[3][i][2] = temp4[i];
                }
                break;
            case 5 :    //IF YELLOW == FACE
               for(i = 0; i < 3; i++) {
                    //RED TO ARRAY
                    temp2[i] = (*c)[1][2][i];
                    //BLUE TO ARRAY
                    temp3[i] = (*c)[2][2][i];
                    //ORANGE TO ARRAY
                    temp4[i] = (*c)[3][2][i];
                    //GREEN TO ARRAY
                    temp5[i] = (*c)[4][2][i];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO RED
                    (*c)[1][2][i] = temp5[i];
                    //ARRAY TO BLUE
                    (*c)[2][2][i] = temp2[i];
                    //ARRAY TO ORANGE
                    (*c)[3][2][i] = temp3[i];
                    //ARRAY TO GREEN
                    (*c)[4][2][i] = temp4[i];
                }
                break;
            default:
                printf("Invalid color value!\n");
                exit(0);
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
                for(i = 0; i < 3; i++) {
                    //GREEN TO ARRAY
                    temp2[i] = (*c)[3][0][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[2][0][i];
                    //BLUE TO ARRAY
                    temp4[i] = (*c)[1][0][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[4][0][i];
                }
                for(i = 0; i < 3; i++) {
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
                for(i = 0; i < 3; i++) {
                    //BLUE TO ARRAY
                    temp2[i] = (*c)[2][i][0];
                    //YELLOW TO ARRAY
                    temp3[i] = (*c)[5][i][0];
                    //GREEN TO ARRAY
                    temp4[i] = (*c)[4][abs(i-2)][2];
                    //WHITE TO ARRAY
                    temp5[i] = (*c)[0][abs(i-2)][0];
                }
                for(i = 0; i < 3; i++) {
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
                for(i = 0; i < 3; i++) {
                    //ORANGE TO ARRAY
                    temp2[i] = (*c)[3][i][0];
                    //WHITE TO ARRAY
                    temp3[i] = (*c)[0][2][abs(i-2)];
                    //RED TO ARRAY
                    temp4[i] = (*c)[1][i][2];
                    //YELLOW TO ARRAY
                    temp5[i] = (*c)[5][0][abs(i-2)];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO YELLOW
                    (*c)[5][0][i] = temp4[i];
                    //ARRAY TO RED
                    (*c)[1][i][2] = temp3[i];
                    //ARRAY TO WHITE
                    (*c)[0][2][i] = temp2[i];
                    //ARRAY TO ORANGE
                    (*c)[3][i][0] = temp5[i];
                }
                break;
            case 3 :    //IF ORANGE == FACE
                for(i = 0; i < 3; i++) {
                    //BLUE TO ARRAY
                    temp2[i] = (*c)[2][i][2];
                    //YELLOW TO ARRAY
                    temp3[i] = (*c)[5][abs(i-2)][2];
                    //GREEN TO ARRAY
                    temp4[i] = (*c)[4][abs(i-2)][0];
                    //WHITE TO ARRAY
                    temp5[i] = (*c)[0][i][2];
                }
                for(i = 0; i < 3; i++) {
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
                for(i = 0; i < 3; i++) {
                    //RED TO ARRAY
                    temp2[i] = (*c)[1][abs(i-2)][0];
                    //YELLOW TO ARRAY
                    temp3[i] = (*c)[5][2][i];
                    //ORANGE TO ARRAY
                    temp4[i] = (*c)[3][abs(i-2)][2];
                    //WHITE TO ARRAY
                    temp5[i] = (*c)[0][0][i];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO WHITE
                    (*c)[0][0][i] = temp2[i];
                    //ARRAY TO RED
                    (*c)[1][i][0] = temp3[i];
                    //ARRAY TO YELLOW
                    (*c)[5][2][i] = temp4[i];
                    //ARRAY TO ORANGE
                    (*c)[3][i][2] = temp5[i];
                }
                break;
            case 5 :    //IF YELLOW == FACE
               for(i = 0; i < 3; i++) {
                    //BLUE TO ARRAY
                    temp2[i] = (*c)[2][2][i];
                    //ORANGE TO ARRAY
                    temp3[i] = (*c)[3][2][i];
                    //GREEN TO ARRAY
                    temp4[i] = (*c)[4][2][i];
                    //RED TO ARRAY
                    temp5[i] = (*c)[1][2][i];
                }
                for(i = 0; i < 3; i++) {
                    //ARRAY TO RED
                    (*c)[1][2][i] = temp2[i];
                    //ARRAY TO BLUE
                    (*c)[2][2][i] = temp3[i];
                    //ARRAY TO ORANGE
                    (*c)[3][2][i] = temp4[i];
                    //ARRAY TO GREEN
                    (*c)[4][2][i] = temp5[i];
                }
                break;
            default:
                printf("Invalid color value!\n");
                exit(0);
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