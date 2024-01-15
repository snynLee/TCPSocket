#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define SERVERPORT  9000


int main()
{
    // ���� ����
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    char sendmsg[] = "Hello Client";    // Ŭ���̾�Ʈ�� ������ �޼���
    char recvmsg[1024];

    // ���̺귯�� �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    // ���� ���� ( TCP )
    hServSock = socket(PF_INET, SOCK_STREAM, 0);       

    // ���Ͽ� ���� �ּ� ����ü ����
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(SERVERPORT);

    // ���Ͽ� �ּ� �Ҵ�
    bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

    // ���Ͽ� ������ ��û ���
    listen(hServSock, 10);

    // Ŭ���̾�Ʈ �ּ� ����ü ũ�⺯�� ����
    int size_clntAddr = sizeof(clntAddr);

    // Ŭ���̾�Ʈ ���� �ڵ鿡 ���ε� Ŭ���̾�Ʈ �ּ� �Ҵ�
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &size_clntAddr);

    // Ŭ���̾�Ʈ�� �޽��� ����
    send(hClntSock, sendmsg, sizeof(sendmsg), 0);

    // Ŭ���̾�Ʈ �޽��� ����
    recv(hClntSock, recvmsg, sizeof(recvmsg) - 1, 0);
    printf("Recevid message: %s\n", recvmsg);

    // ���ϴݱ�
    closesocket(hClntSock);
    closesocket(hServSock);

    // ���̺귯�� ��ȯ
    WSACleanup();

    return 0;

}