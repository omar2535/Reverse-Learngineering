#include "stdafx.h"
#include "utils.h"

char *StringToCharArr(std::string strToConvert) {
	char *charRet = new char[strToConvert.length() + 1];
	std::strcpy(charRet, strToConvert.c_str());
	return charRet;
}