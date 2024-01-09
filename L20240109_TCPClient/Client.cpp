#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h> //Sock ����� ���� ģ��.

#pragma comment(lib, "ws2_32")
using namespace std;

//GetLastError -> ���� �ڵ� Ȯ�ο�

int main() // ���⼭����
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result != 0)
	{
		cout << "Winsock dll error : " << GetLastError() << endl;
		exit(-1);
	} // ������� ������ �ڵ�

	struct sockaddr_in ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("192.168.3.243");
	ServerSockAddr.sin_port = htons(40211);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	Result = connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "can't connect. : " << GetLastError() << endl;
		exit(-1);
	}


	char RecvBuffer[1024] = { 0, };
	int RecvByte = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);

	cout << "Server Sent " << RecvBuffer << endl;



	int SentByte = send(ServerSocket, RecvBuffer, (int)strlen(RecvBuffer), 0);

	cout << "Send Data " << endl;




	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}