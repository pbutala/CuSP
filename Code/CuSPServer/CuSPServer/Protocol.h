#pragma once

public class CProtocol
{
private:
	
protected:

public:
	CProtocol(void);
	~CProtocol(void);
	virtual void GetResponse(const char*, int, char*, char*) = 0;
};

