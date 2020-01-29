import weight_reader as WR 
import model_utils as MU
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("path", help="path to the yolov3 weights")
args = parser.parse_args()
print(args.path)

yolov3 = MU.make_yolov3_model()

weight_reader = WR.WeightReader(args.path)
weight_reader.load_weights(yolov3)

yolov3.save('yolov3.h5')