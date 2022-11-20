#include "GeesWin32Lib.h"
#include "gHexExtractor.h"

int main(int argc, char* argv[]) {
	const char* USAGE = "\nUSAGE: gHexExtractor.exe <target> <output> (Max target file size: 64MB)\n";
	const char* TARGET_NOT_FOUND = "\nERROR: File at path <target> not found\n";
	const char* OUTPUT_ALREADY_EXISTS = "\nERROR: File at path <output> already exists\n";
	const char* TARGET_TOO_BIG = "\nERROR: Target file size is greater than 64MB\n";
	const char* TARGET_READ_FAIL = "\nERROR: Unable to read from file at path <target>\n";

	if (argc != 3) {
		gPrintA(USAGE);
		return 1;
	}

	int errorCode = gHexExtract(argv[1], argv[2]);

	if (errorCode != 0) {

		switch (errorCode) {
		case 1:
			gPrintA(TARGET_NOT_FOUND);
			break;

		case 2:
			gPrintA(OUTPUT_ALREADY_EXISTS);
			break;

		case 3:
			gPrintA(TARGET_TOO_BIG);
			break;

		case 4:
			gPrintA(TARGET_READ_FAIL);
			break;
		}

		return errorCode;
	}

	return 0;
}