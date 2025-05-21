import os
import zipfile
import numpy as np
import random
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import tensorflow as tf
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator, img_to_array, load_img
from tensorflow.keras.preprocessing import image as keras_image


def load_dataset(zip_file_path, extracted_zip_file_path):
    zip_ref = zipfile.ZipFile(zip_file_path, "r")
    zip_ref.extractall(os.path.split(extracted_zip_file_path)[0])
    zip_ref.close()

    train_dir = os.path.join(extracted_zip_file_path, "train")
    validation_dir = os.path.join(extracted_zip_file_path, "validation")

    train_cats_dir = os.path.join(train_dir, "cats")
    train_dogs_dir = os.path.join(train_dir, "dogs")
    validation_cats_dir = os.path.join(validation_dir, "cats")
    validation_dogs_dir = os.path.join(validation_dir, "dogs")

    train_cat_fnames = os.listdir(train_cats_dir)
    train_dog_fnames = os.listdir(train_dogs_dir)
    validation_cat_fnames = os.listdir(validation_cats_dir)
    validation_dog_fnames = os.listdir(validation_dogs_dir)

    print(train_cat_fnames[:10])
    print(train_dog_fnames[:10])
    print("total training cat images :", len(train_cat_fnames))
    print("total training dog images :", len(train_dog_fnames))
    print("total validation cat images:", len(validation_cat_fnames))
    print("total validation dog images:", len(validation_dog_fnames))

    return train_dir, validation_dir, train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames


def do_data_preprocessing(train_dir, validation_dir):
    train_datagen = ImageDataGenerator(rescale=1. / 255)
    validation_datagen = ImageDataGenerator(rescale=1. / 255)

    train_generator = train_datagen.flow_from_directory(
        train_dir,
        batch_size=20,
        class_mode="binary",
        target_size=(150, 150)
    )

    validation_generator = validation_datagen.flow_from_directory(
        validation_dir,
        batch_size=20,
        class_mode="binary",
        target_size=(150, 150)
    )

    return train_generator, validation_generator


def create_cnn_model():
    inputs = tf.keras.Input(shape=(150, 150, 3))
    x = tf.keras.layers.Conv2D(16, (3, 3), activation="relu")(inputs)
    x = tf.keras.layers.MaxPooling2D(2, 2)(x)
    x = tf.keras.layers.Conv2D(32, (3, 3), activation="relu")(x)
    x = tf.keras.layers.MaxPooling2D(2, 2)(x)
    x = tf.keras.layers.Conv2D(64, (3, 3), activation="relu")(x)
    x = tf.keras.layers.MaxPooling2D(2, 2)(x)
    x = tf.keras.layers.Flatten()(x)
    x = tf.keras.layers.Dense(512, activation="relu")(x)
    outputs = tf.keras.layers.Dense(1, activation="sigmoid")(x)

    model = tf.keras.Model(inputs=inputs, outputs=outputs)
    model.summary()
    model.compile(optimizer=Adam(learning_rate=0.001),
                  loss="binary_crossentropy",
                  metrics=["accuracy"])
    return model


def plot_cats_and_dogs(train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames):
    nrows, ncols = 4, 4
    fig = plt.gcf()
    fig.set_size_inches(ncols * 4, nrows * 4)

    pic_index = 8
    next_cat_pix = [os.path.join(train_cats_dir, fname) for fname in train_cat_fnames[pic_index - 8:pic_index]]
    next_dog_pix = [os.path.join(train_dogs_dir, fname) for fname in train_dog_fnames[pic_index - 8:pic_index]]

    for i, img_path in enumerate(next_cat_pix + next_dog_pix):
        sp = plt.subplot(nrows, ncols, i + 1)
        sp.axis("off")
        img = mpimg.imread(img_path)
        plt.imshow(img)
    plt.pause(0)


def classify_images(fn_arr, model):
    for fn in fn_arr:
        path = os.path.join("datasets", fn)
        img = keras_image.load_img(path, target_size=(150, 150))
        x = keras_image.img_to_array(img)
        x = np.expand_dims(x, axis=0)
        image_i = np.vstack([x])
        classes = model.predict(image_i, batch_size=10)

        print(classes[0])
        if classes[0] > 0.5:
            print(fn + " is a dog")
        else:
            print(fn + " is a cat")


def plot_intermediate_repr(model, train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames):
    successive_outputs = [layer.output for layer in model.layers]
    visualization_model = tf.keras.models.Model(inputs=model.input, outputs=successive_outputs)

    cat_img_files = [os.path.join(train_cats_dir, f) for f in train_cat_fnames]
    dog_img_files = [os.path.join(train_dogs_dir, f) for f in train_dog_fnames]
    img_path = random.choice(cat_img_files + dog_img_files)

    img = load_img(img_path, target_size=(150, 150))
    x = img_to_array(img)
    x = x.reshape((1,) + x.shape) / 255.

    successive_feature_maps = visualization_model.predict(x)
    layer_names = [layer.name for layer in model.layers]

    for layer_name, feature_map in zip(layer_names, successive_feature_maps):
        if len(feature_map.shape) == 4:
            n_features = feature_map.shape[-1]
            size = feature_map.shape[1]
            display_grid = np.zeros((size, size * n_features))
            for i in range(n_features):
                x = feature_map[0, :, :, i]
                x -= x.mean()
                x = x / x.std() if x.std() > 1e-14 else x
                x = np.clip(x * 64 + 128, 0, 255).astype("uint8")
                display_grid[:, i * size:(i + 1) * size] = x
            plt.figure(figsize=(20, 2))
            plt.title(layer_name)
            plt.grid(False)
            plt.imshow(display_grid, aspect="auto", cmap="viridis")
            plt.subplots_adjust(left=0.03, right=0.99)
    plt.pause(0)


def plot_history(train, val, title):
    epochs = range(len(train))
    plt.figure()
    plt.plot(epochs, train, label="train")
    plt.plot(epochs, val, label="val")
    plt.title(title)
    plt.legend(loc="best")
    plt.pause(0)


if __name__ == "__main__":
    zip_file_path = "datasets/cats_and_dogs_filtered.zip"
    extracted_zip_file_path = "datasets/cats_and_dogs_filtered"

    train_dir, validation_dir, train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames = load_dataset(
        zip_file_path, extracted_zip_file_path)

    plot_cats_and_dogs(train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames)

    train_generator, validation_generator = do_data_preprocessing(train_dir, validation_dir)

    cnn_model = create_cnn_model()
    history = cnn_model.fit(
        train_generator,
        validation_data=validation_generator,
        steps_per_epoch=100,
        epochs=15,
        validation_steps=50,
        verbose=1
    )

    fn_arr = [
        "cat-2083492_only_head.jpg",
        "cat-1146504_640.jpg",
        "dog-3846767_640.jpg",
        "dog-3388069_640.jpg"
    ]
    classify_images(fn_arr, cnn_model)

    plot_intermediate_repr(cnn_model, train_cats_dir, train_dogs_dir, train_cat_fnames, train_dog_fnames)

    acc = history.history["accuracy"]
    val_acc = history.history["val_accuracy"]
    loss = history.history["loss"]
    val_loss = history.history["val_loss"]

    plot_history(acc, val_acc, "Training and validation accuracy")
    plot_history(loss, val_loss, "Training and validation loss")
