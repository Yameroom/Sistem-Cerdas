#include <stdio.h>

int main() {
    int w1 = 1, w2 = 1, w3 = 1, t = 3; 
    int x1, x2, x3, y, out;

    printf("Operasi AND 3 masukan\n");
    printf("Input x1 = ");
    scanf("%d", &x1);
    printf("Input x2 = ");
    scanf("%d", &x2);
    printf("Input x3 = ");
    scanf("%d", &x3);

    y = w1 * x1 + w2 * x2 + w3 * x3;
    if (y >= t)
        out = 1;
    else
        out = 0;

    printf("Output = %d\n", out);
    return 0;
}