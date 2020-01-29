import time
import zmq
import cv2

import model_utils as MU 
import bounding_box as BB
from keras.models import load_model, Model

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

print('Loading haar cascade classifier')
cascade_classifier = cv2.CascadeClassifier('../rc/cars.xml')

print('Loading YOLO')
yolov3 = load_model('../rc/yolov3.h5')

input_w, input_h = 416, 416
obj_thresh, nms_thresh = 0.5, 0.45
anchors = [[116,90, 156,198, 373,326], [30,61, 62,45, 59,119], [10,13, 16,30, 33,23]]
labels = ["person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", \
              "boat", "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", \
              "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", \
              "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", \
              "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", \
              "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", \
              "apple", "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", \
              "chair", "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor", "laptop", "mouse", \
              "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", \
              "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"]

print('Server Ready...')
while True:
	message = socket.recv()
	print("Received request: %s" % message)

	#Reading the image
	args = message.decode().split(" ")

	#classifying 
	if(args[0] == "haar"):
		print("Loading ", args[1])
		image = cv2.imread(args[1])
		print("Using cascade classifier")
		gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
		cars = cascade_classifier.detectMultiScale(gray_image, 1.1, 3)
		
		#Retourning all the bounding boxes
		res = ""
		for (x,y,w,h) in cars:
			res += '$ ' + str(x) + ',' + str(y) + ',' + str(w) + ',' + str(h) + ',Voiture' + '\r\n'
		print("Sending", res)
		socket.send(res.encode())
	
	elif(args[0] == "yolo"):
		print("Loading ", args[1])
		image, image_w, image_h = MU.load_image_pixels(args[1], (input_w, input_h))
		
		print("Using YOLO neural network")
		yolos = yolov3.predict(image)

		class_threshold = 0.6
		boxes = list()
		for i in range(len(yolos)):
			# decode the output of the network
			boxes += BB.decode_netout(yolos[i][0], anchors[i], obj_thresh,  input_w, input_h)

		# correct the sizes of the bounding boxes
		BB.correct_yolo_boxes(boxes, image_h, image_w, input_w, input_h)

		# suppress non-maximal boxes
		BB.do_nms(boxes, nms_thresh)

		# get the details of the detected objects
		v_boxes, v_labels, v_scores = BB.get_boxes(boxes, labels, class_threshold)
		
		res = ""
		for i in range(len(v_boxes)):
			if(v_labels[i] != "car" and v_labels[i] != "bus" and v_labels[i] != "train" and v_labels[i] != "truck"):
				continue
			y1, x1, y2, x2 = v_boxes[i].ymin, v_boxes[i].xmin, v_boxes[i].ymax, v_boxes[i].xmax
			width, height = x2 - x1, y2 - y1
			res += '$ ' + str(x1) + ',' + str(y1) + ',' + str(width) + ',' + str(height) + ',' + str(v_labels[i]) + ':' + str(round(v_scores[i], 2)) + '\r\n'
		print("Sending", res)
		socket.send(res.encode())
	else:
		print("Classification method not found")

	