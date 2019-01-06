#include "stdafx.h"
#include "utils.h"

char *StringToCharArr(std::string strToConvert) {
	char *charRet = new char[strToConvert.length() + 1];
	std::strcpy(charRet, strToConvert.c_str());
	return charRet;
}

// takes in the number of bytes you want your nop to fill
char *NoOpsBuilder(int numberOfBytes) {
	std::string baseNop = "\x90";
	std::string nopBuilder = "";
	for (int i = 0; i < numberOfBytes; i++) {
		nopBuilder += baseNop;
	}
	return StringToCharArr(nopBuilder);
}

std::vector<BYTE> NoOpsBuilderByte(int numberOfBytes) {
	std::vector<BYTE> byteBuilder = {};
	BYTE nopByte = 0x90;
	for (int i = 0; i < numberOfBytes; i++) {
		byteBuilder.push_back(nopByte);
	}
	return byteBuilder;
}