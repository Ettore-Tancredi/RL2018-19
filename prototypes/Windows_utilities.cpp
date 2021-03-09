#include "stdafx.h"
#include "Windows_Utilities.h"
#include "Windows.h"



void Windows_Utilities::get_stdout_handle()
{
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}


void Windows_Utilities::cls()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdout, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	if (!FillConsoleOutputAttribute(hStdout, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	SetConsoleCursorPosition(hStdout, coordScreen);
}

void Windows_Utilities::gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(hStdout, c);
}
