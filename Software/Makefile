 
IMAGE = .
 
# The name of the C++ compiler
CC = g++
 
# Flags to send the compiler (change the last two with care...)
CFLAGS = -g
 
# Object, Runnable and Include directories
 
ODIR = $(IMAGE)/obj
IDIR = $(IMAGE)/include
RDIR = $(IMAGE)/bin
SDIR = $(IMAGE)/src
 
 
 
FL = -g -I$(IDIR) -O2 -I/usr/include/freetype2 -D_REENTRANT -D_FILE_OFFSET_BITS=64 -I/usr/local/include -I/usr/X11R6/include -I/usr/X11R6/include/X11
GB = -L/usr/lib -L/usr/local/lib -L/usr/X11R6/lib -lMagick++ -L/usr/local/src/ImageMagick-5.4.3/magick -lMagick -ltiff -ljpeg -lpng -ldpstk -ldps -lXext -lXt -lSM -lICE -lX11 -lbz2 -lz -lpthread -lm
 
 
art_image:  $(ODIR)/art_image.o
			 $(CC) -o $(RDIR)/art_image $(ODIR)/art_image.o $(GB)
 
# Make the objects
 
$(ODIR)/art_image.o:  $(SDIR)/art_image.cxx
			 $(CC) -c $(FL) -o $(ODIR)/art_image.o $(SDIR)/art_image.cxx				    
