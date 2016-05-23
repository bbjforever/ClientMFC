#include "stdafx.h"
#include "MsgWriteBigEndian.h"


CMsgWriteBigEndian::CMsgWriteBigEndian()
{
	m_buf = new char[1024];
}


CMsgWriteBigEndian::~CMsgWriteBigEndian()
{
	delete[] m_buf;
}

void CMsgWriteBigEndian::writeString(char * str, int len) {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_UTF;
	/* str���� */
	m_buf[m_loc ++] = len >> 8;//���ֽ�
	m_buf[m_loc ++] = len;//���ֽ�
	/* str���� */
	char * content = m_buf + m_loc;
	memcpy(content, str, len);
	m_loc += len;
}

void CMsgWriteBigEndian::writeInt(int val) {
	/* �������� */
	m_buf[m_loc++] = (char)DataType::TYPE_INT;
	/* ���� */
	m_buf[m_loc ++] = val >> 24;
	m_buf[m_loc ++] = val >> 16;
	m_buf[m_loc ++] = val >> 8;
	m_buf[m_loc ++] = val;
}

void CMsgWriteBigEndian::writeShort(short val) {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_SHORT;
	/* ���� */
	m_buf[m_loc ++] = val >> 8;
	m_buf[m_loc ++] = val;
}

void CMsgWriteBigEndian::writeBool(bool val) {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_BOOL;
	/* ���� */
	m_buf[m_loc ++] = val;
}

void CMsgWriteBigEndian::setData(char * buf, int len) {
	memcpy(buf, m_buf, len);
	m_loc = len;
}
