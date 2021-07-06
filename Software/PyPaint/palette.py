from PIL import Image, ImageTk, ImageDraw, ImageFont
import tkinter


window = tkinter.Tk(className="palette")
image = Image.new("RGB", (700, 700))
draw = ImageDraw.Draw(image)
fnt = ImageFont.truetype("Pillow/Tests/fonts/FreeMono.ttf", 40)
for r in range(4):
 red = round(255.0*r/3.0)
 for g in range(4):
  green = round(255.0*g/3.0)
  for b in range(4):
   blue = round(255.0*b/3.0)
   rec = r*16 + g*4 + b
   x = (rec & 7)*80 + 40
   y = ((rec >> 3) & 7)*80 + 40
   draw.rectangle([x, y, x+70, y+70], fill=(red, green, blue), outline=None, width=1)
   draw.text((x+20,y+20), str(rec), font=fnt, fill=(255,255,255,255))
image.save('../../Artworks/palette.jpg')
pixels = image.load()
canvas = tkinter.Canvas(window, width=image.size[0], height=image.size[1])
canvas.pack()
image_tk = ImageTk.PhotoImage(image)
canvas.create_image(image.size[0]//2, image.size[1]//2, image=image_tk)
window.mainloop()

