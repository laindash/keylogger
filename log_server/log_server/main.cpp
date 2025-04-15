#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <vector>
#include <filesystem>


using namespace std;
namespace fs = std::filesystem;

const short BUFF_SIZE = 1024;

void ensureDirectoryExists(const string& path) {
    if (!fs::exists(path)) {
        fs::create_directories(path);
    }
}

void receiveFile(SOCKET clientSocket, const string& savePath) {
    char buffer[BUFF_SIZE];

    // �������� ������ ����� �����
    int fileNameSize = 0;
    int bytesReceived = recv(clientSocket, reinterpret_cast<char*>(&fileNameSize), sizeof(fileNameSize), 0);
    if (bytesReceived <= 0) {
        cerr << "������ ��������� ������� ����� �����" << endl;
        return;
    }

    // ������� ����� ����� ������� ����� �����
    memset(buffer, 0, sizeof(buffer));

    // �������� ��� �����
    bytesReceived = recv(clientSocket, buffer, fileNameSize, 0);
    if (bytesReceived <= 0) {
        cerr << "������ ��������� ����� �����" << endl;
        return;
    }

    string fileName(buffer, bytesReceived);
    cout << "�������� ��� �����: " << fileName << endl;

    ofstream outFile(savePath + fileName, ios::binary);
    if (!outFile) {
        cerr << "�� ������� ������� ���� ��� ������" << endl;
        return;
    }

    // ����� ������ ����� � ������ �� ����
    int bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, BUFF_SIZE, 0)) > 0) {
        outFile.write(buffer, bytesRead);
    }

    if (bytesRead == SOCKET_ERROR) {
        cerr << "������ ��� ��������� �����" << endl;
    }
    else {
        cout << "���� ������� ������� � ��������: " << savePath + fileName << endl;
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    const char IP_SERV[] = "127.0.0.1";
    const int PORT_NUM = 54000;

    WSADATA wsData;
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
        cerr << "������ ������������� WinSock: " << WSAGetLastError() << endl;
        return 1;
    }

    SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);
    if (ServSock == INVALID_SOCKET) {
        cerr << "������ �������� ������: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in servInfo = {};
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr.s_addr = inet_addr(IP_SERV);
    servInfo.sin_port = htons(PORT_NUM);

    if (bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo)) != 0) {
        cerr << "������ �������� ������: " << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }

    listen(ServSock, SOMAXCONN);

    ensureDirectoryExists("C:\\ReceivedFiles\\");

    cout << "������ ������� � ������� �����������..." << endl;

    int countConnections = 0;

    while (true) {
        sockaddr_in clientInfo;
        int clientInfoSize = sizeof(clientInfo);

        SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfoSize);
        if (ClientConn == INVALID_SOCKET) {
            cerr << "������ ����������� �������: " << WSAGetLastError() << endl;
            continue;
        }

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

        if (countConnections == 0) {
            cout << "������ ����������� � IP �������: " << clientIP << endl;
            countConnections++;
        }

        // ���� ����� �� �������
        receiveFile(ClientConn, "C:\\ReceivedFiles\\");

        // �������� ���������� � ��������
        shutdown(ClientConn, SD_BOTH);
        closesocket(ClientConn);
    }

    closesocket(ServSock);
    WSACleanup();
    return 0;
}
