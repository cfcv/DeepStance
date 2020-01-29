import time
import zmq
import cv2

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

print('Load haar cascade classifier')
cascade_classifier = cv2.CascadeClassifier('../rc/cars.xml')

print('Server Ready')
while True:
	message = socket.recv()
	print("Received request: %s" % message)

	#Reading the image
	args = message.decode().split(" ")
	print("Loading ", args[1])
	image = cv2.imread(args[1])

	#classifying 
	if(args[0] == "haar"):
		print("Using cascade classifier")
		gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
		cars = cascade_classifier.detectMultiScale(gray_image, 1.1, 3)
	else:
		print("Classification method not found")

	#Retourning all the bounding boxes
	res = ""
	for (x,y,w,h) in cars:
		res += '$ ' + str(x) + ',' + str(y) + ',' + str(w) + ',' + str(h) + ', Voiture' + '\r\n'
	print("Sending", res)
	socket.send(res.encode())