#include <stdio.h>

int main() {
    int w1 = 2, w2 = -1, w3 = 2, w4 = -1, w5 = 2, w6 = -1, w7 = 2, w8 = -1, w9 = 2, w10 = 2, w11 = 2, w12 = 2, t = 2;
    int x1, x2, x3, y, o1, o2, o3, o4, z1, z2, z3;

    printf("Operasi XOR 3 masukan\n");
    printf("Input x1 = ");
    scanf("%d", &x1);
    printf("Input x2 = ");
    scanf("%d", &x2);
    printf("Input x3 = ");
    scanf("%d", &x3);

    o1 = w1 * x1 + w4 * x2 + w7 * x3;
    if (o1 >= t)
        z1 = 1;
    else
        z1 = 0;

    o2 = w2 * x1 + w3 * x2 + w8 * x3;
    if (o2 >= t)
        z2 = 1;
    else
        z2 = 0;

    o3 = w5 * x1 + w6 * x2 + w9 * x3;
    if (o3 >= t)
        z3 = 1;
    else
        z3 = 0;

    o4 = w10 * z1 + w11 * z2 + w12 * z3;
    if (o4 >= t)
        y = 1;
    else
        y = 0;

    printf("Output = %d\n", y);
    return 0;
}