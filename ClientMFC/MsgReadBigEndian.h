#ifndef MSG_READ_BIGENDIAN
#define MSG_READ_BIGENDIAN

#pragma once
#include "MsgRead.h"
class CMsgReadBigEndian :
	public CMsgRead
{
public:
	explicit CMsgReadBigEndian(char * buf);
	explicit CMsgReadBigEndian();
	virtual ~CMsgReadBigEndian();

	virtual std::shared_ptr<char> readString();
	virtual int readInt();
	virtual short readShort();
	virtual bool readBool();

	virtual void setData(char * buf, int len);

	inline virtual int getDataLen() {
		return m_loc;
	}

	inline virtual char * getData() {
		return m_buf;
	}
};

#endif