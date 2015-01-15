/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 win /home/david/Documents/Cs2110/hw11/win.png 
 * Time-stamp: Tuesday 11/11/2014, 20:30:54
 * 
 * Image Information
 * -----------------
 * /home/david/Documents/Cs2110/hw11/win.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * A C program is like a fast dance on a newly waxed dance floor by people carrying razors. - Waldi Ravens.
 * 
 * Your life will get more and more exciting.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef WIN_BITMAP_H
#define WIN_BITMAP_H

extern const unsigned short win_palette[256];
#define WIN_PALETTE_SIZE 256

extern const unsigned short win[19200];
#define WIN_SIZE 19200
#define WIN_WIDTH 240
#define WIN_HEIGHT 160

#endif

