import numpy as np
from matplotlib import pyplot as plt
caffe_root = '/home/kenyon/caffe/' 
import sys
sys.path.insert(0, caffe_root + 'python')
import caffe
from pylab import *

print dir(caffe)
from caffe import Layer as L
#from caffe import Param as P

caffe.set_mode_cpu()

#helps to dray the network
import caffe.draw
from caffe.proto import caffe_pb2
#To read the prototxt file
from google.protobuf import text_format


# network file structure
input_net_proto_file ='models/ResNet/ResNet_50_train_val.prototxt'
# output image file
output_image_file ='models/ResNet/figures/resnet50_train.jpg'
#Arrangement of network structure: LR, TB, RL etc.
rankdir ='LR'

net = caffe_pb2.NetParameter()
text_format.Merge(open(input_net_proto_file).read(), net)

caffe.draw.draw_net_to_file(net, output_image_file, rankdir)
