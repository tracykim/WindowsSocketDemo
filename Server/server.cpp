#include <iostream>
#include <string>
#include <winsock.h>
#include <thread> //std::this_thread
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100

using namespace std;

void initialization(); // 初始化套接字
void collect_pointcloud(); // 采集数据
void stopDevice(); //停止采集

int main(int argc, char* argv[]) {
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[BUF_SIZE];
	//string send_buf;
	char recv_buf[BUF_SIZE];
	//定义命令
	char COLLECT[] = "collect";
	char STOP[] = "stop";
	char QUIT[] = "q";
	char FAILURE[] = "collect failure!";
	char COMMAND[] = "pleasure input collect or q!";
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9999);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	// 在bind前添加::
	if (::bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字绑定成功！" << endl;
	}
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "设置监听状态成功！" << endl;
	}
	cout << "服务端正在监听连接，请稍候...." << endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "连接失败！" << endl;
		WSACleanup();
		system("pause");
		return 0;
	}
	cout << "连接建立，准备接受数据" << endl;

	//接收数据
	while (1) {
		recv_len = recv(s_accept, recv_buf, BUF_SIZE, 0);
		if (recv_len < 0) {
			cout << "接受失败！" << endl;
			break;
		}
		else {
			cout << "客户端信息:" << recv_buf << endl;
		}

		if (!strcmp(COLLECT, recv_buf))
		{
			//采集数据
			printf("-------开始采集数据-------\n");
			/// jinye 不连接扫描仪版本
			collect_pointcloud();
			char str[] = "服务端采集数据完毕！";
			send(s_accept, str, BUF_SIZE, 0);

			printf("-------结束采集数据-------\n");
		}
		// 暂停采集
		else if (!strcmp(STOP, recv_buf))
		{
			stopDevice();
		}
		//程序退出		
		else if (!strcmp(QUIT, recv_buf))
		{
			char q[] = "服务端退出";
			send(s_accept, q, BUF_SIZE, 0);
			break;
		}

		else //if (strcmp(COLLECT, recv_buf) && strcmp(QUIT, recv_buf))
		{
			send(s_accept, COMMAND, BUF_SIZE, 0);
		}
		//cout << "请输入回复信息:";
		//gets_s(send_buf);

		////send_buf = "ok";
		//send_len = send(s_accept, send_buf, 100, 0);
		//if (send_len < 0) {
		//	cout << "发送失败！" << endl;
		//	break;
		//}
	}
	
	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
	//释放DLL资源
	WSACleanup();
	system("pause");
	return 0;
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

void collect_pointcloud()
{
	cout << "扫描仪开始采集数据！" << endl;
}

void stopDevice()
{
	cout << "扫描仪停止采集数据！" << endl;
}