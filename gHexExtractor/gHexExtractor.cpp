#include <Windows.h>
#include "gHexExtractor.h"
#include "GeesWin32Lib.h"
//#define MB_384 402653184

int gHexExtract(const char* target, const char* output) {

	if (!gFileExistsA(target)) {
		return 1;	// File not found.
	}

	if (gFileExistsA(output)) {
		return 2;	// File at path <output> already exists
	}

	HANDLE tHandle = CreateFileA(target, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	DWORD tFileSize = GetFileSize(tHandle, NULL);

	if (tFileSize > MB_64) {
		CloseHandle(tHandle);
		return 3;	// Target file is greater than 64MB
	}

	unsigned char* input = (unsigned char*)malloc(MB_64);

	if (!ReadFile(tHandle, input, tFileSize, NULL, NULL)) {
		CloseHandle(tHandle);
		free(input);
		return 4;	// Unable to read from target file
	}

	CloseHandle(tHandle);

	unsigned char* hexOutput = (unsigned char*)malloc((MB_64 * 6) + ((MB_64 / 16) * 2) + 64);	// 6 out chars/1 in byte, and newline+tab every 16 chars, and some extra chars at beginning and end
	int outSize = 0;

	memcpy(hexOutput, (unsigned char*)"const unsigned char payload[", 28);
	outSize += 28;

	unsigned char* tFileSizeChars = (unsigned char*)malloc(sizeof(int));
	wsprintfA((LPSTR)tFileSizeChars, "%d", tFileSize);
	memcpy(hexOutput + outSize, tFileSizeChars, gNumOfDigits(tFileSize));
	free(tFileSizeChars);
	outSize += gNumOfDigits(tFileSize);

	memcpy(hexOutput + outSize, (unsigned char*)"] = {\n\t", 7);
	outSize += 7;

	int byteCount = 0;
	for (int i = 0; i < tFileSize; i++) {
		byteCount++;
		memcpy(hexOutput + outSize, (unsigned char*)"0x", 2);
		outSize += 2;
		wsprintfA((LPSTR)hexOutput+outSize, "%02x", input[i]);
		outSize += 2;

		if (i != tFileSize - 1) {
			memcpy(hexOutput + outSize, (unsigned char*)", ", 2);
			outSize += 2;

			if (byteCount >= 15) {
				memcpy(hexOutput + outSize, (unsigned char*)"\n\t", 2);
				outSize += 2;
				byteCount = 0;
			}
		}
	}

	memcpy(hexOutput + outSize, (unsigned char*)"};", 2);
	outSize += 2;

	free(input);

	HANDLE oHandle = CreateFileA(output, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(oHandle, hexOutput, outSize, NULL, NULL);

	CloseHandle(oHandle);

	free(hexOutput);

	return 0;	// Success!
}