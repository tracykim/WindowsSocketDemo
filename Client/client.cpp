/**
 * client
 */
#include <iostream>
#include <winsock.h>
#include <thread>
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100

using namespace std;
void initialization();
int main() {
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	//char send_buf[100];
	//string send_buf;
	char send_buf[BUF_SIZE];
	char recv_buf[BUFSIZ];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(9999);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		return -1;
		//WSACleanup();
	}
	else {
		cout << "服务器连接成功！" << endl;
	}

	//发送,接收数据
	while (1) {
		//cin >> send_buf;
		cout << "pleasure input:";
		gets_s(send_buf);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//send_buf = "hi,server!";
		//cout << "strlen(send_buf): " << strlen(send_buf) << endl;
		send_len = send(s_server, send_buf, BUF_SIZE, 0);
		if (send_len < 0) {
			cout << "发送失败！" << endl;
			break;
		}
		recv_len = recv(s_server, recv_buf, BUF_SIZE, 0);
		if (recv_len < 0) {
			cout << "接受失败！" << endl;
			break;
		}
		else {
			cout << "服务端信息:" << recv_buf << endl;
		}
	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
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