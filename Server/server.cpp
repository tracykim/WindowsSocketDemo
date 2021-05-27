#include <iostream>
#include <string>
#include <winsock.h>
#include <thread> //std::this_thread
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100

using namespace std;

void initialization(); // ��ʼ���׽���
void collect_pointcloud(); // �ɼ�����
void stopDevice(); //ֹͣ�ɼ�

int main(int argc, char* argv[]) {
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[BUF_SIZE];
	//string send_buf;
	char recv_buf[BUF_SIZE];
	//��������
	char COLLECT[] = "collect";
	char STOP[] = "stop";
	char QUIT[] = "q";
	char FAILURE[] = "collect failure!";
	char COMMAND[] = "pleasure input collect or q!";
	//���������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9999);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	// ��bindǰ���::
	if (::bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "�׽��ְ󶨳ɹ���" << endl;
	}
	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "���ü���״̬ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "���ü���״̬�ɹ���" << endl;
	}
	cout << "��������ڼ������ӣ����Ժ�...." << endl;
	//������������
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "����ʧ�ܣ�" << endl;
		WSACleanup();
		system("pause");
		return 0;
	}
	cout << "���ӽ�����׼����������" << endl;

	//��������
	while (1) {
		recv_len = recv(s_accept, recv_buf, BUF_SIZE, 0);
		if (recv_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else {
			cout << "�ͻ�����Ϣ:" << recv_buf << endl;
		}

		if (!strcmp(COLLECT, recv_buf))
		{
			//�ɼ�����
			printf("-------��ʼ�ɼ�����-------\n");
			/// jinye ������ɨ���ǰ汾
			collect_pointcloud();
			char str[] = "����˲ɼ�������ϣ�";
			send(s_accept, str, BUF_SIZE, 0);

			printf("-------�����ɼ�����-------\n");
		}
		// ��ͣ�ɼ�
		else if (!strcmp(STOP, recv_buf))
		{
			stopDevice();
		}
		//�����˳�		
		else if (!strcmp(QUIT, recv_buf))
		{
			char q[] = "������˳�";
			send(s_accept, q, BUF_SIZE, 0);
			break;
		}

		else //if (strcmp(COLLECT, recv_buf) && strcmp(QUIT, recv_buf))
		{
			send(s_accept, COMMAND, BUF_SIZE, 0);
		}
		//cout << "������ظ���Ϣ:";
		//gets_s(send_buf);

		////send_buf = "ok";
		//send_len = send(s_accept, send_buf, 100, 0);
		//if (send_len < 0) {
		//	cout << "����ʧ�ܣ�" << endl;
		//	break;
		//}
	}
	
	//�ر��׽���
	closesocket(s_server);
	closesocket(s_accept);
	//�ͷ�DLL��Դ
	WSACleanup();
	system("pause");
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

void collect_pointcloud()
{
	cout << "ɨ���ǿ�ʼ�ɼ����ݣ�" << endl;
}

void stopDevice()
{
	cout << "ɨ����ֹͣ�ɼ����ݣ�" << endl;
}