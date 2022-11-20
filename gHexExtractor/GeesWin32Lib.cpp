#include "GeesWin32Lib.h"
#include <Windows.h>

void gPrintA(const char* text) {
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), NULL, NULL);
}

void gPrintW(const wchar_t* text) {
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), text, wcslen(text), NULL, NULL);
}

bool gFileExistsA(LPCSTR szPath) {
	DWORD dwAttrib = GetFileAttributesA(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool gFileExistsW(LPCTSTR szPath) {
	DWORD dwAttrib = GetFileAttributesW(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int gNumOfDigits(int input) {
	int n = 1;
	int in = input;

	while (in > 9) {
		in /= 10;
		n++;
	}

	return n;
}