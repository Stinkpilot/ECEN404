#import the necessary libraries
import numpy  as np
from keras import models
import tensorflow as tf
from keras.preprocessing.image import ImageDataGenerator

CATEGORIES = ["bears", "deer", "lynx", "wolves"]

#insert a sting of the location of the folder containing the test images
test_dir = '/Users/Josh/DeepLearningData/fourAnimalClasses/test'

#processes images from test_dir.
test_datagen = ImageDataGenerator(rescale=1./255)

#batch_size determines how many images to pick and use
#do not exceed maximum images in folder and do not change anything else
test_generator = test_datagen.flow_from_directory(
	test_dir,
	target_size=(150,150),
	batch_size=100,
	class_mode='categorical')

#get images and labels from generator
test_imgs, test_labels = next(test_generator)

#load model to analyse images
model = models.load_model("ForestAnimals5.h5")

#run images through model and output probability of which animal is which
predictions = model.predict_generator(test_generator, steps=1, verbose=1)

#percentage of correct classification
percentage = np.mean(np.equal(np.argmax(test_labels, axis=-1), np.argmax(predictions, axis=-1)))

print(percentage)

#This is for Python 3. If using Python 2, switch function to raw_input().
input("Press Enter to continue...")
