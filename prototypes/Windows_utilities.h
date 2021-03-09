#include "Windows.h"

#ifndef WINDOWS_UTILITIES_H
#define  WINDOWS_UTILITIES_H


class Windows_Utilities
{
private:
	HWND hwnd;
	HANDLE hStdout;

public:
	void cls();
	void get_stdout_handle();
	void gotoxy(int, int);

};



#endif // !WINDOWS_UTILITIES_H


