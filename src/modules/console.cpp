#include "modules.h"
#include "../mem/memory.h"
#include "../game/Player.h"

HANDLE hConsole;
HWND hWindow;
RECT ConsoleRect;

int displayMode = 0;

using namespace std;

//fuck universal shits we on windows bitch
void ClearScreen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD homeCoords = { 0,0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)return;
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	))return;

	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	))return;

	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void initConsole() {
	HWND hWindow = GetConsoleWindow();

	GetWindowRect(hWindow, &ConsoleRect);
	MoveWindow(hWindow, ConsoleRect.left, ConsoleRect.top, 305, 210, TRUE);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("");
	SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// retrieve screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	// current screen buffer size
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	// to remove the scrollbar, make sure the window height matches the screen buffer height
	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	// set the new screen buffer dimensions
	SetConsoleScreenBufferSize(hOut, newSize);

	ClearScreen();
	SetConsoleTextAttribute(hConsole, 12);
	cout << "    __ _________  ______ ______" << endl;
	cout << "   / // /  _/ _ )/  _/ //_/  _/" << endl;
	cout << "  / _  // // _  |/ // ,< _/ /  " << endl;
	cout << " /_//_/___/____/___/_/|_/___/ ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "v";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "2 " << endl << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "  moduleBase -> " << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "  face -> " << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "  action -> " << endl << endl;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "                  END ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Switch side";
}

void updateConsole() {

	while (run) {
		this_thread::sleep_for(chrono::milliseconds(2));

		setCursorPosition(16, 5);
		cout << moduleBase;
		setCursorPosition(10, 6);
		cout << p1.FacingLeft;
		setCursorPosition(11, 6);
		SetConsoleTextAttribute(hConsole, 15);
		cout << " | ";
		setCursorPosition(14, 6);
		SetConsoleTextAttribute(hConsole, 12);
		cout << p2.FacingLeft;
		setCursorPosition(12, 7);
		cout << "                           ";
		setCursorPosition(12, 7);
		cout << p2.cAction;
		setCursorPosition(2, 9);
		SetConsoleTextAttribute(hConsole, 15);
		cout << "----------------";
		setCursorPosition(2, 9);
		SetConsoleTextAttribute(hConsole, 12);
		switch (displayMode) {
		case -1:
			displayMode = 3;
			break;
		case 0:
			cout << p1.cSprite;
			break;
		case 1:
			cout << "d" << p1.Distance;
			break;
		case 2:
			cout << "x" << p1.Position.X;
			break;
		case 3:
			cout << "y" << p1.Position.Y;
			break;
		case 4:
			displayMode = 0;
			break;
		}

	}

}

void modules::console() noexcept 
{
	initConsole();
	ShowConsoleCursor(false);

	thread{ updateConsole }.detach();

	while (run) {

		if (GetAsyncKeyState(VK_DELETE)) { run = false; }

		if (GetAsyncKeyState(VK_PRIOR)) { displayMode--; this_thread::sleep_for(chrono::milliseconds(150)); }

		if (GetAsyncKeyState(VK_NEXT)) { displayMode++; this_thread::sleep_for(chrono::milliseconds(150)); }
		
	}
}

