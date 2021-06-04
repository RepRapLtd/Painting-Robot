from PIL import Image,  ImageFilter, ImagePalette
#import numpy as np
#import cv2
#from skimage import io
#from skimage.viewer import ImageViewer, Qt
import matplotlib.pyplot as plt

def RGBtoCMYK(colour):
 r = colour[0]
 g = colour[1]
 b = colour[2]
 k = 1.0 - max((r, g, b))
 c = (1.0 - r - k)/(1.0 - k)
 m = (1.0 - g - k)/(1.0 - k)
 y = (1.0 - b - k)/(1.0 - k)
 return (c, m, y, k)


#Read image
im = Image.open( '../../Artworks/1.jpeg' )
im = im.quantize(2)
im.show()
#p = im.getpalette()
#for c in p:
 #c0 = c[0]
 #print(c)
 #r, g, b = c0
 #print(r, g, b)
c = (0.6,0.5,0.5)
print(c)
print(RGBtoCMYK(c))

#im = im.convert('RGB')
#im.save('../../Artworks/1a.jpg')


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
