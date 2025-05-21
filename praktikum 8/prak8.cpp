#include "stdio.h"
#include <conio.h>
#include <math.h>

int main()
{
    int i, j, k, epoh = 0, maxIter = 10;
    float x[10][6] =
    {
        {1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 1}
    };
    int T[10] = {1, 2, 1, 1, 1, 1, 2, 2, 2, 2};
    float w[2][6], jarak[2], alpha = 0.05f;

    // Inisialisasi bobot
    jarak[0] = 0.0;
    jarak[1] = 0.0;
    for (i = 0; i < 6; i++)
    {
        w[0][i] = x[0][i];
        w[1][i] = x[1][i];
    }

    // Training
    for (i = 0; i < 10; i++)
    {
        for (j = 2; j < 10; j++)
        {
            jarak[0] = 0.0;
            jarak[1] = 0.0;
            for (k = 0; k < 6; k++)
            {
                jarak[0] = jarak[0] + (x[j][k] - w[0][k]) * (x[j][k] - w[0][k]);
                jarak[1] = jarak[1] + (x[j][k] - w[1][k]) * (x[j][k] - w[1][k]);
            }

            jarak[0] = sqrt(jarak[0]);
            jarak[1] = sqrt(jarak[1]);

            printf("jarak[0]:%f\n", jarak[0]);
            printf("jarak[1]:%f\n", jarak[1]);

            if (jarak[0] <= jarak[1])
            {
                printf("jarak[0]\n");
                if (T[j] == 1)
                {
                    for (k = 0; k < 6; k++)
                    {
                        w[0][k] = w[0][k] + alpha * (x[j][k] - w[0][k]);
                        printf("w[0][%d]:%f\n", k, w[0][k]);
                    }
                }
                else
                {
                    for (k = 0; k < 6; k++)
                    {
                        w[0][k] = w[0][k] - alpha * (x[j][k] - w[0][k]);
                        printf("w[0][%d]:%f\n", k, w[0][k]);
                    }
                }
            }
            else
            {
                printf("jarak[1]\n");
                if (T[j] == 2)
                {
                    for (k = 0; k < 6; k++)
                    {
                        w[1][k] = w[1][k] + alpha * (x[j][k] - w[1][k]);
                        printf("w[1][%d]:%f\n", k, w[1][k]);
                    }
                }
                else
                {
                    for (k = 0; k < 6; k++)
                    {
                        w[1][k] = w[1][k] - alpha * (x[j][k] - w[0][k]);
                        printf("w[1][%d]:%f\n", k, w[1][k]);
                    }
                }
            }
        }

        alpha = alpha - 0.1 * alpha;
        epoh++;
        printf("Epoh:%d\n", epoh);
    }

    // Running
    x[0][0] = 0;
    x[0][1] = 1;
    x[0][2] = 0;
    x[0][3] = 1;
    x[0][4] = 1;
    x[0][5] = 0;

    jarak[0] = 0.0;
    jarak[1] = 0.0;

    for (k = 0; k < 6; k++)
    {
        jarak[0] = jarak[0] + (x[0][k] - w[0][k]) * (x[0][k] - w[0][k]);
        jarak[1] = jarak[1] + (x[0][k] - w[1][k]) * (x[0][k] - w[1][k]);
    }

    jarak[0] = sqrt(jarak[0]);
    jarak[1] = sqrt(jarak[1]);

    printf("jarak[0]:%f\n", jarak[0]);
    printf("jarak[1]:%f\n", jarak[1]);

    if (jarak[0] <= jarak[1])
    {
        printf("Kelas 1\n");
    }
    else
    {
        printf("Kelas 2\n");
    }
}
