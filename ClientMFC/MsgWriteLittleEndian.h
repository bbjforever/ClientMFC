#ifndef MSG_WRITE_LITTLEENDIAN
#define MSG_WRITE_LITTLEENDIAN

#pragma once
#include "MsgWrite.h"
class CMsgWriteLittleEndian :
	public CMsgWrite
{
public:
	CMsgWriteLittleEndian();
	virtual ~CMsgWriteLittleEndian();

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

