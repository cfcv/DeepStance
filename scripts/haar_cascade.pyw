import argparse

#Parsing the path argument
parser = argparse.ArgumentParser()
parser.add_argument("-p", "--path", help="Path to the image")
args = parser.parse_args()
assert (args.path != None),"A path to image must be informed!"

#Reading the image

#classifying 
box1 = (100,100,50,70,"Voiture")
box2 = (500,100,80,90,"Voiture")
#Retourning all the bounding boxes
print(box1)
print(box2)