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
    //link the dll step 1
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
    //step 2
    SOCKET clientsocket = INVALID_SOCKET;
    clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientsocket == INVALID_SOCKET) {
        cout << "Error at socket():" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Socket is OK" << endl;
    }
    //step 3
    int port = 55555;
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);
    if (connect(clientsocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client connect() failed:" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client connect(): is OK" << endl;
        cout << "Client can start sending and receiving data..." << endl;
    }
    //step 4 send user data to server
    char buffer[200];
    cout << "Enter the message to send to server: ";
    cin.getline(buffer, 200);
    int byteCount = send(clientsocket, buffer, 200, 0);
    if (byteCount > 0) {
        cout << "Message Sent: " << buffer << endl;
    }
    else {
        cout << "Error sending message" << endl;
        WSACleanup();
    }
    //step 5 accept confirmation close the socket and clean resources
    byteCount = recv(clientsocket, buffer, 200, 0);
    if (byteCount > 0) {
        cout << "Confirmation Message Received: " << buffer << endl;
    }
    else {
        cout << "Error sending message" << endl;
        WSACleanup();
    }
    system("pause");
    WSACleanup();
    cout << "Closed Socket" << endl;
    return 0;
}
