#ifndef MSG_WRITE_BIGENDIAN
#define MSG_WRITE_BIGENDIAN

#pragma once
#include "MsgWrite.h"
class CMsgWriteBigEndian :
	public CMsgWrite
{
public:
	CMsgWriteBigEndian();
	virtual ~CMsgWriteBigEndian();

	virtual void writeString(char * str, int len);
	virtual void writeInt(int val);
	virtual void writeShort(short val);
	virtual void writeBool(bool val);

	inline virtual int getDataLen() {
		return m_loc;
	}

	inline virtual char * getData() {
		return m_buf;
	}

	virtual void setData(char * buf, int len);
};

#endif