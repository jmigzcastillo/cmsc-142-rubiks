#include <stdio.h>
#define WHITE 0
#define RED 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define YELLOW 5
#define CLOCKWISE 0

int main() {
    char cube[6][3][3];

    return 0;
}

void rotateCube(char ***c, int color, int orientation) {
    int neighbors[6][4] = { //CLOCKWISE
        {4, 3, 2, 1} ,      //neighbors of 0 WHITE
        {0, 2, 5, 4} ,      //neighbors of 1 RED
        {0, 3, 5, 1} ,      //neighbors of 2 BLUE 
        {0, 4, 5, 2} ,      //neighbors of 3 ORANGE
        {0, 1, 5, 3} ,      //neighbors of 4 GREEN
        {4, 1, 2, 3}        //neighbors of 5 YELLOW
    }

    int temp[3][3] = c[color];
    int temp2[3];
    int temp3[3];
    
    if(orientation) { //CLOCKWISE
        //switch elements inside the 3x3 matrix first
        for(int i = 0; i < 3; i++) {
            c[color][i][2] = temp[0][i];
            c[color][2][i] = temp[i][2];
            c[color][i][0] = temp[2][i];
            c[color][0][i] = temp[i][0];
        }

        int next;

        for(int j = 0; j < 4; j++) {
            if(j+1>3) {
                next = 0;
            } else {
                next = j+1;
            }

            switch(color) {
                case 0 :    //IF WHITE == FACE
                    for(int i = 0; i < 3; i++) {
                        //GREEN TO ORANGE
                        temp2[i] = color[3][0][i];
                        color[3][0][i] = color[4][0][i];
                        //ORANGE TO BLUE
                        temp3[i] = color[2][0][i];
                        color[2][0][i] = temp2[i];
                        //BLUE TO RED
                        temp2[i] = color[1][0][i];
                        color[1][0][i] = temp3[i];
                        //RED TO GREEN
                        color[4][0][i] = temp2[i];
                    }
                    break;
                case 1 :    //IF RED == FACE
                    for(int i = 0; i < 3; i++) {
                        //WHITE TO BLUE
                        temp2[i] = color[2][i][0];
                        color[2][i][0] = color[0][i][0];
                        //BLUE TO YELLOW
                        temp3[i] = color[5][i][2];
                        color[5][abs(i-2)][2] = temp2[i];
                        //YELLOW TO GREEN
                        temp2[i] = color[4][i][2];
                        color[4][i][2] = temp3[i];
                        //GREEN TO WHITE
                        color[0][abs(i-2)][0] = temp2[i];
                    }
                    break;
                case 2 :    //IF BLUE == FACE
                    for(int i = 0; i < 3; i++) {
                        //WHITE TO ORANGE
                        temp2[i] = color[3][i][0];
                        color[3][i][0] = color[0][2][i];
                        //ORANGE TO YELLOW
                        temp3[i] = color[5][2][i];
                        color[5][2][i] = temp2[i];
                        //YELLOW TO RED
                        temp2[i] = color[1][i][2];
                        color[1][abs(i-2)][2] = temp3[i];
                        //RED TO WHITE
                        color[0][2][abs(i-2)] = temp2[i];
                    }
                    break;
                case 3 :    //IF ORANGE == FACE
                    for(int i = 0; i < 3; i++) {
                        //WHITE TO GREEN
                        temp2[i] = color[4][i][0];
                        color[4][i][0] = color[0][abs(i-2)][2];
                        //GREEN TO YELLOW
                        temp3[i] = color[5][i][0];
                        color[5][i][0] = temp2[i];
                        //YELLOW TO BLUE
                        temp2[i] = color[2][i][2];
                        color[2][abs(i-2)][2] = temp3[i];
                        //BLUE TO WHITE
                        color[0][i][2] = temp2[i];
                    }
                    break;
                case 4 :    //IF GREEN == FACE
                    for(int i = 0; i < 3; i++) {
                        //WHITE TO RED
                        temp2[i] = color[1][i][0];
                        color[1][i][0] = color[0][0][abs(i-2)];
                        //RED TO YELLOW
                        temp3[i] = color[5][i][0];
                        color[5][abs(i-2)][0] = temp2[i];
                        //YELLOW TO ORANGE
                        temp2[i] = color[2][i][2];
                        color[2][i][2] = temp3[i];
                        //ORANGE TO WHITE
                        color[0][i][2] = temp2[i];
                    }
                    break;
                case 5 :    //IF YELLOW == FACE
                    for(int i = 0; i < 3; i++) {
                        //GREEN TO RED
                        temp2[i] = color[1][2][i];
                        color[1][2][i] = color[4][2][i];
                        //RED TO BLUE
                        temp3[i] = color[2][2][i];
                        color[2][2][i] = temp2[i];
                        //BLUE TO ORANGE
                        temp2[i] = color[3][2][i];
                        color[3][2][i] = temp3[i];
                        //ORANGE TO GREEN
                        color[4][2][i] = temp2[i];
                    }
                    break;
            }

        }

        for(int i = 2; i < -1; i--) {
            
        }
    } else {

    }
}