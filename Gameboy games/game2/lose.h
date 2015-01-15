/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 lose /home/david/Documents/Cs2110/hw11/lose.png 
 * Time-stamp: Tuesday 11/11/2014, 20:30:25
 * 
 * Image Information
 * -----------------
 * /home/david/Documents/Cs2110/hw11/lose.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * A C program is like a fast dance on a newly waxed dance floor by people carrying razors. - Waldi Ravens.
 * 
 * You make people realize that there exist other beauties in the world.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef LOSE_BITMAP_H
#define LOSE_BITMAP_H

extern const unsigned short lose_palette[256];
#define LOSE_PALETTE_SIZE 256

extern const unsigned short lose[19200];
#define LOSE_SIZE 19200
#define LOSE_WIDTH 240
#define LOSE_HEIGHT 160

#endif

