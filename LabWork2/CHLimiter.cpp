#include "CHLimiter.h"

CHLimiter::CHLimiter(int x0, int y0, int x1, int y1) {
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
}

CHLimiter::~CHLimiter() {

}

void CHLimiter::Draw(HDC dc) {
	::MoveToEx(dc, this->x0, this->y0, NULL); // перемещает позицию рисования
	::LineTo(dc, this->x1, this->y1); // отрисовывает линию с текущей позиции до указанной
}

int CHLimiter::GetX0() {
	return this->x0;
}
int CHLimiter::GetX1() {
	return this->x1;
}
int CHLimiter::GetY0() {
	return this->y0;
}
int CHLimiter::GetY1() {
	return this->y1;
}
void CHLimiter::MoveX(int inc) {
	this->x0 -= inc;
	this->x1 -= inc;
}
void CHLimiter::MoveY(int inc) {
	this->y0 -= inc;
	this->y1 -= inc;
}
