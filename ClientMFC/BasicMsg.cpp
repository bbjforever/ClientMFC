#include "stdafx.h"
#include "BasicMsg.h"

CBasicMsg::CBasicMsg()
{
}


CBasicMsg::~CBasicMsg()
{
}


/**
 * ���Endianģʽ�Ƿ��λ��ǰ
 */
bool CBasicMsg::isLittleEndian() {
	int i = 1;
	char * p = (char *)&i;
	if (*p == 1)
		return true;
	
	return false;
}