#include <iostream>
#include <cstdlib>
#include <ctime>

double d_rand() {
    return (((double)(rand() % 32767) / 32767.0 - 0.5) * 2.0);
}

int main() {
    srand((unsigned)time(0));

    int i, j, out, ERR, y;
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}
    };
    int T[4] = {0, 1, 1, 1};
    float w[3], O, LR = 0.1, init = 0.15;

    for (i = 0; i < 3; i++) {
        w[i] = init * d_rand();
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            O = x[0][j] * w[0] + x[1][j] * w[1] + x[2][j] * w[2];
            out = (O > 0.0) ? 1 : 0;
            ERR = T[j] - out;
            if (ERR != 0) {
                w[0] = w[0] + LR * x[0][j] * ERR;
                w[1] = w[1] + LR * x[1][j] * ERR;
                w[2] = w[2] + LR * x[2][j] * ERR;
            }
        }
        std::cout << "Err: " << ERR << std::endl;
    }

    for (i = 0; i < 4; i++) {
        std::cout << "Input X1: ";
        std::cin >> x[0][0];
        std::cout << "Input X2: ";
        std::cin >> x[1][0];
        x[2][0] = 1; 
        O = x[0][0] * w[0] + x[1][0] * w[1] + x[2][0] * w[2];
        y = (O > 0.0) ? 1 : 0;
        std::cout << "Output: " << y << std::endl;
    }

    return 0;
}