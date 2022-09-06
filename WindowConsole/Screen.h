#pragma once
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <vector>
#include "Cursor.h"
#ifndef SCREEN_H_
#define SCREEN_H_

using namespace std;

class Screen {
public:
	Screen(const int& fps, vector<pair<int,int>> matrix);
	~Screen();

	void screenFlip();
	void screenRender();
	void screenUpdate(int index);

private:
	static const int SCREEN_HANDLE_NUM = 2;

	HANDLE screenHandle[SCREEN_HANDLE_NUM];
	HANDLE consoleOut;

	CONSOLE_SCREEN_BUFFER_INFO CSBI;
	SMALL_RECT SCREEN_SIZE;

	CHAR_INFO* screenBuffer;
	COORD screenSize;
	COORD origin;

	int activeIndex = 0;

	bool recentlyWrite;

	int fps;
	bool pause;
	vector<COORD> outputMatrix;
};
#endif