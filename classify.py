import numpy as np
import matplotlib.pyplot as plt


# Make sure that caffe is on the python path:
caffe_root = '/home/geding/uam/si/caffe/'  # this file is expected to be in {caffe_root}/examples
import sys
sys.path.insert(0, caffe_root + 'python')

import caffe

# Set the right path to your model definition file, pretrained model weights,
# and the image you would like to classify.
MODEL_FILE = '/home/geding/si/models/deploy.prototxt'
PRETRAINED = '/home/geding/si/models/caffenet_train_iter_15000.caffemodel'
IMAGE_FILE = 'test/images (1).jpg'

import os


caffe.set_mode_cpu()

net = caffe.Classifier(MODEL_FILE, PRETRAINED,
                       mean=np.load(caffe_root + 'python/caffe/imagenet/ilsvrc_2012_mean.npy').mean(1).mean(1),
                       channel_swap=(2,1,0),
                       raw_scale=220,
                       image_dims=(221, 221))


MINE_DIR = "miny"
filenames = next(os.walk(MINE_DIR))[2]
f = open('folder_mine.txt', 'w')
fBest = open('folder_mine_best_prediction.txt', 'w')
for fileName in filenames:
    if not "jpg" in fileName: continue
    input_image = caffe.io.load_image(MINE_DIR + "/" + fileName)
    prediction = net.predict([input_image])
    print 'prediction shape:', prediction[0].shape
    plt.plot(prediction[0])
    print 'predicted class:', prediction[0].argmax()
    print 'predicted class prob:', prediction[0].item(prediction[0].argmax())
    print 'mine: ', prediction[0][0]
    print 'dang: ', prediction[0][1]
    print 'stone: ', prediction[0][2]
    print 'flora: ', prediction[0][3]
    f.write(fileName + " 0 "+ str(prediction[0][0]) +" 1 " + str(prediction[0][1]) +
        " 2 "+str(prediction[0][2])+" 3 " + str(prediction[0][3]) + "\r\n")
    fBest.write(fileName + " " + str(prediction[0].argmax()) + "\r\n")

f.close()
fBest.close()


OBJECTS_DIR = "obiekty"
filenames = next(os.walk(OBJECTS_DIR))[2]
f = open('folder_objects.txt', 'w')
fBest = open('folder_objects_best_prediction.txt', 'w')
for fileName in filenames:
    print fileName
    if not "jpg" in fileName: continue
    input_image = caffe.io.load_image(OBJECTS_DIR + "/" + fileName)
    prediction = net.predict([input_image])
    print 'prediction shape:', prediction[0].shape
    plt.plot(prediction[0])
    print 'predicted class:', prediction[0].argmax()
    print 'predicted class prob:', prediction[0].item(prediction[0].argmax())
    print 'mine: ', prediction[0][0]
    print 'dang: ', prediction[0][1]
    print 'stone: ', prediction[0][2]
    print 'flora: ', prediction[0][3]
    f.write(fileName + " 0 "+ str(prediction[0][0]) +" 1 " + str(prediction[0][1]) +
        " 2 "+str(prediction[0][2])+" 3 " + str(prediction[0][3]) + "\r\n")
    fBest.write(fileName + " " + str(prediction[0].argmax()) + "\r\n")

f.close()
fBest.close()


