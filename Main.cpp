#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include<WinSock2.h>

//이건 외우자
#pragma comment(lib, "ws2_32.lib") //선언을 해야 WinSock2.h 사용가능

using namespace std;

int main()
{
	//이건 외우자
	/*
	
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);



	WSACleanup();
	*/
	//소캣 라이브러리 로딩
	/*
	Server
	1. 소캣만들기
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

	//TCP : UDP - 정보를 요청후 받고 확인한다. 연결하는 작업을 한다. 순서대로 유지된다.: 정보를 일단 받고 보낸다.

	//시작
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl; //에러 확인용
		exit(-1);
	}

	//서버 만들기
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET스타일에 SOCK_STREA의 소캣을 만들어 달라
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "fail create Socket : "<< GetLastError() <<endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockAddr; //ip와 포트를 적는다.
	memset(&ServerSockAddr,0,sizeof(SOCKADDR_IN));//목적지(ServerSockedAdd)에다 원하는 값(0)만큼 원하는 사이즈(SOCKADDR_IN)만큼 채워달라.
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY : 랜카드중 아무거나 하다 쓰자
	ServerSockAddr.sin_port = htons(8000); //이 포트를 쓰겠다.
	int Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));// 가상 소캣과 ip, 포트연결
	if (Result == SOCKET_ERROR)
	{
		cout << "fail bind : " << GetLastError() << endl;
		exit(-1);
	}

	//외부입력을 기다려라
	Result = listen(ServerSocket, 0);
	if (Result == SOCKET_ERROR)
	{
		cout << "fail listen : " << GetLastError() << endl;
		exit(-1);
	}

	//수락 후에 새로운 포트를 연결해서 클라이언트 소캣 반환
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "fail accept : " << GetLastError() << endl;
		exit(-1);
	}

	//주기
	char Buffer[] = "Hello World";
	int SentBytes = send(ClientSocket, Buffer, sizeof(Buffer), 0);
	if (SentBytes <= 0)
	{
		cout<<"fail send : " << GetLastError() << endl;
		exit(-1);
	}

	//받기
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