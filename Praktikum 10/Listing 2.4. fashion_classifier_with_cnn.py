import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np

def create_cnn_model():
    mnist = tf.keras.datasets.fashion_mnist
    (training_images, training_labels), (test_images, test_labels) = mnist.load_data()

    # Normalisasi data dan menambahkan channel dimension
    training_images = training_images.reshape(-1, 28, 28, 1) / 255.0
    test_images = test_images.reshape(-1, 28, 28, 1) / 255.0

    model = tf.keras.models.Sequential([
        tf.keras.layers.Conv2D(64, (3, 3), activation="relu", input_shape=(28, 28, 1)),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(64, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(128, activation="relu"),
        tf.keras.layers.Dense(10, activation="softmax")
    ])

    model.compile(
        optimizer="adam",
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"]
    )

    model.summary()
    model.fit(training_images, training_labels, epochs=10)
    test_loss = model.evaluate(test_images, test_labels)

    return model, test_loss


def visualizing_conv_and_max_pool(model):
    mnist = tf.keras.datasets.fashion_mnist
    (_, _), (test_images, test_labels) = mnist.load_data()

    test_images = test_images.reshape(-1, 28, 28, 1) / 255.0

    # Menampilkan 100 label pertama dalam bentuk matriks 10x10
    print(test_labels[:100].reshape(10, 10))

    f, ax_arr = plt.subplots(3, 4, figsize=(10, 10))

    first_image = 0
    second_image = 28
    third_image = 23
    convolution_number = 2  # Nomor filter (0–63)

    layer_outputs = [layer.output for layer in model.layers]
    activation_model = tf.keras.models.Model(inputs=model.layers[0].input, outputs=layer_outputs)

    for x in range(4):
        f1 = activation_model.predict(test_images[first_image].reshape(1, 28, 28, 1))[x]
        ax_arr[0, x].imshow(f1[0, :, :, convolution_number], cmap="inferno")
        ax_arr[0, x].grid(False)

        f2 = activation_model.predict(test_images[second_image].reshape(1, 28, 28, 1))[x]
        ax_arr[1, x].imshow(f2[0, :, :, convolution_number], cmap="inferno")
        ax_arr[1, x].grid(False)

        f3 = activation_model.predict(test_images[third_image].reshape(1, 28, 28, 1))[x]
        ax_arr[2, x].imshow(f3[0, :, :, convolution_number], cmap="inferno")
        ax_arr[2, x].grid(False)

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    cnn_model, cnn_test_loss = create_cnn_model()
    cnn_model.save("model-saved/category2.h5")
    visualizing_conv_and_max_pool(cnn_model)
