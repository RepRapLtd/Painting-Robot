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

These people have never existed. They were created by [StyleGAN2](https://arxiv.org/abs/1912.04958). You can [experiment with this here](https://thispersondoesnotexist.com/). We won't just be using AI images of people, but also of landscapes, seascapes, still lives, and all the rest.

We will then feed these into another AI that turns photographs into paintings in any number of different styles, like this:

<table style="width:100%">
  <tr>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai6-nc.jpg" alt="ash hair">
    </th>
    <th><img width: 100%; display: block; src="https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/ai10-nc.jpg" alt="glasses bloke">
    </th>
  </tr>
</table>


Finally, we'll build a robot that will paint that in acrylic on a panel. The software that generates paintings from photographs (real or otherwise) is called Night Café (after the Van Gough painting) and is [available here](https://creator.nightcafe.studio/).

We won't just start with photorealism, we will also use AI-generated abstracts, like this:

![abstract 1](https://github.com/RepRapLtd/Painting-Robot/blob/master/Artworks/1.jpeg)

And paint them directly. That was from [here](https://thisartworkdoesnotexist.com/), incidentally.

All the generation and digital manipulation of images is pretty much in place at free sites like those listed above on the web.

But to start with, we are just going to make a...

## Paint mixer

This will be a device loaded with cyan, magenta, yellow and white paint in precisely metered syringe pumps. You will click on a pixel of the image you want to paint, and the device will give you one mililiter (or whatever volume you select) of the mix you need to get the colour of that pixel.

You can then use that to paint the image by hand. If you're feeling like cheating, as [Vermeer did using a camera obscura](https://www.bbc.co.uk/history/british/empire_seapower/vermeer_camera_01.shtml), you can even use a data projector to throw the image onto your canvas or panel to guide you.

When that's working we will go on to build...
 
## The painting robot

We intend the painting robot to be a machine that works with real artist's brushes on panels. It'll probably be a cartesian design and will be largely 3D printed.

## Licence

All this work is free and open source, licenced under the GPL.


## Some other painting robots:

https://makezine.com/2012/04/22/botspot-open-source-art-robots/

https://github.com/evil-mad/robopaint

https://watercolorbot.com/

Generator AI: https://github.com/lucidrains/stylegan2-pytorch

