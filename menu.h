#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
#include "runner.h"

byte flameid = 0;
boolean showRunner = false;

void drawCandle(byte x, byte y)
{
	if (geo.framesElapsed(4))
	{
		flameid = random(0, 24);
	}
	sprites.drawSelfMasked(x, y + 34, candleTip, 0);
	sprites.drawSelfMasked(x + 4, y + 18, candleFlame, flameid);
}

void stateMenuIntro()
{
	globalCounter++;
	sprites.drawSelfMasked(34, 4, T_arg, 0);
	if (globalCounter > 180)
	{
		globalCounter = 0;
		gameState = STATE_MENU_MAIN;
	}
};

void stateMenuMain()
{
	runnerY = 0;
	if (geo.framesElapsed(4))
		runnerX += 4;
	if (runnerX > 127)
	{
		runnerX = -127;
		showRunner = !showRunner;
	}
	sprites.drawSelfMasked(16, 0, menuTitle, 0);
	sprites.drawSelfMasked(49, 26, menuItems, 0);
	sprites.drawSelfMasked(89, 50, menuYesNo, geo.soundEnabled());
	drawCandle(29, (menuSelection - 2) * 8);
	for (byte i = 2; i < 6; i++)
	{
		if (menuSelection != i)
		{
			sprites.drawErase(49, (i * 8) + 10, menuShade, 0);
			sprites.drawErase(82, (i * 8) + 10, menuShade, 0);
		}
	}
	if (showRunner)
	{
		sprites.drawSelfMasked(runnerX, -2, spotLight, 0);
		drawRunner();
	}
	if (geo.justPressedButton(BTN_UP) && (menuSelection > 2))
		menuSelection--;
	else if (geo.justPressedButton(BTN_DOWN) && (menuSelection < 5))
		menuSelection++;
	else if (geo.justPressedButton(BTN_A) || geo.justPressedButton(BTN_B))
	{
		if (menuSelection != 5)
			gameState = menuSelection;
		else
		{
			if (geo.soundEnabled())
				geo.soundOff();
			else
				geo.soundOn();
			// geo geo.audio.saveOnOff();
		}
	}
}

void stateMenuHelp()
{
	if (geo.justPressedButton(BTN_A) || geo.justPressedButton(BTN_B))
		gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
	sprites.drawSelfMasked(16, 0, menuTitle, 0);
	sprites.drawSelfMasked(15, 25, menuInfo, 0);
	if (geo.justPressedButton(BTN_A) || geo.justPressedButton(BTN_B))
		gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
	// placeHolder
}

void stateMenuPlay()
{
	gameState = STATE_GAME_INIT_LEVEL;
}

#endif
