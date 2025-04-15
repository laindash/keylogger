#include "pch.h"
#include <cstdlib>
#include <ctime>
#include "MakeFileDLL.h"



LPWSTR makeRandomFileName(int sizeOfName, LPCWSTR typeName, int sizeOfTypeName) {
    const int pathSize = 7;
    wchar_t path[pathSize] = L"C:\\CW\\";
    LPWSTR string = new wchar_t[sizeOfName + sizeOfTypeName + pathSize];
    for (int i = 0; i < pathSize - 1; i++) {
        string[i] = path[i];
    }
    for (int i = 0; i < sizeOfName; i++) {
        string[i + pathSize - 1] = static_cast<wchar_t>(rand() % 25 + 65);
    }
    for (int i = 0; i < sizeOfTypeName; i++) {
        string[i + sizeOfName + pathSize - 1] = typeName[i];
    }

    return string;
}
