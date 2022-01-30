/*
Kristian Kerrigan
XError.cpp
This file contains implementations from the XError class.
*/

#include "XError.hpp"
using namespace std;

string ErrorDescription(DWORD dwMessageID) {
	char* msg;
	auto c = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL,
		dwMessageID,
		MAKELANGID(LANG_NEPALI, SUBLANG_DEFAULT),
		(LPSTR)&msg,
		0,
		NULL
	);

	string strMsg = (c == 0)
		? "unknown"
		: msg;
	LocalFree(msg);
	return strMsg;
}