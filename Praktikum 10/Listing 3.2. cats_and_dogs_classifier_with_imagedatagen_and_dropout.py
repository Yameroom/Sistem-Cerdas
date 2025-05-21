import os
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing import image as keras_image

# Constants
IMG_HEIGHT = 150
IMG_WIDTH = 150
BATCH_SIZE = 20

# Plot training history
def plot_history(train, val, title):
    epochs = range(len(train))
    plt.figure()
    plt.plot(epochs, train, label="train")
    plt.plot(epochs, val, label="val")
    plt.title(title)
    plt.legend(loc="best")
    plt.show()

# Create CNN model
def create_cnn_model(input_shape=(150, 150, 3)):
    model = tf.keras.models.Sequential([
        tf.keras.layers.Input(shape=input_shape),
        tf.keras.layers.Conv2D(32, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(64, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(128, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(128, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Dropout(0.5),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(512, activation="relu"),
        tf.keras.layers.Dense(1, activation="sigmoid")
    ])
    model.compile(
        loss="binary_crossentropy",
        optimizer=Adam(learning_rate=1e-4),
        metrics=["accuracy"]
    )
    model.summary()
    return model

# Classify individual images
def classify_images(fn_arr, model):
    for fn in fn_arr:
        path = os.path.join("datasets", fn)

        if not os.path.exists(path):
            print(f"Warning: File {path} not found.")
            continue

        img = keras_image.load_img(path, target_size=(150, 150))
        x = keras_image.img_to_array(img)
        x = np.expand_dims(x, axis=0) / 255.0

        prediction = model.predict(x)
        print(f"File: {fn}, Prediction score: {prediction[0][0]}")

        if prediction[0][0] > 0.5:
            print(f"{fn} is a dog")
        else:
            print(f"{fn} is a cat")

# Build augmentation pipeline
def build_augmentation_pipeline(img_height, img_width):
    data_augmentation = tf.keras.Sequential([
        layers.RandomFlip("horizontal", input_shape=(img_height, img_width, 3)),
        layers.RandomRotation(factor=0.11, fill_mode="nearest"),
        layers.RandomZoom(height_factor=0.2, width_factor=0.2, fill_mode="nearest"),
        layers.RandomTranslation(height_factor=0.2, width_factor=0.2, fill_mode="nearest")
    ])
    return data_augmentation

# Image preprocessing
def process_path(file_path):
    img = tf.io.read_file(file_path)
    img = tf.io.decode_image(img, channels=3, expand_animations=False)
    img = tf.image.resize(img, [IMG_HEIGHT, IMG_WIDTH])
    return img

# Dataset configuration
def configure_for_performance(ds, shuffle=False, augment=False):
    ds = ds.cache()

    if shuffle:
        ds = ds.shuffle(buffer_size=1000)

    ds = ds.batch(BATCH_SIZE)

    if augment:
        augmentation_pipeline = build_augmentation_pipeline(IMG_HEIGHT, IMG_WIDTH)
        ds = ds.map(lambda x, y: (augmentation_pipeline(x, training=True), y),
                    num_parallel_calls=tf.data.AUTOTUNE)

    ds = ds.map(lambda x, y: (tf.cast(x, tf.float32) / 255.0, tf.cast(y, tf.float32)),
                num_parallel_calls=tf.data.AUTOTUNE)
    ds = ds.prefetch(buffer_size=tf.data.AUTOTUNE)
    return ds

# Load and prepare datasets
def do_data_preprocessing_tfdata(train_dir, validation_dir, aug=False):
    train_ds = tf.keras.utils.image_dataset_from_directory(
        train_dir,
        labels='inferred',
        label_mode='binary',
        image_size=(IMG_HEIGHT, IMG_WIDTH),
        interpolation='nearest',
        batch_size=None,
        shuffle=True,
        seed=123
    )

    val_ds = tf.keras.utils.image_dataset_from_directory(
        validation_dir,
        labels='inferred',
        label_mode='binary',
        image_size=(IMG_HEIGHT, IMG_WIDTH),
        interpolation='nearest',
        batch_size=None,
        shuffle=False
    )

    class_names = train_ds.class_names
    print("Class names:", class_names)

    train_ds = configure_for_performance(train_ds, shuffle=True, augment=aug)
    val_ds = configure_for_performance(val_ds, shuffle=False, augment=False)
    return train_ds, val_ds

# Main execution block
if __name__ == "__main__":
    base_dir = "datasets/cats_and_dogs_filtered"
    train_dir = os.path.join(base_dir, "train")
    validation_dir = os.path.join(base_dir, "validation")
    train_cats_dir = os.path.join(train_dir, "cats")
    train_dogs_dir = os.path.join(train_dir, "dogs")
    validation_cats_dir = os.path.join(validation_dir, "cats")
    validation_dogs_dir = os.path.join(validation_dir, "dogs")

    if not os.path.exists(train_dir) or not os.path.exists(validation_dir):
        print(f"Error: Dataset directory {base_dir} or subdirectories not found.")
        exit()

    if not all(os.path.exists(d) for d in [train_cats_dir, train_dogs_dir, validation_cats_dir, validation_dogs_dir]):
        print("Error: One or more subdirectories (cats/dogs) for train/validation not found.")
        exit()

    try:
        print(f"Training cat images: {len(os.listdir(train_cats_dir))}")
        print(f"Training dog images: {len(os.listdir(train_dogs_dir))}")
        print(f"Validation cat images: {len(os.listdir(validation_cats_dir))}")
        print(f"Validation dog images: {len(os.listdir(validation_dogs_dir))}")

        train_generator, validation_generator = do_data_preprocessing_tfdata(
            train_dir, validation_dir, aug=True
        )

        cnn_model = create_cnn_model(input_shape=(IMG_HEIGHT, IMG_WIDTH, 3))

        history = cnn_model.fit(
            train_generator,
            epochs=100,
            validation_data=validation_generator,
            verbose=1
        )

        acc = history.history["accuracy"]
        val_acc = history.history["val_accuracy"]
        loss = history.history["loss"]
        val_loss = history.history["val_loss"]

        plot_history(acc, val_acc, "Training and validation accuracy")
        plot_history(loss, val_loss, "Training and validation loss")

        test_images = [
            "cat-2083492_only_head.jpg",
            "cat-1146504_640.jpg",
            "dog-3846767_640.jpg",
            "dog-3388069_640.jpg"
        ]

        classify_images(test_images, cnn_model)

    except FileNotFoundError as e:
        print(f"FileNotFoundError occurred: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")