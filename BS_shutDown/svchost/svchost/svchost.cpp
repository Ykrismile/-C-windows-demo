#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
enum { SHUTDOWN = 1, REBOOT };

int main()
{
	//初始化网络
	WSADATA wd;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wd)) {
		printf("初始化网络失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	//请求的套接字版本是否一致
	if (LOBYTE(wd.wVersion) != 2 || HIBYTE(wd.wVersion) != 2) {
		printf("请求套接字版本不一致,错误代号：%d\n", GetLastError());
		return 0;
	}

	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockClient) {
		printf("创建套接字失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	//连接服务器
	SOCKADDR_IN serv_addr;
	serv_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.111");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(10086);

	if (SOCKET_ERROR == connect(sockClient, (sockaddr*)&serv_addr, sizeof(serv_addr))) {
		printf("连接服务器失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	printf("连接服务器成功\n");

	while (1) {
		int cmd = 0;
		recv(sockClient, (char*)&cmd,sizeof(cmd), 0);
		switch (cmd)
		{
		case SHUTDOWN:
			system("shutdown -s -t 0");
		break;
		case REBOOT:
			system("shutdown -r -t 0");
			break;
		default:
			break;
		}
	}

	//关闭套接字

	return 0;
}