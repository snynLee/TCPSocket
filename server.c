#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define SERVERPORT  9000


int main()
{
    // 변수 선언
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    char sendmsg[] = "Hello Client";    // 클라이언트에 보내줄 메세지
    char recvmsg[1024];

    // 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    // 소켓 생성 ( TCP )
    hServSock = socket(PF_INET, SOCK_STREAM, 0);       

    // 소켓에 넣을 주소 구조체 생성
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(SERVERPORT);

    // 소켓에 주소 할당
    bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

    // 소켓에 들어오는 요청 대기
    listen(hServSock, 10);

    // 클라이언트 주소 구조체 크기변수 정의
    int size_clntAddr = sizeof(clntAddr);

    // 클라이언트 소켓 핸들에 승인된 클라이언트 주소 할당
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &size_clntAddr);

    // 클라이언트에 메시지 전송
    send(hClntSock, sendmsg, sizeof(sendmsg), 0);

    // 클라이언트 메시지 수신
    recv(hClntSock, recvmsg, sizeof(recvmsg) - 1, 0);
    printf("Recevid message: %s\n", recvmsg);

    // 소켓닫기
    closesocket(hClntSock);
    closesocket(hServSock);

    // 라이브러리 반환
    WSACleanup();

    return 0;

}