#include "stdafx.h"
#include "BasicMsg.h"

CBasicMsg::CBasicMsg()
{
}


CBasicMsg::~CBasicMsg()
{
}


/**
 * 检查Endian模式是否低位在前
 */
bool CBasicMsg::isLittleEndian() {
	int i = 1;
	char * p = (char *)&i;
	if (*p == 1)
		return true;
	
	return false;
}