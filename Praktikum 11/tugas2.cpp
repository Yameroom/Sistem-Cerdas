#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Fungsi keanggotaan trapezoid
float trapmf(float x, float a, float b, float c, float d) {
    if (x <= a || x >= d) return 0;
    else if (x >= b && x <= c) return 1;
    else if (x > a && x < b) return (x - a) / (b - a);
    else return (d - x) / (d - c);
}

// Fungsi keanggotaan triangular
float trimf(float x, float a, float b, float c) {
    if (x <= a || x >= c) return 0;
    else if (x == b) return 1;
    else if (x > a && x < b) return (x - a) / (b - a);
    else return (c - x) / (c - b);
}

// Fungsi minimum
float Min(float a, float b) {
    return a < b ? a : b;
}

// Fungsi defuzzifikasi dengan metode rata-rata terbobot (COA)
float defuzzify(float weights[], float outputs[], int n) {
    float num = 0.0, den = 0.0;
    for (int i = 0; i < n; ++i) {
        num += weights[i] * outputs[i];
        den += weights[i];
    }
    return (den == 0) ? 0 : num / den;
}

int main() {
    float jarak, kecepatan;
    cout << "Masukkan jarak antar kendaraan (meter): ";
    cin >> jarak;
    cout << "Masukkan kecepatan kendaraan (km/jam): ";
    cin >> kecepatan;

    // Derajat keanggotaan jarak
    float jarak_short = trapmf(jarak, 0, 0, 10, 25);
    float jarak_medium = trimf(jarak, 15, 35, 55);
    float jarak_long = trimf(jarak, 45, 65, 85);
    float jarak_very_long = trapmf(jarak, 75, 90, 100, 100);

    // Derajat keanggotaan kecepatan
    float kecepatan_low = trapmf(kecepatan, 0, 0, 20, 50);
    float kecepatan_moderate = trimf(kecepatan, 30, 65, 100);
    float kecepatan_high = trapmf(kecepatan, 80, 100, 120, 120);

    // Aturan fuzzy
    float weights[12];
    float outputs[12];

    // Output konversi:
    // no = 10, soft = 30, moderate = 60, hard = 90
    int i = 0;
    weights[i] = Min(jarak_short, kecepatan_low);     outputs[i++] = 30;
    weights[i] = Min(jarak_short, kecepatan_moderate);outputs[i++] = 90;
    weights[i] = Min(jarak_short, kecepatan_high);    outputs[i++] = 90;

    weights[i] = Min(jarak_medium, kecepatan_low);    outputs[i++] = 30;
    weights[i] = Min(jarak_medium, kecepatan_moderate);outputs[i++] = 60;
    weights[i] = Min(jarak_medium, kecepatan_high);   outputs[i++] = 90;

    weights[i] = Min(jarak_long, kecepatan_low);      outputs[i++] = 10;
    weights[i] = Min(jarak_long, kecepatan_moderate); outputs[i++] = 30;
    weights[i] = Min(jarak_long, kecepatan_high);     outputs[i++] = 60;

    weights[i] = Min(jarak_very_long, kecepatan_low);     outputs[i++] = 10;
    weights[i] = Min(jarak_very_long, kecepatan_moderate);outputs[i++] = 10;
    weights[i] = Min(jarak_very_long, kecepatan_high);    outputs[i++] = 30;

    // Defuzzifikasi
    float pengereman = defuzzify(weights, outputs, 12);

    // Cetak hasil
    cout << "\nLevel Pengereman Direkomendasikan: " << pengereman << "%" << endl;

    // Interpretasi hasil
    string interpretasi;
    if (pengereman < 15) interpretasi = "TANPA REM";
    else if (pengereman < 40) interpretasi = "PENGEREMAN RINGAN";
    else if (pengereman < 75) interpretasi = "PENGEREMAN SEDANG";
    else interpretasi = "PENGEREMAN KERAS";

    cout << "Interpretasi Kualitatif: " << interpretasi << endl;

    return 0;
}
