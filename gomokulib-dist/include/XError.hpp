/*
Kristian Kerrigan
XError.hpp
This file contains an error handling class.
*/

#pragma once
#include <Windows.h>
#undef min

#include <string>
#include <sstream>

std::string ErrorDescription(DWORD dwMessageID);

class XError {
public:
	using id_type = decltype(GetLastError());
	using file_type = char const *;
	using string_type = std::string;
private:
	id_type code_;
	int line_;
	file_type file_;
public:
	XError(int line, file_type file) : code_(GetLastError()), line_(line), file_(file) {}
	auto code() const -> id_type { return code_; }
	auto line() const -> int { return line_; }
	auto file() const -> file_type { return file_; }

	string_type msg() const {
		std::ostringstream oss;
		oss << "Error: " << code() << "\n";
		oss << ErrorDescription(code()) << "\n";
		oss << "In: " << file() << "\n";
		oss << "Line: " << line() << "\n";
		return oss.str();
	}
};

// Error Macros
#define THROW_IF_CONSOLE_ERROR(res) if(!res) throw XError(__LINE__, __FILE__)
#define THROW_CONSOLE_ERROR() throw XError(__LINE__, __FILE__)
