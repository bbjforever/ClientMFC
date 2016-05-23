#include "stdafx.h"
#include "MsgReadBigEndian.h"


CMsgReadBigEndian::CMsgReadBigEndian(char * buf)
{
	m_buf = new char[1024];
	memcpy(m_buf, buf, 1024);
}

CMsgReadBigEndian::CMsgReadBigEndian() {
	m_buf = new char[1024];
}

CMsgReadBigEndian::~CMsgReadBigEndian()
{
	delete[] m_buf;
}

std::shared_ptr<char> CMsgReadBigEndian::readString() {
	/* 数据类型 */
	m_buf[m_loc++] = (char)DataType::TYPE_UTF;
	/* str长度 */
	const short len = (m_buf[m_loc++] << 8)//高字节
		+ m_buf[++m_loc];//低字节
	/* str内容 */
	// TODO: 这里会不会要加1个字节显示'\0'
	char * content = new char[len];
	memcpy(content, m_buf + m_loc, len);
	m_loc += len;
	std::shared_ptr<char> rtn(content);

	return rtn;
}

int CMsgReadBigEndian::readInt() {
	/* 数据类型 */
	m_buf[m_loc++] = (char)DataType::TYPE_INT;
	/* 数据 */
	char ch1 = m_buf[m_loc++];
	char ch2 = m_buf[m_loc++];
	char ch3 = m_buf[m_loc++];
	char ch4 = m_buf[m_loc++];

	return (ch1 >> 24) + (ch2 >> 16) + (ch3 >> 8) + ch4;
}

short CMsgReadBigEndian::readShort() {
	/* 数据类型 */
	m_buf[m_loc++] = (char)DataType::TYPE_SHORT;
	/* 数据 */
	char ch1 = m_buf[m_loc++];
	char ch2 = m_buf[m_loc++];

	return (ch1 >> 8) + ch2;
}

bool CMsgReadBigEndian::readBool() {
	/* 数据类型 */
	m_buf[m_loc++] = (char)DataType::TYPE_BOOL;
	/* 数据 */
	return m_buf[m_loc++];
}

void CMsgReadBigEndian::setData(char * buf, int len) {
	memcpy(buf, m_buf, 1024);
	m_loc = 0;
}