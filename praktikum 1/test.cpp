#include <stdio.h>
int main()
{
    int w1 = 1, w2 = 1, t = 2;
    int x1, x2, y, out;
    printf("Operasi AND\n");
    printf("Input x1 = ");
    scanf_s("%d", &x1);
    printf("Input x2 = ");
    scanf_s("%d", &x2);
    y = w1 * x1 + w2 * x2;
    if (y >= t)
        out = 1;
    else
        out = 0;
    printf("Output = %d\n", out);
    return 0;
}