// client.cpp  

#include <iostream>  
#include <stdio.h>
#include <Winsock2.h>  
#pragma comment(lib,"ws2_32.lib")

using namespace std;

struct UsrData{
	int aa;
	char usr_id[16];
	char usr_pwd[16];
	char usr_nickname[16];
};

int main()
{
	// ����socket��̬���ӿ�(dll)  
	WORD wVersionRequested;
	WSADATA wsaData;    // ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��  
	int err;

	wVersionRequested = MAKEWORD(1, 1);   // ����1.1�汾��WinSock��  

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;          // ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup  
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾  
		// ����Ļ�������WSACleanup()�����Ϣ����������  
		WSACleanup();
		return -1;
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient  
	// SOCKET socket(int af, int type, int protocol);  
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)  
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// ���׽���sockClient��Զ����������  
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);  
	// ��һ����������Ҫ�������Ӳ������׽���  
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ  
	// ��������������ַ�ĳ���  
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");      // ���ػ�·��ַ��127.0.0.1;   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

//	send(sockClient, "Attention: A Client has enter...\n", strlen("Attention: A Client has enter...\n") + 1, 0);

	UsrData sendUser;
	sendUser.aa = 101;
	memcpy(sendUser.usr_id, "100001", sizeof("100001"));
	memcpy(sendUser.usr_pwd, "123456", sizeof("123456"));
	memcpy(sendUser.usr_nickname, "Rock", sizeof("Rock"));
	send(sockClient, (char *)&sendUser, sizeof(UsrData), 0);

	printf("���ǿ�������仰");
	int n = 5;
	do{
		printf("\n��ʣ%d�Σ�", n);
		char talk[100];
		printf("\nPlease enter what you want to say next(\"quit\"to exit):");
		gets(talk);
		send(sockClient, talk, strlen(talk) + 1, 0);          // ������Ϣ  





		char recvBuf[100];
		recv(sockClient, recvBuf, 100, 0);
		printf("%s Says: %s\n", "Server", recvBuf);     // ������Ϣ  
	} while (--n);

	printf("End linking...\n");
	closesocket(sockClient);
	WSACleanup();   // ��ֹ���׽��ֿ��ʹ��  

	printf("\n");
	system("pause");
	return 0;
}