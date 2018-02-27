#pragma once
#include <iostream>
#include <WinSock2.h>
#include "NwIfANT.h"

#pragma comment(lib,"ws2_32.lib")

#define MAX_CONN		2
#define PORT		 8888

using namespace System;
using namespace System::Threading;

ref class CServer
{
private:
	static int connCnt = 0;
	static Mutex^ mut = gcnew Mutex;
	CNwIfANT *pNwIf;
	void ServiceClientSocket(Object^ cSock);

protected:

public:
	CTranslate* pBuffer;
	CServer(void);
	~CServer(void);
	void StartServer(void);
};

