#include "Cursor.h"

Cursor::Cursor(const int& xPos, const int& yPos, int blinkTime)
	:blinkTime(blinkTime)
{
	position.X = xPos;
	position.Y = yPos;
}

Cursor::~Cursor()
{
	
}

void Cursor::showCursor(bool showFlag, HANDLE out)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}