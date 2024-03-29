/*
 @Date    : 2018-04-20 10:30:37
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
21.基于UDP的服务器端和客户端
 */

#include <stdio.h>
#include <winsock2.h>
#include <cstring>

// #pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 100

int main()
{
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);
    //服务器地址信息
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(1234);
    //不断获取用户输入并发送给服务器，然后接受服务器数据
    sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
    while (1)
    {
        char buffer[BUF_SIZE] = {0};
        printf("Input a string(\"end\" for end): ");
        gets(buffer);
        sendto(sock, buffer, strlen(buffer)+1, 0, reinterpret_cast<sockaddr*>(&servAddr),
            sizeof(servAddr));
        if (strcmp(buffer, "end") == 0)
        {
            puts("program ended!");
            break;
        }
        int strLen = recvfrom(sock, buffer, BUF_SIZE+100, 0, &fromAddr, &addrLen);
        buffer[strLen] = '\0';
        printf("Message form server: %s\n", buffer);
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}
