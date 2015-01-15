#include "mylib.h"
#include "text.h"
#include "spaceship.h"
#include "lose.h"
#include "win.h"
#include "title.h"
#include <stdlib.h>
 typedef struct
 {
 	int row;
 	int col;
 	int oldRow;
 	int oldCol;
 	int width;
 	int height;
 	int speed;
 	int rowD;
 	int colD;
 } OBJECT;


int main(void)
{
	REG_DISPCTL = MODE4 | BG2_ENABLE;
	int i;
	//Number of lives
	int lives = 0;
	//Create spaceship obj
	OBJECT spaceship;
	spaceship.row = 0;
	spaceship.col = 0;
	spaceship.oldRow = 0;
	spaceship.oldCol = 0;
	spaceship.width = SPACESHIP_R_WIDTH;
	spaceship.height = SPACESHIP_R_HEIGHT;
	spaceship.speed = 2;
	spaceship.rowD = 0;
	spaceship.colD = 0;
	//Create asteroids
	int numAsteroids = 2;
	int rowB = 20;
	int colB = 20;
	int neg = 1;
	OBJECT asteroids[numAsteroids];
	for (int i = 0; i < numAsteroids; i++)
	{
		asteroids[i].row = rand() % 40 + rowB;
		rowB += 50;
		asteroids[i].col = rand() % 40 + colB;
		colB += 80;
		asteroids[i].oldRow = asteroids[i].row;
		asteroids[i].oldCol = asteroids[i].col;
		asteroids[i].width = ASTEROID_WIDTH;
		asteroids[i].height = ASTEROID_HEIGHT;
		asteroids[i].speed = 1;
		asteroids[i].rowD = neg;
		asteroids[i].colD = neg;
		neg = - neg;
	}
	//Create deathstar
	int deathRow = 60;
	int deathCol = 209;
	//Set initial for lose screen
	int showLoseScreen = 0;
	int notShownLoss = 1;
	//Set initial for win screen
	int showWinScreen = 0;
	int notShownWin = 1;
	//Set initial for title screen
	int showTitleScreen = 1;
	int notShownTitle = 1;
	//Show explosion animation
	int showExplode = 0;
	int astCollision = -1;
	const u16* images[28] =
	{
		explosion_r, explosion_r2, explosion_r3, explosion_r4, explosion_r5,
		explosion_r6, explosion_r7, explosion_r8, explosion_r9, explosion_r10,
		explosion_r11, explosion_r12, explosion_r13, explosion_r14,
		explosion_r15, explosion_r16, explosion_r15, explosion_r17,
		explosion_r18, explosion_r19, explosion_r20, explosion_r21,
		explosion_r22, explosion_r23, explosion_r24, explosion_r25,
		explosion_r26, explosion_r27
	};
	flipPage();
	while(1) {
		waitForVBlank();
		if (KEYDOWN(BUTTON_SELECT))
		{
			main();
		}		
		//Decide if showing lose screen, win screen, title, or continue with game
		if (showTitleScreen && notShownTitle)
		{
			//draw title screen
			for (i = 0; i < 256; i++)
			{
				PALETTE[i] = title_palette[i];
			}
			drawImage4(0, 0, TITLEPAGE_WIDTH, TITLEPAGE_HEIGHT, titlePage);
			flipPage();
			notShownTitle = 0;
		} else if (showTitleScreen)
		{
			//wait for input
			if (KEYDOWN(BUTTON_START))
			{
				showTitleScreen = 0;
				notShownTitle = 1;
				PALETTE[0] = 0;
				fillScreen(BLACK);
			}
		}else if (showLoseScreen && notShownLoss)
		{
			//drawloseimg
			for (i = 0; i < 256; i++)
			{
				PALETTE[i] = lose_palette[i];
			}
			drawImage4(0, 0, LOSE_WIDTH, LOSE_HEIGHT, lose);
			flipPage();
			notShownLoss = 0;
		} else if (showLoseScreen)
		{
			//Wait for input
			if (KEYDOWN(BUTTON_START))
			{
				main();
			}
		} else if (showWinScreen && notShownWin)
		{
			//Draw win image
			for (i = 0; i < WIN_PALETTE_SIZE; i++)
			{
				PALETTE[i] = win_palette[i];
			}
			drawImage4(0, 0, WIN_WIDTH, WIN_HEIGHT, win);
			flipPage();
			notShownWin = 0;
		} else if (showWinScreen)
		{
			//Wait for input
			if (KEYDOWN(BUTTON_START))
			{
				main();
			}
		} else if (showExplode)
		{
			PALETTE[0] = 0;
			fillScreen(0);
			flipPage();
			fillScreen(0);
			//Make sure right palette is loaded
			for (int i = 0; i < 256; i++)
			{
				PALETTE[i] = spaceship_palette[i];
			}
			//Draw animation
			for (int i = 0; i < 27; i++)
			{
				drawImage4(spaceship.row, spaceship.col, EXPLOSION_R_WIDTH,
					EXPLOSION_R_HEIGHT, images[i]);
				flipPage();
				delay(1);
				waitForVBlank();
				if (i == 26)
				{
					showExplode = 0;
					showLoseScreen = 1;
				}
			}
			
		} else
		{

			drawImage4(210, 60, DEATHSTAR_R_WIDTH,
				DEATHSTAR_R_HEIGHT, deathstar_r);
			//Create spaceship palette
			for (i = 0; i < 253; i++)
			{
				PALETTE[i] = spaceship_palette[i];
			}
			
			//Bounding box for spaceship
			int spaceTop = spaceship.row + 2;
			int spaceBot = spaceship.row + spaceship.height;
			int spaceLeft = spaceship.col + 1;
			int spaceRight = spaceship.col + spaceship.width - 2;
		 	//Determine if asteroids are at end of screen
			for (int i = 0; i < numAsteroids; i++)
			{
				//Check for hitting spaceship
				int asTop = asteroids[i].row;
				int asBot = asteroids[i].row + asteroids[i].height - 3;
				int asLeft = asteroids[i].col + 3;
				int asRight = asteroids[i].col + asteroids[i].width;
				if (checkIntersection(spaceBot, spaceTop,
					spaceLeft, spaceRight, asBot, asTop, asLeft, asRight))
				{
					astCollision = i;
					lives--;
					showExplode = 1;
					
				}
				//Move asteroid
				asteroids[i].oldRow = asteroids[i].row;
				asteroids[i].oldCol = asteroids[i].col;
				asteroids[i].row += asteroids[i].rowD;
				asteroids[i].col += asteroids[i].colD;
				//Check for hitting side of screen
				if (asteroids[i].row < 0)
				{
					asteroids[i].rowD = - asteroids[i].rowD;
				} else if (asteroids[i].row > 159 - ASTEROID_HEIGHT + 1)
				{
					asteroids[i].rowD = - asteroids[i].rowD;
				}
				if (asteroids[i].col < 0)
				{
					asteroids[i].colD = - asteroids[i].colD;
				} else if (asteroids[i].col > 239 - ASTEROID_WIDTH + 1)
				{
					asteroids[i].colD = - asteroids[i].colD;
				}
			}
			//Determine if Won
			int deathTop = deathRow;
			int deathBot = deathRow + DEATHSTAR_R_HEIGHT;
			int deathLeft = deathCol;
			int deathRight = deathCol + DEATHSTAR_R_WIDTH;
			int sTop = spaceship.row + 2;
			int sBot = spaceship.row + spaceship.height;
			int sLeft = spaceship.col + 1;
			int sRight = spaceship.col + spaceship.width - 2;
			if (checkIntersection(sBot, sTop, sLeft, sRight, deathBot, deathTop, deathLeft, deathRight))
			{
				showWinScreen = 1;
			}
			//Check for button presses
			if (KEYDOWN(BUTTON_DOWN))
			{		
				spaceship.row += spaceship.speed;
				if (spaceship.row > 159 - spaceship.height + 1)
				{
					spaceship.row = spaceship.oldRow;
				}
			}
			if (KEYDOWN(BUTTON_RIGHT))
			{
				spaceship.col += spaceship.speed;
				if (spaceship.col > 239 - spaceship.width + 1)
				{
					spaceship.col = spaceship.oldCol;
				}
			}
			if (KEYDOWN(BUTTON_LEFT))
			{
				spaceship.col -= spaceship.speed;
				if (spaceship.col < 0)
				{
					spaceship.col = spaceship.oldCol;
				}
			}
			if (KEYDOWN(BUTTON_UP))
			{
				spaceship.row -= spaceship.speed;
				if (spaceship.row < 0)
				{	
					spaceship.row = spaceship.oldRow;
				}
			}
			spaceship.oldRow = spaceship.row;
			spaceship.oldCol = spaceship.col;
			for (int i = 0; i < numAsteroids; i++)
			{
				asteroids[i].oldRow = asteroids[i].row;
				asteroids[i].oldCol = asteroids[i].col;
			}
			
			for (int i = 0; i < numAsteroids; i++)
			{
				drawImage4(asteroids[i].row, asteroids[i].col, 
					asteroids[i].width, asteroids[i].height, asteroid);
			}
			drawImage4(deathRow, deathCol, DEATHSTAR_R_WIDTH,
				DEATHSTAR_R_HEIGHT, deathstar_r);
			drawImage4(spaceship.row, spaceship.col, spaceship.width,
				spaceship.height, spaceship_r);
			flipPage();
			PALETTE[0] = 0;
			fillScreen(0);
			
		}
	}
}




	


