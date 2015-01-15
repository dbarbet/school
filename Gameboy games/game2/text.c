#include "text.h"
#include "mylib.h"

void drawChar(int row, int col, char ch, u8 index)
{
	int r, c;
	for(r = 0; r < 8; r++)
	{
		for(c = 0; c < 6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6) + ch * 48])
			{
				setPixel(row + r, col + c, index);
			}
		}
	}
}

void drawString(int row, int col, char *str, u8 index)
{
	while(*str)
	{
		drawChar(row, col, *str++, index);
		col += 6;

	}
}
