import argparse
import zmq

#Parsing the path argument
parser = argparse.ArgumentParser()
parser.add_argument("-p", "--path", help="Path to the image")
args = parser.parse_args()
assert (args.path != None),"A path to image must be informed!"

context = zmq.Context()

#  Socket to talk to server
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

cmd = "haar " + args.path
socket.send(cmd.encode())

#  Get the reply.
message = socket.recv()
print(message.decode())