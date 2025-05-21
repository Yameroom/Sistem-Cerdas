import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

if __name__ == "__main__":
    # Load the dataset
    mnist = tf.keras.datasets.fashion_mnist
    (training_images, training_labels), (test_images, test_labels) = mnist.load_data()

    # Plot an image from the dataset
    plt.imshow(training_images[0], cmap="Greys")
    plt.pause(1)  # Increase the pause time to give time for plotting
    print(training_labels[0])

    # Print the first training image with full width
    np.set_printoptions(linewidth=np.inf)
    print(training_images[0])

    # Normalize image intensities to [0, 1]
    training_images = training_images / 255.0
    test_images = test_images / 255.0

    # Create a model
    model = tf.keras.models.Sequential([
        tf.keras.layers.Flatten(input_shape=(28, 28)),
        tf.keras.layers.Dense(128, activation=tf.nn.relu),
        tf.keras.layers.Dense(10, activation=tf.nn.softmax)
    ])

    # Compile the model
    model.compile(
        optimizer=tf.optimizers.Adam(),
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"]
    )

    # Train the model
    model.fit(training_images, training_labels, epochs=5)

    # Evaluate the model on the test data
    model.evaluate(test_images, test_labels)