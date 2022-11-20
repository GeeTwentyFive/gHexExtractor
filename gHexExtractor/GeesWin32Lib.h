#pragma once
#include <Windows.h>
#define NELEMS(x) ((sizeof(x) / sizeof(x[0])))
#define CONSOLE_MAX_OUTPUT 8191
#define MB_64 67108864

void gPrintA(const char* text);
void gPrintW(const wchar_t* text);
bool gFileExistsA(LPCSTR szPath);
bool gFileExistsW(LPCTSTR szPath);
int gNumOfDigits(int input);