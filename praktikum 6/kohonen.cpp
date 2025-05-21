#include "stdio.h"
#include <conio.h>
#include <math.h>
int main() {
    float w[2][4] = { {0.2,0.6,0.5,0.9},
                     {0.8,0.4,0.7,0.3} };
    int x[4][4] = { {1,1,0,0},
                   {0,0,0,1},
                   {1,0,0,0},
                   {0,0,1,1} };
    float D[2];
    int i, j, k, l;
    float LR = 0.6;
    //training
    for (l = 0; l < 100; l++) {
        for (k = 0; k < 4; k++) {
            for (j = 0; j < 2; j++) {
                D[j] = 0.0;
                for (i = 0; i < 4; i++) {
                    D[j] = D[j] + (w[j][i] - x[k][i]) * (w[j][i] - x[k][i]);
                }
            }
            if (D[0] < D[1]) {
                for (i = 0; i < 4; i++) {
                    w[0][i] = w[0][i] + LR * (x[k][i] - w[0][i]);
                }
            }
            else {
                for (i = 0; i < 4; i++) {
                    w[1][i] = w[1][i] + LR * (x[k][i] - w[1][i]);
                }
            }
        }
        LR = 0.5 * LR;
    }
    //mapping cluster 
    x[0][0] = 1; x[0][1] = 1; x[0][2] = 0; x[0][3] = 0;
    for (j = 0; j < 2; j++) {
        D[j] = 0.0;
        for (i = 0; i < 4; i++) {
            D[j] = D[j] + sqrt((w[j][i] - x[0][i]) * (w[j][i] - x[0][i]));
        }
        printf("D(%d) = %.2f\n", (j + 1), D[j]);
    }
    if (D[0] < D[1]) {
        printf("Cluster 1");
    }
    else {
        printf("Cluster 2");
    }
}