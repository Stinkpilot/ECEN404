import os
from PIL import Image as im
import numpy as np
import tensorflow as tf
import sys

def Object_Classification_Cut(image, detection_boxes, detection_scores, detection_classes, num_detections, image_tensor, sess):	
    image_expanded = np.expand_dims(image, axis=0)

    # Perform the actual detection by running the model with the image as input
    (boxes, scores, classes, num) = sess.run([detection_boxes, detection_scores, detection_classes, num_detections],feed_dict={image_tensor: image_expanded})

    animals = [0, 0, 0, 0]
    lengthc = np.size(classes)
    lengths = np.size(scores)
    if lengthc == lengths:
        for i in range(lengths):
            if  scores[0,i] > .7:
                if classes[0,i] == 1:
                    animals[0] += 1
                elif classes[0,i] == 2:
                    animals[1] += 1
                elif classes[0,i] == 3:
                    animals[2] += 1
                elif classes[0,i] == 4:
                    animals[3] += 1
            else:
                break
    return animals

