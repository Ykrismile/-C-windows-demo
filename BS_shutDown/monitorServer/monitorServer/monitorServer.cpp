#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

enum{SHUTDOWN=1,REBOOT};

int main()
{
	//初始化网络
	WSADATA wd;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wd)) {
		printf("初始化网络失败,错误代号：%d\n",GetLastError());
		return 0;
	}
	
	//请求的套接字版本是否一致
	if (LOBYTE(wd.wVersion) != 2 || HIBYTE(wd.wVersion) != 2) {
		printf("请求套接字版本不一致,错误代号：%d\n", GetLastError());
		return 0;
	}

	//创建套接字
	SOCKET sockServ = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockServ) {
		printf("创建套接字失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	//绑定套接字
	SOCKADDR_IN serv_addr;
	serv_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(10086);
	
	if (SOCKET_ERROR == bind(sockServ, (sockaddr*)&serv_addr, sizeof(serv_addr))) {
		printf("绑定套接字失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	//监听套接字
	if (SOCKET_ERROR == listen(sockServ, 5)) {
		printf("监听失败,错误代号：%d\n", GetLastError());
		return 0;
	}

	//接受连接请求
	while (1) {
		SOCKADDR_IN client_addr;
		int length = sizeof(client_addr);
		SOCKET connSocket = accept(sockServ, (sockaddr*)&client_addr, &length);

		printf("客户端 %s : %d 已上线\n",inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

		printf("请输入对应的命令值，关机：1，重启：2\n");
		int cmd;
		scanf("%d", &cmd);

		switch (cmd)
		{
		case SHUTDOWN:
		case REBOOT:
			send(connSocket,(const char*)&cmd,sizeof(cmd),0);
			break;
		default:
			printf("您的输入有误\n");
			break;
		}


		//关闭套接字
		closesocket(connSocket);
	}

	
	


	return 0;
}