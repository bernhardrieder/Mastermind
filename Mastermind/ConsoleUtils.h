#pragma once

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

namespace ConsoleUtils
{
	//------------------------------------------------------------------------------------------------
	// global variables & constants:
	//------------------------------------------------------------------------------------------------
	const char FilledRectangleSymbol = 219;		// ASCII code of filled rectangle
	const char FilledSmileySymbol = 2;		// ASCII code of filled smiley -> not working
	const char UnfilledSmileySymbol = 1;		// ASCII code of unfilled smiley -> not working


	//------------------------------------------------------------------------------------------------
	// utility functions for text attributes:
	//------------------------------------------------------------------------------------------------
	namespace Colors
	{
		enum Color
		{
			BLACK = 0, DARKBLUE, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE
		};
	}
	static Colors::Color CurrentConsoleOutputColor = Colors::WHITE;

	namespace KeyCodes
	{
		// see https://en.wikipedia.org/wiki/ASCII
		enum KeyCode
		{
			Backspace = 8,
			Enter = 13,
			ESC = 27,
			C = 67,
			G = 71,
			H = 72,
			R = 82,
			S = 83,
			c = 99,
			g = 103,
			h = 104,
			r = 114,
			s = 115
		};
	}

	inline void setTextColor(const Colors::Color& c)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
		CurrentConsoleOutputColor = c;
	}

	inline void setCursorPosition(const int& x, const int& y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}


	inline void getCursorPosition(int &outX, int &outY)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			outX = csbi.dwCursorPosition.X;
			outY = csbi.dwCursorPosition.Y;
		}
	}


	inline void offsetCursorInLine(const int& offset)
	{
		int x, y;
		getCursorPosition(x, y);
		setCursorPosition(x + offset, y);
	}
}