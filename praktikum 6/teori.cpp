#include <stdio.h>
#include <math.h>

int main() {
    // Data input: 6 titik data berdimensi 2
    float x[6][2] = {
        {0.10, 0.10},
        {0.20, 0.20},
        {0.30, 0.10},
        {0.50, 0.30},
        {0.40, 0.40},
        {0.20, 0.40}
    };

    // Bobot awal untuk dua cluster
    float w[2][2] = {
        {0.5, 0.5},
        {0.5, 0.5}
    };

    float D[2];         // Menyimpan jarak ke masing-masing cluster
    float LR = 0.6;     // Learning Rate
    int i, j, k, l;

    // === Training (Iterasi sebanyak 10 kali) ===
    for (l = 0; l < 10; l++) {
        for (k = 0; k < 6; k++) {
            // Hitung jarak dari data ke masing-masing cluster
            for (j = 0; j < 2; j++) {
                D[j] = 0.0;
                for (i = 0; i < 2; i++) {
                    D[j] += (w[j][i] - x[k][i]) * (w[j][i] - x[k][i]);
                }
            }

            // Update bobot ke cluster yang lebih dekat
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
        // Learning rate dikurangi di setiap epoch
        LR *= 0.5;
    }

    // === Output bobot akhir ===
    printf("Bobot akhir:\n");
    printf("w[0] = [%.4f, %.4f]\n", w[0][0], w[0][1]);
    printf("w[1] = [%.4f, %.4f]\n", w[1][0], w[1][1]);

    // === Mapping data ke cluster ===
    for (k = 0; k < 6; k++) {
        printf("\nTitik Data: [%.2f, %.2f]\n", x[k][0], x[k][1]);

        for (j = 0; j < 2; j++) {
            D[j] = 0.0;
            for (i = 0; i < 2; i++) {
                D[j] += (w[j][i] - x[k][i]) * (w[j][i] - x[k][i]);
            }
            printf("D(%d) = %.4f\n", j + 1, D[j]);
        }

        if (D[0] <= D[1]) {
            printf("Cluster 1\n");
        } else {
            printf("Cluster 2\n");
        }
    }

    return 0;
}
