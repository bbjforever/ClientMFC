#ifndef MSG_READ_LITTLEENDIAN
#define MSG_READ_LITTLEENDIAN

#pragma once
#include "MsgRead.h"
class CMsgReadLittleEndian :
	public CMsgRead
{
public:
	explicit CMsgReadLittleEndian(char * buf);
	explicit CMsgReadLittleEndian();
	virtual ~CMsgReadLittleEndian();

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