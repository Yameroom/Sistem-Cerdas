#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

/*--------------------- random function -----------------------*/
float d_rand(void) {
    return ((float)(((rand() % 32767) / 32767.0 - 0.5) * 2.0));
}

/*-------------------------- sigmoid ------------------------------*/
float sigmoid(float u) {
    return ((float)(1.0 / (1.0 + exp(-u))));
}

int main() {
    int i, j, k, p, l;
    float z, delta_o, delta_h[2], g1, f1[2];
    float y[3] = {0.0, 0.0, 1.0};
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}
    };
    float t[4] = {0, 1, 1, 0};
    float w[2][3], O[2], s[3], LR = 0.1f, init = 0.15f, error;

    // Inisialisasi bobot
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 3; i++) {
            w[j][i] = init * d_rand();
        }
    }
    for (j = 0; j < 3; j++) {
        s[j] = init * d_rand();
    }

    // Training
    for (l = 0; l < 15000; l++) {
        error = 0.0;
        for (p = 0; p < 4; p++) {
            for (j = 0; j < 2; j++) {
                O[j] = 0.0;
                for (i = 0; i < 3; i++) {
                    O[j] += x[i][p] * w[j][i];
                }
                y[j] = sigmoid(O[j]);
            }
            O[0] = 0.0;
            for (i = 0; i < 3; i++) {
                O[0] += y[i] * s[i];
            }
            z = sigmoid(O[0]);

            g1 = z * (1 - z);
            delta_o = (t[p] - z) * g1;
            for (j = 0; j < 2; j++) {
                f1[j] = y[j] * (1 - y[j]);
            }
            for (j = 0; j < 2; j++) {
                delta_h[j] = f1[j] * delta_o * s[j];
            }
            for (i = 0; i < 3; i++) {
                s[i] += LR * delta_o * y[i];
            }
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 3; i++) {
                    w[j][i] += LR * delta_h[j] * x[i][p];
                }
            }
            error += ((t[p] - z) * (t[p] - z)) / 2;
        }
        error /= 4;
        printf("Iterasi: %d Error: %f\n", l, error);
        if (error < 0.01) break;
    }

    // Running
    char ch;
    for (;;) {
        printf("Input X1:");
        scanf("%d", &x[0][0]);
        printf("Input X2:");
        scanf("%d", &x[1][0]);
        for (j = 0; j < 2; j++) {
            O[j] = 0.0;
            for (i = 0; i < 3; i++) {
                O[j] += x[i][0] * w[j][i];
            }
            y[j] = sigmoid(O[j]);
        }
        O[0] = 0.0;
        for (i = 0; i < 3; i++) {
            O[0] += y[i] * s[i];
        }
        z = sigmoid(O[0]);
        printf("z: %f\n", z);
        if (z < 0.5)
            printf("output: 0\n");
        else
            printf("output: 1\n");
        ch = getch();
        if (ch == 'e') break;
    }

    return 0;
}