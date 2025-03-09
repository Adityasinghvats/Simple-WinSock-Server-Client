/*******************************************************************************
                     Created By : Aditya Singh Vats

              GitHub : -https ://github.com/Adityasinghvats                 

          Website : -https ://adityasinghvats.github.io/adix/  

*******************************************************************************/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "stdafx.h"

using namespace std;
int main() {
    //link the dll 
    WSADATA wsadata;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsadata);
    if (wsaerr != 0) {
        cout << "The winsock dll not found" << endl;
        return 0;
    }
    else {
        cout << "The winsock dll found" << endl;
        cout << "Status: " << wsadata.szSystemStatus << endl;
    }

    SOCKET clientsocket = INVALID_SOCKET;
    clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientsocket == INVALID_SOCKET) {
        cout << "Error at socket():" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket is OK" << endl;
    }

    int port = 55555;
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);
    if (connect(clientsocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "client connect() failed:" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "client connect(): is OK" << endl;
        cout << "Client can start sending and receiving data..." << endl;
    }
    system("pause");
    WSACleanup();
    return 0;
}


