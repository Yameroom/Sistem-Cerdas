#include <stdio.h>
#include <math.h>

int main() {
    float w[2][2] = { {0.5, 0.5},
                      {0.5, 0.5} };
    float x[6][2] = { {0.1, 0.1},
                      {0.2, 0.2},
                      {0.3, 0.1},
                      {0.5, 0.3},
                      {0.4, 0.4},
                      {0.2, 0.4} };
    float D[2];
    int i, j, k, l;
    float LR = 0.6;

    // Training
    for (l = 0; l < 10; l++) {  
        for (k = 0; k < 6; k++) {  
            for (j = 0; j < 2; j++) {
                D[j] = 0.0;
                for (i = 0; i < 2; i++) {  
                    D[j] = D[j] + (w[j][i] - x[k][i]) * (w[j][i] - x[k][i]);
                }
            }
            if (D[0] < D[1]) {
                for (i = 0; i < 2; i++) {
                    w[0][i] = w[0][i] + LR * (x[k][i] - w[0][i]);
                }
            } else {
                for (i = 0; i < 2; i++) {
                    w[1][i] = w[1][i] + LR * (x[k][i] - w[1][i]);
                }
            }
        }
        LR = 0.5 * LR; 
    }

    // Testing cluster
    char input;
    do {
        printf("\nMasukkan vektor input (format: a b) atau 'q' untuk keluar: ");
        if (scanf("%f %f", &x[0][0], &x[0][1]) == 2) {
            // Mapping cluster
            for (j = 0; j < 2; j++) {
                D[j] = 0.0;
                for (i = 0; i < 2; i++) {
                    D[j] = D[j] + sqrt((w[j][i] - x[0][i]) * (w[j][i] - x[0][i]));
                }
                printf("D(%d) = %.2f\n", (j + 1), D[j]);
            }
            if (D[0] < D[1]) {
                printf("Cluster 1\n");
            } else {
                printf("Cluster 2\n");
            }
        } else {
            scanf(" %c", &input);  
            if (input == 'q' || input == 'Q') {
                break;  
            } else {
                printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1); 

    printf("Program selesai.\n");
    return 0;
}