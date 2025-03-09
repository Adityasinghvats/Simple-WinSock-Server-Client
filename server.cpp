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

    //socket creation
    SOCKET serversocket = INVALID_SOCKET;
    serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serversocket == INVALID_SOCKET) {
        cout << "Error at socket():" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket is OK" << endl;
    }
    //closesocket(serversocket);

    //bind
    int port = 55555;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serversocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed:" << WSAGetLastError() << endl;
        closesocket(serversocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "bind() is OK" << endl;
    }

    //Listen on socket
    if (listen(serversocket, 1) == SOCKET_ERROR) {
        cout << "listen() : error listening on socket" << WSAGetLastError() << endl;
    }
    else cout << "Listen() is OK, I'm waiting for connections..." << endl;

    //accept the connection
    SOCKET acceptSocket;
    acceptSocket = accept(serversocket, nullptr, nullptr);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept failed:" << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    else {
        cout << "accept() is working" << endl;
        cout << "Client is conencted" << endl;
    }
    system("pause");
    WSACleanup();
    return 0;
}