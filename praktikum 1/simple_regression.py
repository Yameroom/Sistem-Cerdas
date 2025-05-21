import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from tensorflow import keras

def plot_data(x_data, y_data):
    """Fungsi untuk menampilkan plot data input."""
    fig, ax = plt.subplots()
    ax.plot(x_data, y_data, 'ro')
    plt.pause(1)
    
if __name__ == "__main__":
    # Definisikan dan kompilasi model neural network
    model = tf.keras.Sequential([
        keras.layers.Dense(units=1, input_shape=[1])
    ])
    model.compile(optimizer="sgd", loss="mean_squared_error")

    # Data input
    xs = np.array([-1.0, 0.0, 1.0, 2.0, 3.0, 4.0])
    ys = np.array([-3.0, -1.0, 1.0, 3.0, 5.0, 7.0])  # y = 2x - 1

    # Tampilkan plot data
    plot_data(xs, ys)

    # Melatih neural network
    model.fit(xs, ys, epochs=500)

    # Prediksi dengan model
    print(model.predict([10.0]))  # Hasil seharusnya mendekati 19