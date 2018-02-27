#include "StdAfx.h"
#include <conio.h>
#include "Server.h"
#include "Protocol.h"
#include "Protocol1_0.h"

#pragma comment(lib,"ws2_32.lib")

CServer::CServer(void)
{
	pBuffer = new CTranslate();
	pNwIf = new CNwIfANT(pBuffer);
}

CServer::~CServer(void)
{
	delete pNwIf;
	delete pBuffer;
}

void CServer::StartServer(void)
{
	WSADATA WsaDat;
	SOCKET Socket;
	int nResult = WSAStartup(MAKEWORD(2,2),&WsaDat);
	if(nResult!=0)
	{
		std::cout<<"WSA Initialization failed: "<<nResult<<"\r\n";
		WSACleanup();
		return;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=htonl(INADDR_ANY);
	serverInf.sin_port=htons(PORT);


	Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		int nError=WSAGetLastError();
		std::cout<<"Socket creation failed: "<<nError<<"\r\n";
		WSACleanup();
		return;
	}

	if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"Unable to bind socket: "<<nError<<"\r\n";
		WSACleanup();
		return;
	}

	std::cout<<"CuSP Server is Online.\r\n";
	std::cout<<"Initializing Network Interface...\r\n";

	while(!CNwIfANT::detectInterface())
	{
		std::cout<<"Cannot Locate Network Interface.\r\n";
		std::cout<<"PlugIn USB and click any key.\r\n";
		fflush(stdin);
		_getch();

	}
	std::cout<<"Network Interface Initialized.\r\n";
	fflush(stdout);

	std::cout<<"Connecting to CuSP...\r\n";
	if(pNwIf->openControlChannel())
	//if(pNwIf->connectSensor())
	{
		std::cout<<"Connected to CuSP !\r\n";
	}
	else
	{
		std::cout<<"Connection Failed\r\n";
	}

	while(true)
	{
		mut->WaitOne();
		bool ok = (connCnt < MAX_CONN);
		mut->ReleaseMutex();

		if(ok)
		{
			if(listen(Socket,0)==SOCKET_ERROR)
			{
				int nError=WSAGetLastError();
				//std::cout<<"Unable to listen: "<<nError<<"\r\n";
				WSACleanup();
				return;
			}

			SOCKET clientSocket=SOCKET_ERROR;
			while(clientSocket == SOCKET_ERROR)
			{
				//std::cout<<"Waiting for incoming connections...\r\n";
				clientSocket=accept(Socket,NULL,NULL);
			}
			//Socket=clientSocket;

			mut->WaitOne();
			std::cout<<"Client connected!\r\n";

			ParameterizedThreadStart^ threadDelegate = gcnew ParameterizedThreadStart(this, &CServer::ServiceClientSocket);
			Thread^ newThread = gcnew Thread(threadDelegate);
			newThread->Start(clientSocket);

			connCnt++;
			mut->ReleaseMutex();
		}
	}

	// Shutdown our socket
	if(shutdown(Socket,SD_SEND)==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"Unable to shutdown socket: "<<nError<<"\r\n";
		closesocket(Socket);
		WSACleanup();
		return;
	}

	// Close our socket entirely
	closesocket(Socket);

	// Cleanup Winsock
	WSACleanup();

	return;
}

void CServer::ServiceClientSocket(Object^ Socket)
{
	const int MAXBUF = 1024;
	SOCKET cSocket = (SOCKET)Socket;
	CProtocol *pProtocol = new CProtocol1_0();

	char *szMessage="Welcome to CuSP Network!\r\n";
	send(cSocket,szMessage,strlen(szMessage),0);

	// If iMode!=0, non-blocking mode is enabled.
	u_long iMode=1;
	ioctlsocket(cSocket,FIONBIO,&iMode);

	char bufIn[MAXBUF];
	char bufOut[MAXBUF];
	char bufIf[MAXBUF];
	char bufTmp[MAXBUF];
	int inRxLen = 0;
	int outTxLen = 0;
	memset(bufIn,0,MAXBUF);
	memset(bufOut,0,MAXBUF);

	int nError=WSAGetLastError();
	while((nError==WSAEWOULDBLOCK) || (nError==0))
	{
		inRxLen = recv(cSocket,bufIn,MAXBUF,0);
		bufIn[inRxLen] = '\0';
		if(inRxLen > 0)
		{
			mut->WaitOne();
			std::cout<<bufIn;
			mut->ReleaseMutex();
			pProtocol->GetResponse(bufIn,inRxLen,bufOut,bufIf);
			strcat(bufOut, "\r\n");
			send(cSocket,bufOut,strlen(bufOut),0);
			if(strlen(bufIf) > 0)
			{
				pNwIf->pC2NBuffer->translateClientMessage(bufIf, bufTmp);
				//pNwIf->pC2NBuffer->setBufferData(bufTmp, strlen(bufTmp) + 1);
				pNwIf->pC2NBuffer->setBufferData(bufTmp, 7);//6 params + \0. may need to change.
			}
			// Get Response must also return bufANT to transfer relevant messages to ANT
			// this gets stored in buffer in pBuffer
		}
		outTxLen = pNwIf->pN2CBuffer->getBufferData(bufOut, MAXBUF);
		if(outTxLen > 0)
		{
			strcat(bufOut, "\r\n");
			send(cSocket,bufOut,strlen(bufOut),0);
		}
		/*else
		{
			strcpy(bufOut, "\r\n");
			send(cSocket,bufOut,strlen(bufOut),0);
			System::Threading::Thread::Sleep(100);
		}*/
		nError=WSAGetLastError();
	}

	mut->WaitOne();
	std::cout<<"Connection Closed: "<<nError<<"\r\n";
	mut->ReleaseMutex();

	// Shutdown our socket
	if(shutdown(cSocket,SD_SEND)==SOCKET_ERROR)
	{
		nError=WSAGetLastError();
		//std::cout<<"Unable to shutdown socket: "<<nError<<"\r\n";
	}

	// Close our socket entirely
	closesocket(cSocket);

	mut->WaitOne();
	connCnt--;
	mut->ReleaseMutex();
	delete pProtocol;
}