from PIL import Image,  ImageFilter, ImagePalette
#import numpy as np
#import cv2
#from skimage import io
#from skimage.viewer import ImageViewer, Qt
import matplotlib.pyplot as plt

#Read image
im = Image.open( '../../Artworks/cb-1.jpg' )
im.show()
im = im.convert("P", palette = Image.ADAPTIVE, colors = 16)
p = im.getcolors()
print(p)
im.show()
#im1 = ImagePalette.ImagePalette(mode ='RGB', palette = None, size = 0)
#print(im1)

'''
for q in range(0, 201, 40):
 q1 = q
 if q1 < 1:
  q1 = 1
 r = 50-q/4
 print('r: ', r, ' q: ', q1)
 im2 = im.filter(ImageFilter.BoxBlur(r))
 #im2.show()
 im3 = im2.quantize(q1)
 im3.show()
'''
