#include <Windows.h>
#include <Windowsx.h>
#include <vector>
#include "CBall.h"
#include "CHLimiter.h"
using namespace std;

HINSTANCE g_hInstance;
int g_nCmdShow;
HWND g_mainWnd;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

CBall b1(10.0, 10.0, 100.0, 100.0, 10.0);

// Изменять код нужно только в этом месте 

//===============================
//           x0        y0         x1         y1
CHLimiter h1(200 - 80, 200 + 80, 200 + 80, 200 + 80);
//CHLimiter h2(350, 100, 350, 200);
CHLimiter h3(200 - 150, 200 - 80, 200 - 30, 200 - 80); // Верхняя левая горизонтальная
CHLimiter h4(200, 200 + 87, 200, 200 + 200); // Центр низ вертикальная
CHLimiter h5(200 - 90, 200 - 200, 200 - 90, 200 - 87); // Верхняя левая вертикальная
CHLimiter h6(200 + 30, 200 - 40, 200 + 150, 200 - 40);
CHLimiter h7(200 + 90, 200 - 200, 200 + 90, 200 - 47);
int arr_size = 7 - 1; // вводим размер массива (обновлять при добавлении новых препядствий)
CHLimiter** lims2 = new CHLimiter * [arr_size] { &h1, & h3, & h4, & h5, & h6, & h7 };

//===============================

BOOL InitAppClass() {
	ATOM class_id;
	WNDCLASS wc = { 0 };
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(105, 105, 105))); //GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = L"LabWork2";
	class_id = RegisterClass(&wc);

	if (class_id != 0)
		return TRUE;
	return FALSE;
}

BOOL InitWindow() { //функция создания окна
	g_mainWnd = CreateWindow(L"LabWork2", L"PONG", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 0, 0, g_hInstance, 0);
	if (!g_mainWnd) return FALSE;
	ShowWindow(g_mainWnd, g_nCmdShow);
	UpdateWindow(g_mainWnd);
	return TRUE;
}
void OnIdle() {
	DWORD ticks = GetTickCount64();

	b1.Move(ticks);
	InvalidateRect(g_mainWnd, NULL, TRUE);
}
WPARAM StartMessageLoop() { // Цикл обработки сообщений
	MSG msg;
	while (1) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(1); // пауза между обновлениями экрана в 20 мс
			OnIdle();
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { // (идентификатор окна, где сгенерировано сообщение; тип сообщения; параметры сообщения) функция окна
	switch (msg) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps); // функция берет контекст рисования у системы
		b1.Draw(hDC);
		for (int i = 0; i < arr_size; i++)
		{
			lims2[i]->Draw(hDC);
		}
		EndPaint(hWnd, &ps); // функция возвращает контекст рисования системе
		return 0;
	}
	case WM_SIZE:
	{
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = HIWORD(lParam);
		rect.right = LOWORD(lParam);
		b1.SetBounds(rect);
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_UP:
			lims2[1]->MoveY(3);
			return 0;
		case VK_LEFT:
			lims2[1]->MoveX(3);
			return 0;
		case VK_DOWN:
			lims2[1]->MoveY(-3);
			return 0;
		case VK_RIGHT:
			lims2[1]->MoveX(-3);
			return 0;
		}
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow) {
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;

	if (!InitAppClass())
		return 0;
	if (!InitWindow())
		return 0;

	RECT cr;

	GetClientRect(g_mainWnd, &cr);
	b1.SetBounds(cr);
	b1.SetHLimiters(lims2, arr_size);
	return StartMessageLoop();
}
