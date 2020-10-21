#include <Magick++.h>
#include "unistd.h"  
#include <iostream.h>
#include <math.h>
 
using namespace std;
using namespace Magick;
 
#define KS 13
#define SIG 8.0

 
int main(int argc,char **argv)
{
  char resp = ' ';
  double r, g, b;
  long k, s, disp_pid;

  if(argc != 3)
  {
    cerr << "Usage: art_image input_file output_file\n";
    exit(1);
  }
       try {
         // Create an image object and read the image
         Image image( argv[1] );

	 while(resp != 'q')
	 {
	   image.display(); 
	   cout << "Command: ";
	   cin >> resp;
	   switch(resp)
	   {
	   case 'r':
	     cout << "Number of colours: ";
	    int cols;
	    cin >> cols;
            image.quantizeColors(cols);
            image.quantize(1);
	    break;

	   case 't':
	    cout << "Colour RGB for transparency (0..255): ";
	    cin >> r >> g >> b;
            image.transparent(ColorRGB(r/255.0,g/255.0,b/255.0));
	    break;

	   case 'b':
	     cout << "Kernel size and sigma: ";
	     cin >> k >> s;
	     image.blur(k, s);
	     break;

	   case 'g':
	     image.modulate(100,0,100);
	     break;

	   case 'd':
	     image.despeckle();
	     break;

	   case 'c':
	     cout << "Radius: ";
	     cin >> r;
	     cout << "Sigma: ";
	     cin >> g;
	     image.charcoal(r, g);
	     break;

	   case 'q':
	     break;

	   default:
	     cout << "\nCommands:\n";
	     cout << "r: reduce colours\n";
	     cout << "t: set a colour transparent\n";
	     cout << "b: blur\n";
	     cout << "g: set grey\n";
	     cout << "d: despeckle\n";
	     cout << "c: charcoal\n";
	     cout << "q: quit.\n\n";
	   }
           image.write(argv[2]);
	 }
       }
       catch( Exception &error_ )
         {
           cout << "Caught exception: " << error_.what() << endl;
           return 1;
         }
       return 0;
}                
