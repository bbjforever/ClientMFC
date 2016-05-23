#ifndef MSG_READ
#define MSG_READ

#pragma once
#include "BasicMsg.h"
#include <memory>

class CMsgRead :
	public CBasicMsg
{
public:
	explicit CMsgRead(char * buf);
	virtual ~CMsgRead();

	virtual std::shared_ptr<char> readString() = 0;
	virtual int readInt() = 0;
	virtual short readShort() = 0;
	virtual bool readBool() = 0;

	virtual void setData(char * buf, int len) = 0;

	inline virtual int getDataLen() = 0;
	inline virtual char * getData() = 0;

protected:
	explicit CMsgRead() {};

	char * m_buf;
	int m_loc;//当前buf位置
};

/* 执行类 */
class CMsgReader :
	public CMsgRead
{
public:
	explicit CMsgReader(char * buf);
	virtual ~CMsgReader();

	CMsgReader(const CMsgReader& reader);

	virtual std::shared_ptr<char> readString();
	virtual int readInt();
	virtual short readShort();
	virtual bool readBool();

	inline virtual int getDataLen() {
		return m_reader->getDataLen();
	}

	inline virtual char * getData() {
		return m_reader->getData();
	}

private:
	virtual void setData(char * buf, int len) {
	}

private:
	CMsgRead * m_reader;
};

#endif
