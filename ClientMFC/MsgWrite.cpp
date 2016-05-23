#include "stdafx.h"
#include "MsgWrite.h"

#include "MsgWriteBigEndian.h"
#include "MsgWriteLittleEndian.h"


CMsgWrite::CMsgWrite()
{
	
}


CMsgWrite::~CMsgWrite()
{

}


/* ****************************** writer ********************************** */
CMsgWriter::CMsgWriter() : m_writer(nullptr)
{
	bool b = isLittleEndian();
	if (b) {
		m_writer = new CMsgWriteLittleEndian();
	}
	else {
		m_writer = new CMsgWriteBigEndian();
	}
}

CMsgWriter::~CMsgWriter() {
	delete m_writer;
}

CMsgWriter::CMsgWriter(const CMsgWriter& writer) {
	bool b = isLittleEndian();
	if (b) {
		m_writer = new CMsgWriteLittleEndian();
	}
	else {
		m_writer = new CMsgWriteBigEndian();
	}

	m_writer->setData(writer.m_writer->getData(), writer.m_writer->getDataLen());
}

void CMsgWriter::writeString(char * str, int len) {
	m_writer->writeString(str, len);
}

void CMsgWriter::writeInt(int val) {
	m_writer->writeInt(val);
}

void CMsgWriter::writeShort(short val) {
	m_writer->writeShort(val);
}

void CMsgWriter::writeBool(bool val) {
	m_writer->writeBool(val);
}