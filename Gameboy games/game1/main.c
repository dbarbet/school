#include "mylib.h"
#include "text.h"
#include "racecar.h"
#include "loseScreen.h"
#include "winScreen.h"
#include "banana.h"
#include <stdlib.h>
typedef struct
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	int width;
	int height;
} CAR;

typedef struct
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	int width;
	int height;
	int makeAnotherBanana;
	int bananaFlying;
	int lowerBound;
} BANANA;

int main(void)
{
	REG_DISPCTL = 3 | (1<<10);
	CAR mainCar;
	int numBananas = 10;
	BANANA bananas[numBananas];
	int lower = 10;
	//Set banana attributes
	for (int i = 0; i < numBananas; i++)
	{
		
		bananas[i].lowerBound = lower;
		bananas[i].col = rand() % 23 + lower;
		bananas[i].oldCol = bananas[i].col;
		bananas[i].width = BANANA_WIDTH;
		bananas[i].height = BANANA_HEIGHT;
		bananas[i].makeAnotherBanana = rand() % 50;
		bananas[i].bananaFlying = 0;
		lower += 23;
	}
	//Speed of bananas
	int speed = 3;
	//How long until winning
	int timer = 10;
	//Set car attributes
	mainCar.row = 129;
	mainCar.col = 114;
	mainCar.oldRow = 129;
	mainCar.oldCol = 114;
	mainCar.width = RACECAR_WIDTH;
	mainCar.height = RACECAR_HEIGHT;
	//Set if lose screen is shown
	int showLoseScreen = 0;
	int notShownLoss = 1;
	//Set if win screen is shown
	int showWinScreen = 0;
	int notShownWin = 1;
	//Clear Screen
	fillScreen(WHITE);
	while(1) {
		//Decide if showing lose screen, win screen, or continue with game
		if (showLoseScreen && notShownLoss)
		{
			//drawloseimg
			drawImage3(0, 0, LOSESCREEN_WIDTH, LOSESCREEN_HEIGHT, loseScreen);
			drawString(130, 10, "You Hit A Banana And Crashed!!", RED);
			drawString(140, 10, "Press Start to try again.", RED);
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
			drawImage3(0, 0, WINSCREEN_WIDTH, WINSCREEN_HEIGHT, winScreen);
			drawString(130, 10, "You Avoided All Bananas. Congrats!!", RED);
			drawString(140, 10, "Press Start to play again.", RED);
			notShownWin = 0;
		} else if (showWinScreen)
		{
			//Wait for input
			if (KEYDOWN(BUTTON_START))
			{
				main();
			}
		} else
		{
			waitForVBlank();
			//Determine if bananas are at end of screen
			for (int i = 0; i < numBananas; i++)
			{
				if (bananas[i].row >= 159)
				{
					bananas[i].bananaFlying = 0;
					bananas[i].makeAnotherBanana = rand() % 50;
					//Determine if last banana has made it off of screen
					if (i == numBananas - 1)
					{
						timer--;
					}
				}
			}
			//Determine if game should make new projectile
			for (int i = 0 ; i < numBananas; i++)
			{
				if (bananas[i].bananaFlying == 0)
				{
					bananas[i].row = 0;
					bananas[i].oldRow = 0;
					bananas[i].col = rand() % 23 + bananas[i].lowerBound;
					drawImage3(bananas[i].row, bananas[i].col, bananas[i].width, bananas[i].height, banana);
					bananas[i].bananaFlying = 1;
				} else if (bananas[i].makeAnotherBanana >= 50)
				{
					drawRect(bananas[i].oldRow, bananas[i].col, bananas[i].width, bananas[i].height, WHITE);
					drawImage3(bananas[i].row, bananas[i].col, bananas[i].width, bananas[i].height, banana);
					bananas[i].row = bananas[i].row + speed;
				}
			}
			//Draw wave timer and line
			plotLine(149, 0, 149, 239, BLACK);
			if (timer == 10)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 10", BLACK);
			} else if (timer == 9)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 9", BLACK);
			} else if (timer == 8)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 8", BLACK);
			} else if (timer == 7)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 7", BLACK);
			} else if (timer == 6)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 6", BLACK);
			} else if (timer == 5)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 5", BLACK);
			} else if (timer == 4)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 4", BLACK);
			} else if (timer == 3)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 3", BLACK);
			} else if (timer == 2)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 2", BLACK);
			} else if (timer == 1)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 1", BLACK);
			} else if (timer == 0)
			{
				drawRect(151, 0, 240, 10, WHITE);
				drawString(151, 0, "WAVES LEFT: 0", BLACK);
			}
				
			//Draw over old main
			drawRect(mainCar.oldRow, mainCar.oldCol, mainCar.width, mainCar.height, WHITE);
			//Draw new main character
			drawImage3(mainCar.row, mainCar.col, mainCar.width, mainCar.height, racecar);
			//Calculate bounding boxes of cars and bananas, accounting for oversized image
			int carTop = mainCar.row + 2;
			int carBot = mainCar.row + mainCar.height;
			int carLeft = mainCar.col + 2;
			int carRight = mainCar.col + mainCar.width - 2;
			for (int i = 0; i < numBananas; i++)
			{
				int bananaTop = bananas[i].row + 2;
				int bananaBot = bananas[i].row + bananas[i].height;
				int bananaLeft = bananas[i].col + 2;
				int bananaRight = bananas[i].col + bananas[i].width - 2;
				if (checkIntersection(carBot, carTop, carLeft, carRight, bananaBot, bananaTop, bananaLeft, bananaRight))
				{
					showLoseScreen = 1;
				}
			}
			//Set main character row = oldrow...
			mainCar.oldRow = mainCar.row;
			mainCar.oldCol = mainCar.col;
			//Check for button presses
			if (KEYDOWN(BUTTON_DOWN))
			{		
				mainCar.row += 2;
				if (mainCar.row > 149 - mainCar.height + 1)
				{
					mainCar.row = mainCar.oldRow;
				}
			}
			if (KEYDOWN(BUTTON_RIGHT))
			{
				mainCar.col += 2;
				if (mainCar.col > 239 - mainCar.width + 1)
				{
					mainCar.col = mainCar.oldCol;
				}
			}
			if (KEYDOWN(BUTTON_LEFT))
			{
				mainCar.col -= 2;
				if (mainCar.col < 0)
				{
					mainCar.col = mainCar.oldCol;
				}
			}
			if (KEYDOWN(BUTTON_UP))
			{
				mainCar.row -= 2;
				if (mainCar.row < 15)
				{	
					mainCar.row = mainCar.oldRow;
				}
			}
		
			
			drawRect(mainCar.oldRow, mainCar.oldCol, mainCar.width, mainCar.height, WHITE);
			//Draw new main character
			drawImage3(mainCar.row, mainCar.col, mainCar.width, mainCar.height, racecar);
			//Old row = row...
			mainCar.oldRow = mainCar.row;
			mainCar.oldCol = mainCar.col;
			//Determine how to draw projectiles
			for (int i = 0 ; i < numBananas; i++)
			{
				if (bananas[i].bananaFlying == 0)
				{
					bananas[i].row = 0;
					bananas[i].oldRow = 0;
					drawImage3(bananas[i].row, bananas[i].col, bananas[i].width, bananas[i].height, banana);
					bananas[i].bananaFlying = 1;
				} else if (bananas[i].makeAnotherBanana >= 100)
				{
					drawRect(bananas[i].oldRow, bananas[i].col, bananas[i].width, bananas[i].height, WHITE);
					drawImage3(bananas[i].row, bananas[i].col, bananas[i].width, bananas[i].height, banana);
				}
			}
			//set projectile oldrow = row...
			for (int i = 0; i < numBananas; i++)
			{
				bananas[i].oldRow = bananas[i].row;
				bananas[i].makeAnotherBanana = bananas[i].makeAnotherBanana + 1;
			}
			//Determine if win condition met
			if (timer == 0)
			{
				showWinScreen = 1;
			}
		}
	}
}


	


