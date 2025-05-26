#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define POP_SIZE 4
#define SIZE 5

int individu[POP_SIZE][SIZE];
int individuBaru[POP_SIZE][SIZE];
int fitnessValue[POP_SIZE];
int totalFitness, bestFitness;
double percentValue[POP_SIZE];

void init_population() {
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            individu[i][j] = rand() % 2;
        }
    }
}

int fitness() {
    int jum;
    totalFitness = 0;

    for (int i = 0; i < POP_SIZE; i++) {
        jum = 0;
        for (int j = 0; j < SIZE; j++) {
            jum += individu[i][j];
        }
        fitnessValue[i] = jum;
        totalFitness += jum;
    }

    bestFitness = fitnessValue[0];
    for (int i = 1; i < POP_SIZE; i++) {
        if (fitnessValue[i] > bestFitness)
            bestFitness = fitnessValue[i];
    }

    for (int i = 0; i < POP_SIZE; i++) {
        printf("Individu[%d]: ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%d", individu[i][j]);
        }
        printf(" NF: %d\n", fitnessValue[i]);
    }

    printf("Total Fitness: %d Best Fitness: %d\n", totalFitness, bestFitness);
    return bestFitness;
}

void rouletteSelection() {
    double totalPercentFitness = 0.0;

    for (int j = 0; j < POP_SIZE; j++) {
        percentValue[j] = (fitnessValue[j] * 100.0) / totalFitness;
        printf("Percent individu[%d]: %.2f\n", j + 1, percentValue[j]);
        totalPercentFitness += percentValue[j];
    }

    for (int i = 0; i < POP_SIZE; i++) {
        double daerahPersen = 0.0;
        double random = rand() % 100;
        int k;

        for (k = 0; k < POP_SIZE; k++) {
            daerahPersen += percentValue[k];
            if (random <= daerahPersen) break;
        }

        for (int j = 0; j < SIZE; j++) {
            individuBaru[i][j] = individu[k][j];
        }
    }

    for (int i = 0; i < POP_SIZE; i++) {
        printf("Individu[%d]: ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            individu[i][j] = individuBaru[i][j];
            printf("%d", individu[i][j]);
        }
        printf("\n");
    }
}

void crossOver() {
    for (int i = 0; i < POP_SIZE; i += 2) {
        int r = rand() % SIZE;
        printf("Crossover point (random): %d\n", r);

        for (int j = 0; j < SIZE; j++) {
            if (j < r) {
                individuBaru[i][j]     = individu[i][j];
                individuBaru[i + 1][j] = individu[i + 1][j];
            } else {
                individuBaru[i][j]     = individu[i + 1][j];
                individuBaru[i + 1][j] = individu[i][j];
            }
        }
    }

    for (int i = 0; i < POP_SIZE; i++) {
        printf("Individu[%d]: ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            individu[i][j] = individuBaru[i][j];
            printf("%d", individu[i][j]);
        }
        printf("\n");
    }
}

void mutasi() {
    for (int i = 0; i < POP_SIZE; i += 2) {
        int r = rand() % SIZE;
        printf("Mutasi index (random): %d\n", r);

        for (int j = 0; j < SIZE; j++) {
            individuBaru[i][j] = individu[i][j];
        }

        individuBaru[i][r] = 1 - individu[i][r];  // Flip bit
    }

    for (int i = 0; i < POP_SIZE; i++) {
        printf("Individu[%d]: ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            individu[i][j] = individuBaru[i][j];
            printf("%d", individu[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int best;

    init_population();

    for (int iter = 0; iter < 100; iter++) {
        best = fitness();
        if (best == SIZE) break;

        rouletteSelection();
        crossOver();
        mutasi();
    }

    getch();
    return 0;
}
