# Control program for the paint mixer
#
# Adrian Bowyer
# RepRap Ltd
#
# https://reprapltd.com
#
# 7 July 2021
#
# Licence: GPL
#-------------------------------------------
#


from PIL import Image, ImageTk
import tkinter
import serial

# Set false to turn off commentary
debug = True

class Mixer:
 def __init__(self, live):
  if live:
   self.usb = serial.Serial('/dev/ttyACM0',115200,timeout=0.1)
   # Tell it to use relative moves
   self.usb.write(str.encode("G91\n"))
  # Assume all retracted from last use
  self.retracted = [True]*4
  # Millilitres per unit of movement (i.e. reciprocal of what volume you get for G1 X1)
  self.milliL = 1.0
  # Extrusion rate, ml/second
  self.extrudeRate = 0.1
  # Retraction rate, ml/second
  self.retractionRate = 0.3
  # How many ml to retract
  self.retractMl = 0.1
  self.live = live


 def Move(self, movements, f):
  s = "G1 X"
  s += str(movements[0])
  s += " Y"
  s += str(movements[1])
  s += " Z"
  s += str(movements[2])
  s += " E"
  s += str(movements[3])
  s += " F"
  s += str(f)
  s += "\n"
  if self.live:
   self.usb.write(str.encode(s))
  if debug:
   print("Sent: ", s)

 def Feed(self, mlPerSecond):
  return 60.0*mlPerSecond*self.milliL

 def Extrude(self, volumes):
  movements = [0.0]*4
  for v in range(4):
   m = volumes[v]*self.milliL
   if self.retracted[v]:
    m = m + self.retractMl*self.milliL
    self.retracted[v] = False
   movements[v] = m
  self.Move(movements, self.Feed(self.extrudeRate))

 def Retract(self):
  movements = [0.0]*4
  for v in range(4):
   if self.retracted[v]:
    m = 0
   else:
    m = -self.retractMl*self.milliL
   self.retracted[v] = True
   movements[v] = m
  self.Move(movements, self.Feed(self.retractionRate))


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

def FloatsToString(floats):
 s = " "
 for f in floats:
  s += '%.4f' % f
  s += " "
 s = "(" + s + ")"
 return s

class Picture:

 # This does an avearage in the 5x5 square round the pixel
 # This may not be what we always want...
 def callback(self, event):
  colour = [0.0, 0.0, 0.0]
  for x in range(event.x - 2, event.x + 3):
   for y in range(event.y - 2, event.y + 3):
    pColour = self.pixels[x,y]
    c = ColourScale(pColour)
    colour[0] += c[0]
    colour[1] += c[1]
    colour[2] += c[2]
  colour[0] /= 25.0
  colour[1] /= 25.0
  colour[2] /= 25.0
  pColour = (int(round(colour[0]*255.0)), int(round(colour[1]*255.0)), int(round(colour[2]*255.0)))
  self.selectedColour.configure(bg='#%02x%02x%02x' % pColour)
  self.cmyw = RGBtoCMYW(colour)
  if debug:
   print("x =", event.x, ", y =", event.y, ", rgb:", FloatsToString(colour), ", cmyw:", FloatsToString(self.cmyw))


 def Retract(self):
  self.mixer.Retract()

 def Extrude(self, volume):
  volumes = [0.0]*4
  for v in range(4):
   volumes[v] = self.cmyw[v]*volume
  self.mixer.Extrude(volumes)

 def Extrude005(self):
  self.Extrude(0.05)

 def Extrude01(self):
  self.Extrude(0.1)

 def Extrude02(self):
  self.Extrude(0.2)

 def Extrude05(self):
  self.Extrude(0.5)

 def Extrude1(self):
  self.Extrude(1.0)

 def Quit(self):
  self.Retract()
  quit()

 def __init__(self, name, live):
  self.window = tkinter.Tk(className=name)
  self.mixer = Mixer(live)
  self.image = Image.open(name)
  self.pixels = self.image.load()
  self.canvas = tkinter.Canvas(self.window, width=self.image.size[0]+150, height=self.image.size[1])
  self.canvas.pack()
  image_tk = ImageTk.PhotoImage(self.image)
  self.canvas.create_image(self.image.size[0]//2, self.image.size[1]//2, image=image_tk)

  self.selectedColour = tkinter.Button(text="", width=10, height=3, bg="white", fg="white")
  self.selectedColour.pack()
  yPos = 10
  self.selectedColour.place(x=self.image.size[0]+20, y = yPos)
  self.retract = tkinter.Button(text="retract", width=10, height=3, bg="grey", fg="white",command=self.Retract)
  self.retract.pack()
  yPos += 70
  self.retract.place(x=self.image.size[0]+20, y = yPos)

  self.e005 = tkinter.Button(text="0.05 ml", width=10, height=3, bg="grey", fg="white",command=self.Extrude005)
  self.e005.pack()
  yPos += 70
  self.e005.place(x=self.image.size[0] + 20, y=yPos)
  self.e01 = tkinter.Button(text="0.1 ml", width=10, height=3, bg="grey", fg="white",command=self.Extrude01)
  self.e01.pack()
  yPos += 70
  self.e01.place(x=self.image.size[0] + 20, y=yPos)
  self.e02 = tkinter.Button(text="0.2 ml", width=10, height=3, bg="grey", fg="white",command=self.Extrude02)
  self.e02.pack()
  yPos += 70
  self.e02.place(x=self.image.size[0] + 20, y=yPos)
  self.e05 = tkinter.Button(text="0.5 ml", width=10, height=3, bg="grey", fg="white",command=self.Extrude05)
  self.e05.pack()
  yPos += 70
  self.e05.place(x=self.image.size[0] + 20, y=yPos)
  self.e1 = tkinter.Button(text="1 ml", width=10, height=3, bg="grey", fg="white",command=self.Extrude1)
  self.e1.pack()
  yPos += 70
  self.e1.place(x=self.image.size[0] + 20, y=yPos)

  self.quit = tkinter.Button(text="Quit", width=10, height=3, bg="grey", fg="white",command=self.Quit)
  self.quit.pack()
  yPos += 100
  self.quit.place(x=self.image.size[0] + 20, y=yPos)

  self.canvas.bind("<Button-1>", self.callback)
  self.cmyw = RGBtoCMYW((1, 1, 1))
  self.window.mainloop()

#p = Picture('../../Artworks/ai6-nc.jpg')
p = Picture('../../Artworks/combined-palette.jpg', False)




