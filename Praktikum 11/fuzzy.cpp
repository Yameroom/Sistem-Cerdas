#include <conio.h>
#include <cstdio>

float MFx(float a, float b, float z) {
    float hasil_MFx;
    if ((z >= a) && (z < b)) hasil_MFx = (b - z) / (b - a);
    if (z <= a) hasil_MFx = 1;
    if (z >= b) hasil_MFx = 0;
    return hasil_MFx;
}

float MFy(float a, float b, float z) {
    float hasil_MFy;
    if ((z >= a) && (z < b)) hasil_MFy = (z - a) / (b - a);
    if (z <= a) hasil_MFy = 0;
    if (z >= b) hasil_MFy = 1;
    return hasil_MFy;
}

float Min(float a, float b) {
    float hasil_min;
    if (a < b)
        hasil_min = a;
    else
        hasil_min = b;
    return hasil_min;
}

int main() {
    float u1x, u2x, u3x, u1y, u2y, u3y;
    float minR1, minR2, minR3, minR4;
    float proR1, proR2, proR3, proR4;

    // Fuzzyfication
    float permintaan = 4000;
    float persediaan = 300;

    printf("Persoalan:\n");
    printf("Permintaan: %.0f\n", permintaan);
    printf("Persediaan: %.0f\n", persediaan);
    printf("Berapa jumlah produksi?\n");

    u1x = MFx(1000, 5000, permintaan); // permintaan turun
    printf("Fungsi keanggotaan permintaan turun: %.2f\n", u1x);

    u1y = MFy(1000, 5000, permintaan); // permintaan naik
    printf("Fungsi keanggotaan permintaan naik: %.2f\n", u1y);

    u2x = MFx(100, 600, persediaan); // persediaan sedikit
    printf("Fungsi keanggotaan persediaan sedikit: %.2f\n", u2x);

    u2y = MFy(100, 600, persediaan); // persediaan banyak
    printf("Fungsi keanggotaan persediaan banyak: %.2f\n", u2y);

    // Rule 1: IF Permintaan TURUN And Persediaan BANYAK THEN Produksi BERKURANG
    minR1 = Min(u1x, u2y);
    printf("Minimum Permintaan TURUN And Persediaan BANYAK: %.2f\n", minR1);
    proR1 = 7000 - minR1 * 5000;
    printf("Produksi berkurang: %.0f\n", proR1);

    // Rule 2: IF Permintaan TURUN And Persediaan SEDIKIT THEN Produksi BERKURANG
    minR2 = Min(u1x, u2x);
    printf("Minimum Permintaan TURUN And Persediaan SEDIKIT: %.2f\n", minR2);
    proR2 = 7000 - minR2 * 5000;
    printf("Produksi berkurang: %.0f\n", proR2);

    // Rule 3: IF Permintaan NAIK And Persediaan BANYAK THEN Produksi BERTAMBAH
    minR3 = Min(u1y, u2y);
    printf("Minimum Permintaan NAIK And Persediaan BANYAK: %.2f\n", minR3);
    proR3 = 2000 + minR3 * 5000;
    printf("Produksi bertambah: %.0f\n", proR3);

    // Rule 4: IF Permintaan NAIK And Persediaan SEDIKIT THEN Produksi BERTAMBAH
    minR4 = Min(u1y, u2x);
    printf("Minimum Permintaan NAIK And Persediaan SEDIKIT: %.2f\n", minR4);
    proR4 = 2000 + minR4 * 5000;
    printf("Produksi bertambah: %.0f\n", proR4);

    // Defuzzifikasi (Metode Center of Area)
    float pembilang = minR1 * proR1 + minR2 * proR2 + minR3 * proR3 + minR4 * proR4;
    float penyebut = minR1 + minR2 + minR3 + minR4;
    float hasil_COA = pembilang / penyebut;

    printf("Produksi: %.0f\n", hasil_COA);
}
