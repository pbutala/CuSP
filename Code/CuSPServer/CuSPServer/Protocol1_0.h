#pragma once
#include "protocol.h"

class CProtocol1_0 :
	public CProtocol
{
private:
	static const char* strCusp;
	static const char* strSrvr;

public:

	CProtocol1_0(void);
	~CProtocol1_0(void);
	virtual void GetResponse(const char*, int, char*, char*);
};

