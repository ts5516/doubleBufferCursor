#pragma once
#ifndef CURSOR_H_
#define CURSOR_H_
#include <Windows.h>
#include <time.h>
class Cursor {
public:
	Cursor(const int& xPos, const int& yPos, int blinkTime);
	~Cursor();
	
	static void showCursor(bool showFlag, HANDLE out);

	int getCursorBlinkTime()
	{
		return blinkTime;
	}

	COORD getCursor()
	{
		return position;
	}
	
	void setCursor(COORD crd)
	{
		position.X = crd.X;
		position.Y = crd.Y;
	}

private:
	COORD position;

	int blinkTime;
};
#endif