#include "stdafx.h"
#include "MsgReadLittleEndian.h"


CMsgReadLittleEndian::CMsgReadLittleEndian(char * buf)
{
	m_buf = new char[1024];
	memcpy(m_buf, buf, 1024);
}

CMsgReadLittleEndian::CMsgReadLittleEndian() {
	m_buf = new char[1024];
}

CMsgReadLittleEndian::~CMsgReadLittleEndian()
{
	delete[] m_buf;
}

std::shared_ptr<char> CMsgReadLittleEndian::readString() {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_UTF;
	/* str���� */
	const short len = (m_buf[m_loc ++] << 8)//���ֽ�
	 + m_buf[++ m_loc];//���ֽ�
	/* str���� */
	// TODO: ����᲻��Ҫ��1���ֽ���ʾ'\0'
	char * content = new char[len];
	memcpy(content, m_buf + m_loc, len);
	m_loc += len;
	std::shared_ptr<char> rtn(content);

	return rtn;
}

int CMsgReadLittleEndian::readInt() {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_INT;
	/* ���� */
	char ch1 = m_buf[m_loc ++];
	char ch2 = m_buf[m_loc ++];
	char ch3 = m_buf[m_loc ++];
	char ch4 = m_buf[m_loc ++];

	return (ch1 >> 24) + (ch2 >> 16) + (ch3 >> 8) + ch4;
}

short CMsgReadLittleEndian::readShort() {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_SHORT;
	/* ���� */
	char ch1 = m_buf[m_loc ++];
	char ch2 = m_buf[m_loc ++];

	return (ch1 >> 8) + ch2;
}

bool CMsgReadLittleEndian::readBool() {
	/* �������� */
	m_buf[m_loc ++] = (char)DataType::TYPE_BOOL;
	/* ���� */
	return m_buf[m_loc ++];
}

void CMsgReadLittleEndian::setData(char * buf, int len) {
	memcpy(buf, m_buf, 1024);
	m_loc = 0;
}
