from PIL import Image, ImageTk
#, ImageFilter, ImagePalette
import tkinter
#import numpy as np
#import cv2
#from skimage import io
#from skimage.viewer import ImageViewer, Qt
#import matplotlib.pyplot as plt

def RGBtoCMYK(colour):
 r = colour[0]
 g = colour[1]
 b = colour[2]
 k = 1.0 - max((r, g, b))
 c = (1.0 - r - k)/(1.0 - k)
 m = (1.0 - g - k)/(1.0 - k)
 y = (1.0 - b - k)/(1.0 - k)
 return (c, m, y, k)

def RGBtoCMYW(colour):
 r = colour[0]
 g = colour[1]
 b = colour[2]
 k = 1.0 - max((r, g, b))
 w = 1 - k
 c = 1.0 - r + k/3.0
 m = 1.0 - g + k/3.0
 y = 1.0 - b + k/3.0
 s = w + c + m + y
 w = w/s
 c = c/s
 m = m/s
 y = y/s
 return (c, m, y, w)

def ColourScale(colour):
 r = colour[0]/255.0
 g = colour[1]/255.0
 b = colour[2]/255.0
 return (r, g, b)

class Picture:

 def callback(self, event):
  c = ColourScale(self.pixels[event.x,event.y])
  print("x = ", event.x, ", y = ", event.y, ", rgb: ", c, ", cmyw: ", RGBtoCMYW(c))

 def __init__(self, name):
  self.window = tkinter.Tk(className=name)
  im = Image.open(name)
  #im = im.quantize(4)
  #im.show()
  self.pixels = im.load()
  canvas = tkinter.Canvas(self.window, width=im.size[0], height=im.size[1])
  canvas.pack()
  image_tk = ImageTk.PhotoImage(im)
  canvas.create_image(im.size[0]//2, im.size[1]//2, image=image_tk)
  canvas.bind("<Button-1>", self.callback)
  self.window.mainloop()

#p = Picture('../../Artworks/ai6-nc.jpg')
p = Picture('../../Artworks/palette.jpg')





