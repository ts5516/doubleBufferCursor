#include <iostream>
#include <vector>
#include "Screen.h"

using namespace std;

vector<pair<int, int>> spiralOrder(int height, int width)
{
    int m = height, n = width;
    vector<pair<int, int>> ans;
    vector<vector<bool> > seen(m, vector<bool>(n, false));

    if (m == 0)
        return ans;

    int dr[] = { 0, 1, 0, -1 };
    int dc[] = { 1, 0, -1, 0 };

    int x = 0, y = 0, di = 0;

    for (int i = 0; i < m * n; i++) {
        ans.push_back(make_pair(y,x));
        seen[x][y] = true;
        int newX = x + dr[di];
        int newY = y + dc[di];

        if (0 <= newX && newX < m && 0 <= newY && newY < n
            && !seen[newX][newY]) {
            x = newX;
            y = newY;
        }
        else {
            di = (di + 1) % 4;
            x += dr[di];
            y += dc[di];
        }
    }

    return ans;
}

void gameStart(int& width, int& height, const int& speed)
{
    vector<pair<int, int>> spiralMatrix = spiralOrder(height, width);

    Screen screen(speed, spiralMatrix);
    screen.screenRender();
}

int main()
{
	int width, height, speed;
	cout << "가로, 세로, 속도\n";
	cin >> width;
	cin >> height;
	cin >> speed;

	gameStart(width, height, speed); //game start
}