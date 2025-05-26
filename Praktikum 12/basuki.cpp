#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const string target = "BASUKI";
const string karakter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int jumlah_populasi = 100;
const float mutation_rate = 0.2;

struct Individu {
    string angka;
    int fitness;

    Individu(string s) {
        angka = s;
        fitness = hitungFitness(s);
    }

    static int hitungFitness(const string& s) {
        int f = 0;
        for (int i = 0; i < target.size(); ++i) {
            if (s[i] == target[i]) {
                f += 26;
            } else {
                f += 26 - abs(s[i] - target[i]);
            }
        }
        return f;
    }
};

bool bandingFitness(const Individu& a, const Individu& b) {
    return a.fitness > b.fitness;
}

string randomString(int length) {
    string result = "";
    for (int i = 0; i < length; ++i) {
        result += karakter[rand() % karakter.length()];
    }
    return result;
}

Individu crossover(const Individu& parent1, const Individu& parent2) {
    string child = "";
    for (int i = 0; i < parent1.angka.size(); ++i) {
        if ((rand() % 2) == 0)
            child += parent1.angka[i];
        else
            child += parent2.angka[i];
    }

    for (int i = 0; i < child.size(); ++i) {
        if (((float)rand() / RAND_MAX) < mutation_rate) {
            child[i] = karakter[rand() % karakter.length()];
        }
    }

    return Individu(child);
}

int main() {
    srand(time(0));
    vector<Individu> populasi;

    for (int i = 0; i < jumlah_populasi; ++i) {
        populasi.push_back(Individu(randomString(target.size())));
    }

    int generasi = 1;

    while (true) {
        for (auto& individu : populasi) {
            individu.fitness = Individu::hitungFitness(individu.angka);
        }

        sort(populasi.begin(), populasi.end(), bandingFitness);

        cout << generasi << " "
             << populasi[0].angka
             << " >> Fitness = " << populasi[0].fitness << endl;

        if (populasi[0].angka == target) {
            cout << ">> Selesai dalam generasi ke-" << generasi << endl;
            break;
        }

        vector<Individu> new_populasi;

        for (int i = 0; i < 10; ++i) {
            new_populasi.push_back(populasi[i]);
        }

        while (new_populasi.size() < jumlah_populasi) {
            int idx1 = rand() % 50;
            int idx2 = rand() % 50;
            Individu anak = crossover(populasi[idx1], populasi[idx2]);
            new_populasi.push_back(anak);
        }

        populasi = new_populasi;
        generasi++;
    }

    return 0;
}
