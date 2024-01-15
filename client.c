#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>


#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000


int main()
{
    // ���� ����
    WSADATA wsaData;
    SOCKET hSock;
    SOCKADDR_IN servAddr;

    char sendmsg[] = "Hello Server";    // ������ ������ �޼���
    char recvmsg[1024];

    // ���̺귯�� �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    // ���� ���� ( TCP )
    hSock = socket(PF_INET, SOCK_STREAM, 0);        

    // ��� ���� ���Ͽ� ���� �ּ� ����ü ����
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(SERVERIP);
    servAddr.sin_port = htons(SERVERPORT);

    // ���� ���Ͽ� �ּ� �Ҵ�
    connect(hSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

    // ������ �޽��� ����
    send(hSock, sendmsg, sizeof(sendmsg), 0);

    // ���� �޽��� ����
    recv(hSock, recvmsg, sizeof(recvmsg) - 1, 0);
    printf("Recevied message: %s\n", recvmsg);

    // ���ϴݱ�
    closesocket(hSock);

    // ���̺귯�� ��ȯ
    WSACleanup();

    return 0;
}