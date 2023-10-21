#pragma once
#include <Windows.h>
#include <Windowsx.h>
#include "CHLimiter.h"
#include <vector>
class CBall
{
	HBRUSH hBrush;
	DWORD prev_ticks;
	double x, y; // ���������� ������ �����
	double vx, vy; // �������� �� ���� ����
	double r; // ������ �����
	RECT bounds;
	int lim_quantity;
	int lims_size;
	CHLimiter** lims;
public:
	CBall(double x, double y, double vx, double vy, double r);
	~CBall();
	void Draw(HDC dc);
	void Move(DWORD ticks);
	void SetBounds(RECT bnds);
	void SetHLimiters(CHLimiter** l, int size);
};

