#include "mylib.h"
u16 *videoBuffer = (u16 *)0x6000000;


void setPixel(int row, int col, u8 index)
{
	if(col & 1)
	{
		videoBuffer[OFFSET(row, col, 240) / 2] = (videoBuffer[OFFSET(row, col, 240) / 2] & 0x00FF) | (index<<8);
	}
	else
	{
		videoBuffer[OFFSET(row, col, 240) / 2] = (videoBuffer[OFFSET(row, col, 240) / 2] & 0xFF00) | (index);
	}
}

void drawRect(int row, int col, int height, int width, u8 index)
{
	volatile unsigned short color = index | (index<<8);
	int r;
	for(r = 0; r < height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)/2];
		DMA[3].cnt = (width/2) | DMA_SOURCE_FIXED | DMA_ON; 
	}
}

void drawEQTriangle(int row, int col, int height, int length, u16 color)
{
	int r, c;
	for (r = height; r >= 0; r--)
	{
		for (c = length - 1; c >= 0; c--)
		{
			setPixel(row + r, col + c, color);
		}
		length--;
	}
}

void drawEQTriangle2(int row, int col, int height, int length, u16 color)
{
	int r, c;
	for (r = 0; r < height; r++)
	{
		for (c = length - 1; c >= 0; c--)
		{
			setPixel(row + r, col + c, color);
		}
		length--;
	}
}

void plotLine(int x0, int y0, int x1, int y1, u16 color)
{
	int x, y, px, xe, ye, i, dx2, dy2;
	int py = 0;
	int dx = x1 - x0;
	int dy = y1 - y0;
	if (dx < 0) dx2 = -dx;
	else dx2 = dx;
	if (dy < 0) dy2 = -dy;
	else dy2 = dy;
	px = dx2 << 1;
	px = px - dx2;
	py = py << 1;
	py = py - dy2;
	if (dy2 <= dx2) 
	{
		if (dx >= 0)
		{
			x = x0;
			y = y0;
			xe = x1;
		} else
		{
			x = x1;
			y = y1;
			xe = x0;
		}
		setPixel(x, y, color);
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0) px = px + (dy2 << 1);
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1;
				else y = y - 1;
				px = px + ((dy2 - dx2) << 1);
			}
			setPixel(x, y, color);
		}
	} else
	{
		if (dy >= 0) {
			x = x0;
			y = y0;
			ye = y1;
		} else {
			x = x1;
			y = y1;
			ye = y0;
		}
		setPixel(x, y, color);
		for (i = 0; y < ye; i++) {
			y = y + 1;
			if (py <= 0) py = py + (dx2 << 1);
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
				else x = x - 1;
				py = py + ((dx2 - dy2) << 1);
			}
			setPixel(x, y, color);
		}
	}
}

/*Draws circle with row and column being the midpoint of the circle.
 *Used Bresenham's circle algorithm.
 */
void drawCircle(int row, int col, int radius, u16 color)
{
	int x0 = col;
	int y0 = row;
	int x = radius;
	int y = 0;
	int radE = 1 - x;
	while (x >= y)
	{
		setPixel(x + x0, y + y0, color);
		setPixel(y + x0, x + y0, color);
		setPixel(-x + x0, y + y0, color);
		setPixel(-y + x0, x + y0, color);
		setPixel(-x + x0, -y + y0, color);
		setPixel(-y + x0, -x + y0, color);
		setPixel(x + x0, -y + y0, color);
		setPixel(y + x0, -x + y0, color);
		y++;
		if (radE < 0)
		{
			radE += (y << 1) + 1;
		} else
		{
			x--;
			radE += (y - x + 1) << 1;
		}
	}
}
void waitForVBlank()
{
	while (SCANLINECOUNTER >= 160);
	while (SCANLINECOUNTER < 160);
}

/*Returns 0 if not intersecting, 1 if intersecting
 *r1: rectangle 1, r2: rectangle 2
 */
int checkIntersection(int r1Bot, int r1Top, int r1Left, int r1Right, int r2Bot, int r2Top, int r2Left, int r2Right)
{
	if ((r1Bot < r2Top) || (r1Top > r2Bot) || (r1Left > r2Right) || (r1Right < r2Left))
	{
		return 0;
	} else
	{
		return 1;
	}
}

void fillScreen(u8 index)
{
	volatile u16 color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_ON;
}


void drawImage3(int r, int c, int width, int height, const u16* image)
{
	int row;
	for (row = 0; row < height; row++)
	{
		DMA[3].src = &image[row * width];
		DMA[3].dst = &videoBuffer[OFFSET(row+r, c, 240)];
		DMA[3].cnt = width | DMA_ON;
	}
}
void drawImage4(int r, int c, int width, int height, const u16* image)
{
	int row;
	for (row = 0; row < height; row++)
	{
		DMA[3].src = &image[(row * width) / 2];
		DMA[3].dst = &videoBuffer[OFFSET(row+r, c, 240) / 2];
		DMA[3].cnt = (width / 2) | DMA_ON;
	}
}

void flipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG)
	{
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

void delay(int n)
{
	int i;
	volatile int x=0;
	for(i=0; i<n*10000;i++)
	{
		x++;
	}
}




