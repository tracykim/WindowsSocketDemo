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
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	//char send_buf[100];
	//string send_buf;
	char send_buf[BUF_SIZE];
	char recv_buf[BUFSIZ];
	//���������׽��֣����������׽���
	SOCKET s_server;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(9999);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "����������ʧ�ܣ�" << endl;
		return -1;
		//WSACleanup();
	}
	else {
		cout << "���������ӳɹ���" << endl;
	}

	//����,��������
	while (1) {
		//cin >> send_buf;
		cout << "pleasure input:";
		gets_s(send_buf);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//send_buf = "hi,server!";
		//cout << "strlen(send_buf): " << strlen(send_buf) << endl;
		send_len = send(s_server, send_buf, BUF_SIZE, 0);
		if (send_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		recv_len = recv(s_server, recv_buf, BUF_SIZE, 0);
		if (recv_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else {
			cout << "�������Ϣ:" << recv_buf << endl;
		}
	}
	//�ر��׽���
	closesocket(s_server);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
void initialization() {
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ

}