#ifndef MY_CLIENT
#define MY_CLIENT

#pragma once

#include <list>

#include "BasicMsg.h"
#include "MsgWrite.h"

class CMyClient
{
	friend void onRun(CMyClient* cc);

public:
	CMyClient();
	~CMyClient();

	bool createClient();
	void addMessage(char * data, int msgLen);
	void addMessage(CMsgWriter& msg);
	void close();
	void start();

private:
	void addMessage(char * msg);
	void addMessage(Msg * msg);
	bool sendMessage(Msg * msg);
	void waitStopThread();

private:
	std::list <Msg *> m_sendList;
	SOCKET m_socket;//·þÎñÆ÷Ì×½Ó×Ö

	bool m_toStop;
	bool m_isStop;
	bool m_isThreadRun;

	static const int BUF_SIZE = 128;
};

#endif