#pragma once

#ifdef FILETRANSFERDLL_EXPORTS  // ќпредел€етс€ при компил€ции DLL
#define FILETRANSFERDLL_API __declspec(dllexport)
#else
#define FILETRANSFERDLL_API __declspec(dllimport)
#endif

#include <Windows.h>

extern "C" FILETRANSFERDLL_API LPWSTR makeRandomFileName(int sizeOfName, LPCWSTR typeName, int sizeOfTypeName);