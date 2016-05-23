#ifndef BASIC_MSG
#define BASIC_MSG

#pragma once

typedef struct Msg
{
	char * data;
	short len;

	Msg(char * data_, short len_) {
		data = data_;
		len = len_;
	}

	~Msg() {
		delete[] data;
	}
} Msg;

/* 数据格式类型 */
enum class DataType : char
{
	TYPE_UTF = 1,
	TYPE_INT,
	TYPE_BOOL,
	TYPE_SHORT
};

class CBasicMsg
{
public:
	CBasicMsg();
	virtual ~CBasicMsg();

protected:
	bool isLittleEndian();
};

#endif
