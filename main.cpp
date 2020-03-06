//2020.01.05 
//add = block_rotate, overlap_check



#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void star_move(HDC hdc, int x, int y);
void draw_background(HDC hdc);
void delete_block(HDC hdc);
void make_block(HDC hdc);
int overlap_x_y();
void rotate_block();


int x = 4;
int y = 4;
int prev_x = 4;
int prev_y = 4;


int back[22][12] = {{1,1,1,1,1,1,1,1,1,1,1,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1,1,1} };

int orign_block[4][4] = {
	{0,0,0,0},
	{1,0,0,0},
	{1,1,1,1},
	{0,0,0,0}
};

int block[4][4] = {
	{0,0,0,0},
	{1,0,0,0},
	{1,1,1,1},
	{0,0,0,0}
};
//void enable_console()
//{
//	AllocConsole();
//	freopen("CONIN$", "r", stdin);
//	freopen("CONOUT$", "w", stdout);
//	freopen("CONOUT$", "w", stderr);
//}




/*  Make the class name into a global variable  */
char szClassName[] = "WindowsApp";

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nFunsterStil)

{
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

	//enable_console();

	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default color as the background of the window */
	//wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wincl.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));


	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		"Windows App",       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		240,                 /* The programs width */
		480,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	/* Make the window visible on the screen */
	ShowWindow(hwnd, nFunsterStil);

	printf("hwnd=%d\n", hwnd);



	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{	
	HDC hdc;
	int i, j;
	hdc = GetDC(hWnd);
	
	delete_block(hdc);
	y += 22;
	if (overlap_x_y() > 0) {
		y -= 22;
		make_block(hdc);

		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				if (block[j][i] == 1)
				{
					back[((y - 4) / 22) + j + 1][((x - 4) / 22) + i + 1] = 1;
				}
			}
		}
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				block[j][i] = orign_block[j][i];
			}
		}
		x = 4 + 22 * 2, y = 4;

		for (i = 0; i < 22; i++) {

		}
	}
	

	make_block(hdc);
	ReleaseDC(hWnd, hdc);
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HANDLE hTimer;
	static char *str;



	switch (message) {
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hwnd, 1, 1000, (TIMERPROC)TimerProc);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			hdc = GetDC(hwnd);

			delete_block(hdc);
			x -= 22;
			if (overlap_x_y() >= 1) {
				x += 22;
			}
			make_block(hdc);

			ReleaseDC(hwnd, hdc);
			break;
		case VK_RIGHT:
			hdc = GetDC(hwnd);

			delete_block(hdc);
			x += 22;
			if (overlap_x_y() >= 1) {
				x -= 22;
			}
			make_block(hdc);

			ReleaseDC(hwnd, hdc);
			break;
		case VK_UP:
			hdc = GetDC(hwnd);

			delete_block(hdc);
			y -= 22;
			if (overlap_x_y() >= 1) {
				y += 22;
			}
			make_block(hdc);

			ReleaseDC(hwnd, hdc);
			break;
		case VK_DOWN:
			hdc = GetDC(hwnd);

			delete_block(hdc);
			y += 22;
			if (overlap_x_y() >= 1) {
				y -= 22;
			}
			make_block(hdc);

			ReleaseDC(hwnd, hdc);
			break;

		case VK_SPACE:
			hdc = GetDC(hwnd);

			delete_block(hdc);
			rotate_block();
			make_block(hdc);

			ReleaseDC(hwnd, hdc);
			break;
		}
		//InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		draw_background(hdc);
		//star_move(hdc, x, y);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hwnd, message, wParam, lParam));

}


//void draw_background(HDC hdc)
//{
//	int i, j;
//
//	for (i = 0; i < 22; i++) {
//		for (j = 0; j < 12; j++) {
//			if (back[i][j] == 1)
//				TextOut(hdc, 50 + j * 10, 50 + i * 10, "*", 1);
//		}
//	}
//}

void star_move(HDC hdc, int x, int y)
{
	int i, j;

	TextOut(hdc, prev_x, prev_y, "  ", 2);
	TextOut(hdc, x, y, "*", 1);
	prev_x = x;
	prev_y = y;

}

void make_block(HDC hdc)
{
	int i, j;
	HPEN MyPen, OldPen;
	HBRUSH MyBrush, OldBrush;

	MyPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	OldPen = (HPEN)SelectObject(hdc, MyPen);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (block[i][j] == 1) {
				Rectangle(hdc, j * 22 +x, i * 22 +y, (j * 22 +x) + 19, (i*22 +y) + 19);
			}
			else {

			}
		}
	}
	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);



	prev_x = x;
	prev_y = y;
}

void delete_block(HDC hdc)
{
	int i, j;
	HPEN MyPen, OldPen;
	HBRUSH MyBrush, OldBrush;

	MyPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	OldPen = (HPEN)SelectObject(hdc, MyPen);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (block[i][j] == 1) {
				Rectangle(hdc,j * 22 + prev_x,i * 22 +prev_y, (j * 22 +prev_x) + 19,( i * 22 + prev_y )+ 19);
			}
			else {

			}
		}
	}
	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);



	prev_x = x;
	prev_y = y;
}

void draw_background(HDC hdc)
{
	int i, j;
	HBITMAP hBit, OldBit;
	BITMAP bit;
	HDC hMemDC;

	hMemDC = CreateCompatibleDC(hdc);

	//hBit=(HBITMAP)LoadImage(NULL,"tiger.bmp",IMAGE_BITMAP,
//		0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hBit = (HBITMAP)LoadImage(NULL, "tetris_background.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(bit), &bit);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, OldBit);
	DeleteObject(hBit);
	DeleteDC(hMemDC);

	//printf("bit.bmWidth = %d, bit.bmHeight= %d\n", bit.bmWidth, bit.bmHeight);
}

int overlap_x_y() {
	int i, j;
	int overlap_count = 0;

	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if ((block[j][i] == 1) && (back[((y-4)/22) + j +1][((x-4)/22) + i + 1] >= 1))
			{
				overlap_count++;
			}
		}
	}

	return overlap_count;
}

void rotate_block() {

	/*int x1, y1;

	int x_origin, y_origin;

	x_origin = (x-4)/22 - 2;
	y_origin = (y-4)/22 - 2;

	x1 = x_origin - (x-4)/22;
	y1 = y_origin - (y-4)/22;

	y = ((3 - y1) + x);
	x = (x1 + y);*/

	int i, j;
	int x1, y1;
	int clone_block[4][4] = { 0, };

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			clone_block[i][3 - j] = block[j][i];
		}
	}

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			block[j][i] = clone_block[j][i];
		}
	}
}
