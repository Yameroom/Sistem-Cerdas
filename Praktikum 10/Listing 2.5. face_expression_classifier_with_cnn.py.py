import os
import zipfile
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.preprocessing import image as keras_image


# Callback untuk menghentikan training jika sudah mencapai akurasi tertentu
class MyCallback(tf.keras.callbacks.Callback):
    def __init__(self, desired_accuracy):
        super(MyCallback, self).__init__()
        self.DESIRED_ACCURACY = desired_accuracy

    def on_epoch_end(self, epoch, logs=None):
        if logs is None:
            logs = {}
        if logs.get("accuracy") > self.DESIRED_ACCURACY:
            print(f"\nReached {self.DESIRED_ACCURACY * 100:.2f}% accuracy so cancelling training!")
            self.model.stop_training = True


# Ekstraksi dataset
def load_dataset(zip_file_path, extracted_zip_file_path, train_happy_dir, train_sad_dir):
    if not os.path.exists(extracted_zip_file_path):
        os.makedirs(extracted_zip_file_path, exist_ok=True)
        zip_ref = zipfile.ZipFile(zip_file_path, "r")
        zip_ref.extractall(extracted_zip_file_path)
        zip_ref.close()

    train_happy_names = os.listdir(train_happy_dir)
    train_sad_names = os.listdir(train_sad_dir)

    print(train_happy_names[:10])
    print(train_sad_names[:10])
    print(f"Total training happy images: {len(train_happy_names)}")
    print(f"Total training sad images: {len(train_sad_names)}")
    return train_happy_names, train_sad_names


# Preprocessing data dan membuat generator
def do_data_preprocessing(dataset_dir):
    train_datagen = ImageDataGenerator(rescale=1./255, validation_split=0.2)

    train_generator = train_datagen.flow_from_directory(
        dataset_dir,
        target_size=(150, 150),
        batch_size=8,
        class_mode="binary",
        subset='training'
    )

    validation_generator = train_datagen.flow_from_directory(
        dataset_dir,
        target_size=(150, 150),
        batch_size=8,
        class_mode="binary",
        subset='validation'
    )

    return train_generator, validation_generator


# Arsitektur model CNN
def create_cnn_model():
    model = tf.keras.models.Sequential([
        tf.keras.layers.Conv2D(16, (3, 3), activation="relu", input_shape=(150, 150, 3)),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(32, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Conv2D(64, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(2, 2),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(512, activation="relu"),
        tf.keras.layers.Dense(1, activation="sigmoid")
    ])

    model.compile(
        loss="binary_crossentropy",
        optimizer=Adam(learning_rate=0.001),
        metrics=["accuracy"]
    )

    model.summary()
    return model


# Menampilkan contoh gambar happy & sad
def plot_training_images(train_happy_dir, train_sad_dir, train_happy_names, train_sad_names):
    plt.figure(figsize=(16, 16))
    img_index = 0

    next_happy_img = [os.path.join(train_happy_dir, fname) for fname in train_happy_names[img_index:img_index + 8]]
    next_sad_img = [os.path.join(train_sad_dir, fname) for fname in train_sad_names[img_index:img_index + 8]]

    for i, img_path in enumerate(next_happy_img + next_sad_img):
        plt.subplot(4, 4, i + 1)
        plt.axis("off")
        img = mpimg.imread(img_path)
        plt.imshow(img)

    plt.tight_layout()
    plt.show()


# Mengklasifikasi gambar uji
def classify_images(fn_arr, model):
    for fn in fn_arr:
        path = os.path.join("datasets", fn)
        if not os.path.exists(path):
            print(f"File not found: {path}")
            continue

        img = keras_image.load_img(path, target_size=(150, 150))
        x = keras_image.img_to_array(img)
        x = np.expand_dims(x, axis=0)
        x /= 255.0  # Normalize the image

        prediction = model.predict(x)
        print(f"Prediction score for {fn}: {prediction[0][0]}")
        if prediction[0] > 0.5:
            print(f"{fn} is happy")
        else:
            print(f"{fn} is sad")


# Main program
if __name__ == "__main__":
    # Konfigurasi path
    base_dir = "datasets"
    zip_file_path = os.path.join(base_dir, "happy-or-sad.zip")
    extracted_zip_file_path = os.path.join(base_dir, "happy-or-sad")
    train_happy_dir = os.path.join(extracted_zip_file_path, "happy")
    train_sad_dir = os.path.join(extracted_zip_file_path, "sad")

    # Load dataset
    train_happy_names, train_sad_names = load_dataset(
        zip_file_path, extracted_zip_file_path,
        train_happy_dir, train_sad_dir
    )

    # Visualisasi gambar latih
    plot_training_images(train_happy_dir, train_sad_dir, train_happy_names, train_sad_names)

    # Preprocessing data
    train_generator, validation_generator = do_data_preprocessing(extracted_zip_file_path)

    # Buat dan latih model CNN
    cnn_model = create_cnn_model()
    DESIRED_ACCURACY = 0.99
    callbacks = MyCallback(DESIRED_ACCURACY)

    history = cnn_model.fit(
        train_generator,
        steps_per_epoch=train_generator.samples // train_generator.batch_size,
        validation_data=validation_generator,
        validation_steps=validation_generator.samples // validation_generator.batch_size,
        epochs=50,
        verbose=1,
        callbacks=[callbacks]
    )

    # Uji klasifikasi gambar baru
    test_images = [
        "beauty-1132617_640.jpg",
        "girl-2961959_640.jpg",
        "woman-2126727_640.jpg",
        "beautiful-18279_640.jpg"
    ]
    classify_images(test_images, cnn_model)
