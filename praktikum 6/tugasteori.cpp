#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;
const int VECTOR_SIZE = 63;
const int NUM_CLASSES = 3;
const int NUM_SAMPLES_PER_CLASS = 5;
const int NUM_EPOCHS = 100;
const double INITIAL_LEARNING_RATE = 0.1;

double euclideanDistance(const vector<double>& v1, const vector<double>& v2) {
    double sum = 0.0;
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        sum += pow(v1[i] - v2[i], 2);
    }
    return sqrt(sum);
}

class LVQ {
public:
    LVQ() {
        weightVectors.push_back(vector<double>(trainingData[0].begin(), trainingData[0].end()));
        weightVectors.push_back(vector<double>(trainingData[5].begin(), trainingData[5].end()));
        weightVectors.push_back(vector<double>(trainingData[10].begin(), trainingData[10].end()));
    }

    void train() {
        double learningRate = INITIAL_LEARNING_RATE;
        for (int epoch = 0; epoch < NUM_EPOCHS; ++epoch) {
            for (int i = 0; i < trainingData.size(); ++i) {
                const vector<double>& sample = trainingData[i];
                const string& trueClass = trainingLabels[i];

                int closestIndex = findClosestWeightVector(sample);
                string closestClass = classLabels[closestIndex];

                if (trueClass == closestClass) {
                    for (int j = 0; j < VECTOR_SIZE; ++j) {
                        weightVectors[closestIndex][j] += learningRate * (sample[j] - weightVectors[closestIndex][j]);
                    }
                } else {
                    for (int j = 0; j < VECTOR_SIZE; ++j) {
                        weightVectors[closestIndex][j] -= learningRate * (sample[j] - weightVectors[closestIndex][j]);
                    }
                }
            }

            printf("Epoch %d/%d:\n", epoch + 1, NUM_EPOCHS);
            for (int c = 0; c < NUM_CLASSES; ++c) {
                int repIndex = c * NUM_SAMPLES_PER_CLASS;
                printf("  Class %d:", c + 1);
                for (int w = 0; w < NUM_CLASSES; ++w) {
                    double dist = euclideanDistance(trainingData[repIndex], weightVectors[w]);
                    printf(" [%.4f]", dist);
                }
                printf("\n");
            }

            learningRate *= 0.95;
            printf("\n");
        }

        printf("Bobot Final:\n");
        for (int c = 0; c < NUM_CLASSES; ++c) {
            printf("  Class %d: ", c + 1);
            for (int j = 0; j < VECTOR_SIZE; ++j) {
                printf("%.4f ", weightVectors[c][j]);
            }
            printf("\n");
        }
        printf("\nPelatihan selesai.\n\n");
    }

    string classify(const vector<double>& input, vector<double>& distances) {
        distances.clear();
        for (int i = 0; i < NUM_CLASSES; ++i) {
            distances.push_back(euclideanDistance(input, weightVectors[i]));
        }
        int closestIndex = 0;
        double minDistance = distances[0];
        for (int i = 1; i < NUM_CLASSES; ++i) {
            if (distances[i] < minDistance) {
                minDistance = distances[i];
                closestIndex = i;
            }
        }
        return classLabels[closestIndex];
    }

private:
    vector<vector<double>> weightVectors;
    vector<string> classLabels = {"A", "B", "H"};

    vector<vector<double>> trainingData = {
        // 5 Dataset A
        {
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        {
            0,0,0,1,0,0,0,
            0,0,1,0,1,0,0,
            0,0,1,0,1,0,0,
            0,0,1,0,1,0,0,
            0,1,1,1,1,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1
        },
        {
            0,0,0,1,0,0,0,
            0,0,1,0,1,0,0,
            0,0,1,0,1,0,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        {
            0,0,0,1,0,0,0,
            0,0,1,0,1,0,0,
            0,1,0,0,0,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        {
            0,0,0,1,0,0,0,
            0,1,1,0,1,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        // 5 Dataset B
        {
            1,1,1,1,1,0,0,
            1,0,0,0,0,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,1,0,
            1,1,1,1,1,0,0,
            1,0,0,0,0,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,1,0,
            1,1,1,1,1,0,0
        },
        {
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,1
        },
        {
            1,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,1,0,
            1,1,1,1,1,0,0,
            1,0,0,0,0,1,0,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,0
        },
        {
            0,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            0,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            0,1,1,1,1,1,0
        },
        {
            1,1,1,1,1,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,1,0,
            1,1,1,1,1,0,0,
            1,0,0,0,0,1,0,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,0
        },
        // 5 Dataset H
        {
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,1,1,1,1,1,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        {
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1,
            1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1,
            1,1,0,0,0,1,1
        },
        {
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1,
            1,0,1,1,1,0,1,
            1,0,1,1,1,0,1,
            1,0,0,0,0,0,1,
            1,0,0,0,0,0,1
        },
        {
            1,1,0,0,0,1,1,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,1,1,1,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            1,1,0,0,0,1,1
        },
        {
            1,1,1,0,1,1,1,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,1,1,1,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            0,1,0,0,0,1,0,
            1,1,1,0,1,1,1
        }
    };

    vector<string> trainingLabels = {
        "A", "A", "A", "A", "A",
        "B", "B", "B", "B", "B",
        "H", "H", "H", "H", "H"
    };

    int findClosestWeightVector(const vector<double>& sample) {
        double minDistance = euclideanDistance(sample, weightVectors[0]);
        int closestIndex = 0;
        for (int i = 1; i < NUM_CLASSES; ++i) {
            double distance = euclideanDistance(sample, weightVectors[i]);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = i;
            }
        }
        return closestIndex;
    }
};

void testLVQ(LVQ& lvq, float testing_data[3][VECTOR_SIZE], const vector<string>& expectedLabels) {
    for (int i = 0; i < 3; ++i) {
        vector<double> sample(testing_data[i], testing_data[i] + VECTOR_SIZE);
        vector<double> distances;
        string predictedClass = lvq.classify(sample, distances);
        printf("Sampel %d:\n", i + 1);
        printf("  Diharapkan: '%s'\n", expectedLabels[i].c_str());
        printf("  Dengan jarak:");
        for (int j = 0; j < NUM_CLASSES; ++j) {
            printf(" [%.4f]", distances[j]);
        }
        printf("\n");
        printf("  Hasil Prediksi: '%s'\n\n", predictedClass.c_str());
    }
}

int main() {
    LVQ lvq;
    printf("Melatih model LVQ...\n");
    lvq.train();

    float testing_data[3][VECTOR_SIZE] = {
        // Huruf H
        {1,1,0,0,0,1,1,
         1,1,0,0,0,1,1,
         1,1,0,0,0,1,1,
         1,1,0,0,0,1,1,
         1,1,1,1,1,1,1,
         1,1,1,1,1,1,1,
         1,1,0,0,0,1,1,
         1,1,0,0,0,1,1,
         1,1,0,0,0,1,1},
        // Huruf A
        {0,0,0,1,0,0,0,
         0,0,1,0,1,0,0,
         0,1,0,0,0,1,0,
         0,1,0,0,0,1,0,
         0,1,1,1,1,1,0,
         0,1,1,1,1,1,0,
         0,1,0,0,0,1,0,
         0,1,0,0,0,1,1,
         1,1,0,0,0,1,1},
        // Huruf B
        {1,0,1,1,1,0,0,
         1,0,0,0,0,1,0,
         1,0,0,0,0,0,1,
         1,0,0,0,0,1,0,
         1,1,1,1,1,0,0,
         1,0,0,0,0,1,0,
         1,0,0,0,0,0,1,
         1,1,0,0,0,0,1,
         1,0,1,1,1,1,0}
    };

    vector<string> expectedLabels = {"H", "A", "B"};

    printf("Hasil pengujian:\n");
    testLVQ(lvq, testing_data, expectedLabels);

    return 0;
}