#include <stdio.h>

int main() {
    int w1 = 2, w2 = -1, w3 = 2, w4 = -1, w5 = 2, w6 = 2, t = 2;
    int x1, x2, y, o1, o2, o3, z1, z2;

    printf("Operasi XOR\n");
    printf("Input x1 = ");
    scanf("%d", &x1);
    printf("Input x2 = ");
    scanf("%d", &x2);

    o1 = w1 * x1 + w4 * x2;
    if (o1 >= t)
        z1 = 1;
    else
        z1 = 0;

    o2 = w2 * x1 + w3 * x2;
    if (o2 >= t)
        z2 = 1;
    else
        z2 = 0;

    o3 = w5 * z1 + w6 * z2;
    if (o3 >= t)
        y = 1;
    else
        y = 0;

    printf("Output = %d\n", y);
    return 0;
}