import argparse
import cv2

#Parsing the path argument
parser = argparse.ArgumentParser()
parser.add_argument("-p", "--path", help="Path to the image")
args = parser.parse_args()
assert (args.path != None),"A path to image must be informed!"

#Reading the image
image = cv2.imread(args.path)

#classifying 
cascade_classifier = cv2.CascadeClassifier('../rc/cars.xml')
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

cars = cascade_classifier.detectMultiScale(gray_image, 1.1, 3)


#Retourning all the bounding boxes
for (x,y,w,h) in cars:
	box = (x, y, w, h, "Voiture")
	print('$', x, ',', y, ',', w, ',', h, ',', "Voiture")