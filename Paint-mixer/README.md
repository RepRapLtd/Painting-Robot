When you have a colour picture in a computer that uses red(R), green(G), and blue(B) additive light values you sometimes need to print it.

That means it has to be converted to the subtractive primaries for ink or paint: cyan(C), magenta(M), and yellow(Y), together with black(K).

The first question that arises is, why black? C,M, and Y are subtractive, so if you mix an equal amount of each you get black, meaning the actual black colour is theoretically redundant - you could make it with the other three. The reason is twofold: first black is cheap, you often need it alone for printing text, diagrams, and so on, and so you might as well use it instead of mixing C, M and Y every time you need it; the second is that inks and other colours are never perfect, so if you mix C, M and Y you get something very dark, but that often isn't quite true black.

How do we do the conversion? Let's start without black. If we have R, G and B values, each between 0 (none) and 1 (full brightness), then the C,M,Y equivalent is given by

C = 1 - R<br />
M = 1 - G<br />
Y = 1 - B<br />

And if we want to use black as well, we first note that there must be a minimum value out of C, M, and Y. If we imagine taking that and mixing it with equal amounts of the other two we will get a little bit of black. Then we can then add in the extra bits of the other two to get the colour we want. So we substitute actual black for that little bit of C,M,Y then add in the others:

K = 1 - max(R,G,B)<br />
C = (1 - R - K)/(1 - K)<br />
M = (1 - G - K)/(1 - K)<br />
Y = (1 - B - K)/(1 - K)<br />

Now. This all depends on the fact that we will be printing with subtractive inks on white paper. The paper is giving us any white we need - just see what happens in the formulae when R, G, and B all equal 1 and so we want white. (In fact then the formulae give the correct K value for this, then a divide by zero for the other three which should all be 0, so we have to detect that in programs that do this conversion.)

This is all very well for colours like inks or water colours on a white background. But suppose we want to mix opaque colours like oil paints or acrylics? Clearly any white behind won't show through, so the first thing is that we have to add in a white(W) paint. Do we also need black? If we are happy with the black our C, M, and Y give us when mixed equally, then no - we just need C, M, Y, and W.

A moment's thought shows that

W = 1 - K = max(R, G, B)<br />

And our formulae become

(K = 1 - max(R,G,B))<br />
W' = 1 - K<br />
C' = 1 - R + K/3<br />
M' = 1 - G + K/3<br />
Y' = 1 - B + K/3<br />

The reason for the primes (') will be seen in a moment. The (K formula) is in brackets because we need the value of K to work out the four other values, even though we won't be using any black paint.

There is one final problem: our C', M', Y', W' values are all in the correct ratios, but they don't add up to 1.  If we want to mix a certain number of milliliters of the right coloured paint, we need to know what fraction is W, what fraction is C and so on. So finally, we divide the four C', M', Y', W' values by the sum(S) of them all to get four fractions that add up to 1:

S = W' + C' + M' + Y'<br />
W = W'/S<br />
C = C'/S<br />
M = M'/S<br />
Y = Y'/S<br />

