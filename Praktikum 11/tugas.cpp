#include <stdio.h>
#include <math.h>
#include <string.h>

float shortMF_dis(float x) {
    if (x <= 2) return 1;
    else if (x > 2 && x < 6) return (6 - x) / 4.0;
    else return 0;
}

float mediumMF_dis(float x) {
    if (x >= 2 && x < 6) return (x - 2) / 4.0;
    else if (x >= 6 && x <= 10) return (10 - x) / 4.0;
    else return 0;
}

float longMF_dis(float x) {
    if (x >= 6 && x < 10) return (x - 6) / 4.0;
    else if (x >= 10 && x <= 14) return (14 - x) / 4.0;
    else return 0;
}

float veryLongMF_dis(float x) {
    if (x >= 10 && x < 14) return (x - 10) / 4.0;
    else if (x >= 14) return 1;
    else return 0;
}

float lowMF_sp(float y) {
    if (y <= 20) return 1;
    else if (y > 20 && y < 40) return (40 - y) / 20.0;
    else return 0;
}

float mediumMF_sp(float y) {
    if (y >= 20 && y < 40) return (y - 20) / 20.0;
    else if (y >= 40 && y <= 60) return (60 - y) / 20.0;
    else return 0;
}

float highMF_sp(float y) {
    if (y >= 40 && y < 60) return (y - 40) / 20.0;
    else if (y >= 60) return 1;
    else return 0;
}

float minf(float a, float b) {
    return (a < b) ? a : b;
}

int main() {
    const float B0 = 0, B1 = 25, B2 = 50, B3 = 100;

    float testData[][2] = {
        {1,75}, {2,80}, {4,10}, {5,40}, {16,10}, {12,40}, {13,35},
        {50,50}, {8.9,48.5}, {30,25.8}, {11,22.5}, {9.5,44}
    };
    int numTests = sizeof(testData) / sizeof(testData[0]);

    for (int t = 0; t < numTests; ++t) {
        float d = testData[t][0];
        float v = testData[t][1];

        float dx_s = shortMF_dis(d);
        float dx_m = mediumMF_dis(d);
        float dx_l = longMF_dis(d);
        float dx_v = veryLongMF_dis(d);

        float dy_l = lowMF_sp(v);
        float dy_m = mediumMF_sp(v);
        float dy_h = highMF_sp(v);

        float a[12], z[12];
        a[0] = minf(dy_l, dx_s);   z[0] = B2;
        a[1] = minf(dy_l, dx_m);   z[1] = B1;
        a[2] = minf(dy_l, dx_l);   z[2] = B0;
        a[3] = minf(dy_l, dx_v);   z[3] = B0;

        a[4] = minf(dy_m, dx_s);   z[4] = B3;
        a[5] = minf(dy_m, dx_m);   z[5] = B2;
        a[6] = minf(dy_m, dx_l);   z[6] = B1;
        a[7] = minf(dy_m, dx_v);   z[7] = B0;

        a[8] = minf(dy_h, dx_s);   z[8] = B3;
        a[9] = minf(dy_h, dx_m);   z[9] = B3;
        a[10]= minf(dy_h, dx_l);   z[10]= B2;
        a[11]= minf(dy_h, dx_v);   z[11]= B1;

        float sum_a = 0, sum_az = 0;
        for (int i = 0; i < 12; ++i) {
            sum_a += a[i];
            sum_az += a[i] * z[i];
        }

        float out = (sum_a > 1e-6) ? sum_az / sum_a : B0;

        const char *label;
        if (out < B1) label = "TANPA REM";
        else if (out < B2) label = "RINGAN";
        else if (out < B3) label = "SEDANG";
        else label = "KERAS";

        printf("Data uji ke-%d: Jarak = %.2f m, Kecepatan = %.2f km/jam\n", t+1, d, v);
        printf(">> Tingkat Pengereman: %.2f (%s)\n\n", out, label);
    }

    return 0;
}