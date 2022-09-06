#include "Screen.h"

Screen::Screen(const int& fps, vector<pair<int, int>> matrix)
	:fps(fps), pause(false),
	recentlyWrite(false),
	consoleOut(GetStdHandle(STD_OUTPUT_HANDLE))
{
	GetConsoleScreenBufferInfo(consoleOut, &CSBI);
	SCREEN_SIZE = CSBI.srWindow;
	screenBuffer = (CHAR_INFO*)malloc(
		sizeof(CHAR_INFO) * (SCREEN_SIZE.Right * SCREEN_SIZE.Bottom));

	//console output save
	screenSize = { SCREEN_SIZE.Right, SCREEN_SIZE.Bottom };
	origin = { 0,0 };

	COORD cursor = { CSBI.dwCursorPosition.X, CSBI.dwCursorPosition.Y };
	ReadConsoleOutput(consoleOut, screenBuffer,
		screenSize, origin, &SCREEN_SIZE);

	for (pair<int, int> elm : matrix)
	{
		COORD crd = { cursor.X + elm.first*2, cursor.Y + elm.second };
		outputMatrix.push_back(crd);
	}

	for (int i = 0; i < SCREEN_HANDLE_NUM; i++)
	{
		screenHandle[i] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0, NULL,
			CONSOLE_TEXTMODE_BUFFER, NULL);

		WriteConsoleOutput(screenHandle[i], screenBuffer,
			screenSize, origin, &SCREEN_SIZE);

		Cursor::showCursor(false, screenHandle[i]);
	}
	
	SetConsoleActiveScreenBuffer(screenHandle[activeIndex]);
}

Screen::~Screen()
{
	for(int i = 0; i< SCREEN_HANDLE_NUM; i++)
		CloseHandle(screenHandle[i]);
	CloseHandle(consoleOut);

	delete[] screenBuffer;
}

void Screen::screenRender()
{
	clock_t startTime = clock(), blinkTime = clock(), endTime;
	int index = 0;

	while (true)
	{
		if (_kbhit() && _getch() == 32)
			pause = !pause;
		
		endTime = clock();
		if (endTime - startTime > 1000 / fps && !pause) {
			screenUpdate(index++);
			startTime = endTime;
		}

		if (endTime - blinkTime > 500) {
			screenFlip();
			blinkTime = endTime;
		}
	}
}

void Screen::screenFlip()
{
	recentlyWrite = false;
	activeIndex = 1 - activeIndex; // 0, 1 flip
	SetConsoleActiveScreenBuffer(screenHandle[activeIndex]);
}

void Screen::screenUpdate(int index)
{
	DWORD dw;
	std::string str = "бс";

	WriteConsoleOutput(screenHandle[activeIndex], screenBuffer,
		screenSize, origin, &SCREEN_SIZE);
	WriteConsoleOutput(screenHandle[1-activeIndex], screenBuffer,
		screenSize, origin, &SCREEN_SIZE);

	SetConsoleCursorPosition(
		screenHandle[activeIndex], outputMatrix[index]);
	WriteFile(
		screenHandle[activeIndex],
		str.c_str(), str.size(),
		&dw, NULL);

	ReadConsoleOutput(screenHandle[activeIndex], screenBuffer,
		screenSize, origin, &SCREEN_SIZE);
}