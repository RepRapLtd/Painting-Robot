# Painting-Robot

This is a project to create a painting robot. But this is a tricky thing to do, so we will do it in stages hoping that each stage on its own will be useful.

## Background

A while ago any half-decent artist would rock up at the palace of Lorenzo de Medici in a mendicant sort of way then later depart with a wheelbarrow full of gold ducats.  These they would use to set up a Florentine atelier.  Here they would install a dozen or so junior wannabe artists.  These would be set to gathering firewood, grinding pigments, poisoning themselves with the results, making flat(ish) wood panels,  trimming candles and all the rest while the artist thought *Profound Artistic Thoughts* and, from time to time, dabbed a bit of paint on a panel.

These days, of course, we have computers and robots to do all that, including some - though not all - of the *Profound Artistic Thinking*.

So the general idea of this project is to start with an AI (or possibly even a *camera*) generating photorealistic images like this:

<table style="width:100%">
  <tr>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai-face-6.jpeg" alt="ash hair">
    </th>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai-face-10.jpeg" alt="glasses bloke">
    </th>
  </tr>
</table>

These people have never existed. They were created by [StyleGAN2](https://arxiv.org/abs/1912.04958). You can [experiment with this here](https://thispersondoesnotexist.com/). 

We will then feed these into another AI that turns photographs into paintings in any number of different styles, like this:

<table style="width:100%">
  <tr>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai6-nc.jpg" alt="ash hair">
    </th>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai10-nc.jpg" alt="glasses bloke">
    </th>
  </tr>
</table>

We won't just be using AI images of people, but also of landscapes, seascapes, still lives, and all the rest. Here, for example, is a landscape image from [Artbreeder](https://www.artbreeder.com/). 

![landscape 1](https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/artb-1.jpg)

This is an AI that works like [Richard Dawkins' Biomorphs selection program](http://www.emergentmind.com/biomorphs). The AI generates a number of images from which you select the one you like most. It then creates mutations of that image and you repeat your selection until you have something that looks like what you want. That is already pretending to be a painting, but here is the result of running it through the painting generation program:

![landscape 1 nc](https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/artb-1-nc.jpg)


Finally, we'll build a robot that will paint that in acrylic on a panel. The software that generates paintings from photographs (real or otherwise) is called Night Café (after the Van Gough painting) and is [available here](https://creator.nightcafe.studio/).

We won't just start with photorealism, we will also use AI-generated abstracts, like this:

![abstract 1](https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/1.jpeg)

And paint them directly. That was from [here](https://thisartworkdoesnotexist.com/), incidentally.

All the generation and digital manipulation of images is pretty much in place at free sites like those listed above on the web.

But to start with, we are just going to make a...

## Paint mixer

This will be a device loaded with cyan, magenta, yellow and white paint in precisely metered syringe pumps. You will click on a pixel of the image you want to paint, and the device will give you one mililiter (or whatever volume you select) of the mix you need to get the colour of that pixel.

Here is a picture of the work-in-progress on the mixer, which is in the Paint-mixer directory of this repository:

![mixer wip](https://github.com/RepRapLtd/Painting-Robot/blob/master/Paint-mixer/Pics/mixer-wip.jpg)

You can then use that to paint the image by hand. If you're feeling like cheating, as [Vermeer did using a camera obscura](https://www.bbc.co.uk/history/british/empire_seapower/vermeer_camera_01.shtml), you can even use a data projector to throw the image onto your canvas or panel to guide you.

When that's working we will go on to build...
 
## The painting robot

We intend the painting robot to be a machine that works with real artist's brushes on panels. It'll probably be a cartesian design and will be largely 3D printed. It will have a webcam looking at its panel under constant lighting. To paint a picture stored in the controling computer as a .png or whatever it will:

1. Compute the biggest difference between the panel and the .png file.
2. Mix paint to the average colour of that area.
3. Apply it to the panel.
4. Go to 1.

Until a person stops it or maybe untill the difference measure in Step 1. is smaller than some threshold. 

## Licence

All this work is free and open source, licenced under the GPL.


## Some other painting robots:

https://makezine.com/2012/04/22/botspot-open-source-art-robots/

https://github.com/evil-mad/robopaint

https://watercolorbot.com/

Generator AI: https://github.com/lucidrains/stylegan2-pytorch

https://kvfrans.com/clipdraw-exploring-text-to-drawing-synthesis/

https://github.com/BachiLi/diffvg


