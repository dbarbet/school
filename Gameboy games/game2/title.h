/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 title /home/david/Documents/Cs2110/hw11/titlePage.jpg 
 * Time-stamp: Tuesday 11/11/2014, 20:30:42
 * 
 * Image Information
 * -----------------
 * /home/david/Documents/Cs2110/hw11/titlePage.jpg 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * A C program is like a fast dance on a newly waxed dance floor by people carrying razors. - Waldi Ravens.
 * 
 * A soft voice may be awfully persuasive.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef TITLE_BITMAP_H
#define TITLE_BITMAP_H

extern const unsigned short title_palette[256];
#define TITLE_PALETTE_SIZE 256

extern const unsigned short titlePage[19200];
#define TITLEPAGE_SIZE 19200
#define TITLEPAGE_WIDTH 240
#define TITLEPAGE_HEIGHT 160

#endif

