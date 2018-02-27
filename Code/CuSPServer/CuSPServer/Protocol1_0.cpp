#include "StdAfx.h"
#include "Protocol1_0.h"
#include <string.h>

const char* CProtocol1_0::strCusp = "cusp";
const char* CProtocol1_0::strSrvr = "srvr";

CProtocol1_0::CProtocol1_0(void)
{

}

CProtocol1_0::~CProtocol1_0(void)
{

}

void CProtocol1_0::GetResponse(const char *strIn, int strInLen, char* bufOut, char* bufIf)
{
	bufOut[0] = '\0';
	bufIf[0] = '\0';
	char target[5];
	int i=0,j=0;
	target[0] = strIn[i++];
	target[1] = strIn[i++];
	target[2] = strIn[i++];
	target[3] = strIn[i++];
	target[4] = '\0';
	i++;
	if(strcmpi(target, CProtocol1_0::strCusp) == 0)
	{
		//while(strIn[i] != '\0')
		while(i < strInLen)
		{
			bufIf[j++] = strIn[i++];
		}
		strcpy(bufOut, "ok");
		bufIf[j++] = '\0';
	}
	else if(strcmpi(target, CProtocol1_0::strSrvr) == 0)
	{
		strcpy(bufOut, "ok");
	}
	else
	{
		strcpy(bufOut, "error");
	}
	//strcat(bufOut, "\r\n");
}

