#include "stdafx.h"
#include "MsgWriteLittleEndian.h"


CMsgWriteLittleEndian::CMsgWriteLittleEndian()
{
	m_buf = new char[1024];
}


CMsgWriteLittleEndian::~CMsgWriteLittleEndian()
{
	delete[] m_buf;
}

void CMsgWriteLittleEndian::writeString(char * str, int len) {
	/* �������� */
	m_buf[m_loc++] = (char)DataType::TYPE_UTF;
	/* str���� */
	m_buf[m_loc++] = len >> 8;//���ֽ�
	m_buf[m_loc++] = len;//���ֽ�
	/* str���� */
	char * content = m_buf + m_loc;
	memcpy(content, str, len);
	m_loc += len;
}

void CMsgWriteLittleEndian::writeInt(int val) {
	/* �������� */
	m_buf[m_loc++] = (char)DataType::TYPE_INT;
	/* ���� */
	m_buf[m_loc++] = val >> 24;
	m_buf[m_loc++] = val >> 16;
	m_buf[m_loc++] = val >> 8;
	m_buf[m_loc++] = val;
}

void CMsgWriteLittleEndian::writeShort(short val) {
	/* �������� */
	m_buf[m_loc++] = (char)DataType::TYPE_SHORT;
	/* ���� */
	m_buf[m_loc++] = val >> 8;
	m_buf[m_loc++] = val;
}

void CMsgWriteLittleEndian::writeBool(bool val) {
	/* �������� */
	m_buf[m_loc++] = (char)DataType::TYPE_BOOL;
	/* ���� */
	m_buf[m_loc++] = val;
}

void CMsgWriteLittleEndian::setData(char * buf, int len) {
	memcpy(m_buf, buf, len);
	m_loc = len;
}