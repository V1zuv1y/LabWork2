#include "CBall.h"
#include "CHLimiter.h"
#include <vector>
CBall::CBall(double x, double y, double vx, double vy, double r) {

	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->r = r;
	this->prev_ticks = GetTickCount64();
	lims = new CHLimiter*[this->lims_size];
}
CBall::~CBall() {
	DeleteObject(hBrush);
}
void CBall::Draw(HDC dc) {
	HBRUSH hOldBrush;

	hOldBrush = SelectBrush(dc, hBrush);
	Ellipse(dc, x - r, y - r, x + r, y + r);
	SelectBrush(dc, hOldBrush);
}

void CBall::Move(DWORD ticks)
{
	// расчет времени между движениями в секундах
	double s_delta = ((double)(ticks - this->prev_ticks)) / 1000.0;

	// реакция шарика на границы экрана
	if ((this->x >= bounds.right - r) && (this->vx > 0))
		this->vx = -(this->vx);
	if ((this->x <= r) && (this->vx < 0))
		this->vx = -(this->vx);
	if ((this->y >= bounds.bottom - r) && (this->vy > 0))
		this->vy = -(this->vy);
	if ((this->y <= r) && (this->vy < 0))
		this->vy = -(this->vy);

	// Реакция на горизонтальное препядствие
	for (int i = 0; i < lims_size; i++) 
	{
		if (lims[i]->GetY0() == lims[i]->GetY1()) // проверка на горизонтальность препядствия
		{
			if (((this->x + r) >= lims[i]->GetX0()) && ((this->x - r) <= lims[i]->GetX1()))
			{
				if (this->vy > 0)
				{
					if (((lims[i]->GetY0() - this->y) < this->r) && ((lims[i]->GetY0() - this->y) > 0))
						this->vy = -(this->vy);
				}
				else if ((this->y - lims[i]->GetY0() < this->r) && ((this->y - lims[i]->GetY0()) > 0))
					this->vy = -(this->vy);
			}
		}
		// Реакция на вертикальное препядствие
		if (lims[i]->GetX0() == lims[i]->GetX1()) // проверка на вертикальность препядствия
		{
			if (((this->y + r) >= lims[i]->GetY0()) && ((this->y - r) <= lims[i]->GetY1()))
			{
				if (this->vx > 0)
				{
					if (((lims[i]->GetX0() - this->x) < this->r) && ((lims[i]->GetX0() - this->x) > 0))
						this->vx = -(this->vx);
				}
				else if ((this->x - lims[i]->GetX0() < this->r) && ((this->x - lims[i]->GetX0()) > 0))
					this->vx = -(this->vx);
			}
		}
	}
	this->prev_ticks = ticks;
	double dx = vx * s_delta;
	double dy = vy * s_delta;

	this->x += dx;
	this->y += dy;
}

void CBall::SetBounds(RECT bnds) {
	this->bounds = bnds;
}


void CBall::SetHLimiters(CHLimiter **l, int size) {
	for (int i = 0; i < size; i++)
	{
		this->lims[i] = l[i];
	}
	this->lims_size = size;
}