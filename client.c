#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>


#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000


int main()
{
    // 변수 선언
    WSADATA wsaData;
    SOCKET hSock;
    SOCKADDR_IN servAddr;

    char sendmsg[] = "Hello Server";    // 서버에 보내줄 메세지
    char recvmsg[1024];

    // 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    // 소켓 생성 ( TCP )
    hSock = socket(PF_INET, SOCK_STREAM, 0);        

    // 대상 서버 소켓에 넣을 주소 구조체 정의
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(SERVERIP);
    servAddr.sin_port = htons(SERVERPORT);

    // 서버 소켓에 주소 할당
    connect(hSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

    // 서버에 메시지 전송
    send(hSock, sendmsg, sizeof(sendmsg), 0);

    // 서버 메시지 수신
    recv(hSock, recvmsg, sizeof(recvmsg) - 1, 0);
    printf("Recevied message: %s\n", recvmsg);

    // 소켓닫기
    closesocket(hSock);

    // 라이브러리 반환
    WSACleanup();

    return 0;
}