#ifndef MSG_WRITE
#define MSG_WRITE

#pragma once
#include "BasicMsg.h"

class CMsgWrite :
	public CBasicMsg
{
public:
	explicit CMsgWrite();
	virtual ~CMsgWrite();

	virtual void writeString(char * str, int len) = 0;
	virtual void writeInt(int val) = 0;
	virtual void writeShort(short val) = 0;
	virtual void writeBool(bool val) = 0;

	virtual int getDataLen() = 0;
	virtual char * getData() = 0;
	virtual void setData(char * buf, int len) = 0;

protected:
	char * m_buf;
	int m_loc;//当前buf位置
};

/* 执行类 */
class CMsgWriter :
	public CMsgWrite
{
public:
	explicit CMsgWriter();
	virtual ~CMsgWriter();

	CMsgWriter(const CMsgWriter& writer);

	virtual void writeString(char * str, int len);
	virtual void writeInt(int val);
	virtual void writeShort(short val);
	virtual void writeBool(bool val);

	inline virtual int getDataLen() {
		return m_writer->getDataLen();
	}

	inline virtual char * getData() {
		return m_writer->getData();
	}

private:
	virtual void setData(char * buf, int len) {
	}

private:
	CMsgWrite * m_writer;
};

#endif