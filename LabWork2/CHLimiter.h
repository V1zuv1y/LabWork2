#pragma once
#include <Windows.h>
#include <Windowsx.h>

class CHLimiter {
	int y0, y1;
	int x0, x1;
public:
	CHLimiter(int x0, int y0, int x1, int y1);
	~CHLimiter();
	void Draw(HDC dc);
	int GetX0();
	int GetX1();
	int GetY0();
	int GetY1();
	void MoveX(int inc);
	void MoveY(int inc);
};

