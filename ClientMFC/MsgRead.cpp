#include "stdafx.h"
#include "MsgRead.h"
#include "MsgReadLittleEndian.h"
#include "MsgReadBigEndian.h"


CMsgRead::CMsgRead(char * buf)
{

}


CMsgRead::~CMsgRead()
{

}

/* ****************************** writer ********************************** */
CMsgReader::CMsgReader(char * buf) : m_reader(nullptr)
{
	bool b = isLittleEndian();
	if (b) {
		m_reader = new CMsgReadLittleEndian();
	}
	else {
		m_reader = new CMsgReadBigEndian();
	}
}

CMsgReader::~CMsgReader() {
	delete m_reader;
}

CMsgReader::CMsgReader(const CMsgReader& reader) {
	bool b = isLittleEndian();
	if (b) {
		m_reader = new CMsgReadLittleEndian();
	}
	else {
		m_reader = new CMsgReadBigEndian();
	}

	m_reader->setData(reader.m_reader->getData(), reader.m_reader->getDataLen());
}

std::shared_ptr<char> CMsgReader::readString() {
	return m_reader->readString();
}

int CMsgReader::readInt() {
	return m_reader->readInt();
}

short CMsgReader::readShort() {
	return m_reader->readShort();
}

bool CMsgReader::readBool() {
	return m_reader->readBool();
}