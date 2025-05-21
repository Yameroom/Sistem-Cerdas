#include "stdio.h"
#include <math.h>

int main() {
    float x[6][2] = {
        {0.10, 0.10},
        {0.20, 0.20},
        {0.30, 0.10},
        {0.50, 0.30},
        {0.40, 0.40},
        {0.20, 0.40}
    };

    float w[2][2] = { {0.5, 0.5}, {0.5, 0.5} };
    float D[2];
    int i, j, k, l;
    float LR = 0.6;

    // Training
    for (l = 0; l < 10; l++) {
        for (k = 0; k < 6; k++) {
            for (j = 0; j < 2; j++) {
                D[j] = 0.0;
                for (i = 0; i < 2; i++) {
                    D[j] += (w[j][i] - x[k][i]) * (w[j][i] - x[k][i]);
                }
            }

            if (D[0] < D[1]) {
                for (i = 0; i < 2; i++) {
                    w[0][i] += LR * (x[k][i] - w[0][i]);
                }
            } else {
                for (i = 0; i < 2; i++) {
                    w[1][i] += LR * (x[k][i] - w[1][i]);
                }
            }
        }
        LR *= 0.5;
    }

    printf("w[0] = [%.4f, %.4f]\n", w[0][0], w[0][1]);
    printf("w[1] = [%.4f, %.4f]\n", w[1][0], w[1][1]);

    // Mapping Cluster
    float test[2] = {0.10, 0.10};
    for (j = 0; j < 2; j++) {
        D[j] = 0.0;
        for (i = 0; i < 2; i++) {
            D[j] += (w[j][i] - test[i]) * (w[j][i] - test[i]);
        }
        printf("D(%d) = %.4f\n", j + 1, D[j]);
    }

    if (D[0] <= D[1]) {
        printf("Cluster 1\n");
    } else {
        printf("Cluster 2\n");
    }

    return 0;
}