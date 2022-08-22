#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include<WinSock2.h>

//�̰� �ܿ���
#pragma comment(lib, "ws2_32.lib") //������ �ؾ� WinSock2.h ��밡��

using namespace std;

int main()
{
	//�̰� �ܿ���
	/*
	
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);



	WSACleanup();
	*/
	//��Ĺ ���̺귯�� �ε�
	/*
	Server
	1. ��Ĺ�����
	2.bind
	3.listen
	4.accept

	5.send
	6.recv
	*/

	/*
	Client
	1. socket
	2.commect
	3.recv
	4.send
	*/

	//TCP : UDP - ������ ��û�� �ް� Ȯ���Ѵ�. �����ϴ� �۾��� �Ѵ�. ������� �����ȴ�.: ������ �ϴ� �ް� ������.

	//����
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl; //���� Ȯ�ο�
		exit(-1);
	}

	//���� �����
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET��Ÿ�Ͽ� SOCK_STREA�� ��Ĺ�� ����� �޶�
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "fail create Socket : "<< GetLastError() <<endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockAddr; //ip�� ��Ʈ�� ���´�.
	memset(&ServerSockAddr,0,sizeof(SOCKADDR_IN));//������(ServerSockedAdd)���� ���ϴ� ��(0)��ŭ ���ϴ� ������(SOCKADDR_IN)��ŭ ä���޶�.
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY : ��ī���� �ƹ��ų� �ϴ� ����
	ServerSockAddr.sin_port = htons(8000); //�� ��Ʈ�� ���ڴ�.
	int Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));// ���� ��Ĺ�� ip, ��Ʈ����
	if (Result == SOCKET_ERROR)
	{
		cout << "fail bind : " << GetLastError() << endl;
		exit(-1);
	}

	//�ܺ��Է��� ��ٷ���
	Result = listen(ServerSocket, 0);
	if (Result == SOCKET_ERROR)
	{
		cout << "fail listen : " << GetLastError() << endl;
		exit(-1);
	}

	//���� �Ŀ� ���ο� ��Ʈ�� �����ؼ� Ŭ���̾�Ʈ ��Ĺ ��ȯ
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "fail accept : " << GetLastError() << endl;
		exit(-1);
	}

	//�ֱ�
	char Buffer[] = "Hello World";
	int SentBytes = send(ClientSocket, Buffer, sizeof(Buffer), 0);
	if (SentBytes <= 0)
	{
		cout<<"fail send : " << GetLastError() << endl;
		exit(-1);
	}

	//�ޱ�
	char Buffer2[1024] = { 0, };
	int RecvBytes = recv(ClientSocket, Buffer2, 1024, 0);
	if (RecvBytes <= 0)
	{
		cout << "fail recv : " << GetLastError() << endl;
		exit(-1);
	}

	cout << Buffer2 << endl;




	closesocket(ServerSocket);
	closesocket(ClientSocket);

	WSACleanup();

	return 0;
}