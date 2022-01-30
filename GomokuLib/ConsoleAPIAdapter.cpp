/*
Kristian Kerrigan
ConsoleAPIAdapter.cpp
This file contains all the implementions from ConsoleAPIAdapter.hpp
*/

#include "ConsoleAPIAdapter.hpp"
using namespace std;

ConsoleAPIAdapter::ConsoleAPIAdapter() {
	this->hConsoleInput_ = GetStdHandle(STD_INPUT_HANDLE);
	this->hConsoleOutput_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleAPIAdapter::SaveOriginalTitle(vector<char>& originalTitle) {
	originalTitle = vector<char>(64 * 1024);
	originalTitle.resize(GetConsoleTitleA(originalTitle.data(), (DWORD)originalTitle.size() + 1));
	originalTitle.shrink_to_fit();
}

void ConsoleAPIAdapter::GetScreenBufferData(vector<CHAR_INFO>& bufferData, CONSOLE_SCREEN_BUFFER_INFO& csbi) {
	SMALL_RECT bufferRect{ 0 };
	bufferData.resize(csbi.dwSize.X * csbi.dwSize.Y);

	bufferRect.Right = csbi.dwSize.X - 1;
	bufferRect.Bottom = csbi.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(this->hConsoleOutput_, bufferData.data(), csbi.dwSize, COORD{ 0 }, &bufferRect));
}

void ConsoleAPIAdapter::ResizeWindow(WORD width, WORD height) {
	SMALL_RECT sr{ 0 };
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(this->hConsoleOutput_, TRUE, &sr));

	COORD newBuffer;
	newBuffer.X = width;
	newBuffer.Y = height;
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(this->hConsoleOutput_, newBuffer));

	CONSOLE_SCREEN_BUFFER_INFO sbi;
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(this->hConsoleOutput_, &sbi));

	sr.Top = sr.Left = 0;
	width = std::min((SHORT)width, sbi.dwMaximumWindowSize.X);
	height = std::min((SHORT)height, sbi.dwMaximumWindowSize.Y);
	sr.Right = width - 1;
	sr.Bottom = height - 1;
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(this->hConsoleOutput_, TRUE, &sr));
	this->currentConsoleWidth = sr.Right - sr.Left + 1;
}

void ConsoleAPIAdapter::HideConsoleCursor(CONSOLE_CURSOR_INFO& cci) {
	auto newCCI = cci;
	newCCI.bVisible = FALSE;
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(this->hConsoleOutput_, &newCCI));
}

void ConsoleAPIAdapter::RestoreWindow(CONSOLE_SCREEN_BUFFER_INFO& csbiOriginal, vector<CHAR_INFO>& originalBuffer) {
	// Restore the original settings/size
	SMALL_RECT sr{ 0 };
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(this->hConsoleOutput_, TRUE, &sr));
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(this->hConsoleOutput_, csbiOriginal.dwSize));
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(this->hConsoleOutput_, TRUE, &csbiOriginal.srWindow));

	SMALL_RECT bufferRect = SMALL_RECT{ 0 };
	bufferRect.Right = csbiOriginal.dwSize.X - 1;
	bufferRect.Bottom = csbiOriginal.dwSize.Y - 1;
	WriteConsoleOutputA(this->hConsoleOutput_, originalBuffer.data(), csbiOriginal.dwSize, COORD{ 0 }, &bufferRect);
}

void ConsoleAPIAdapter::FillConsoleBackground(WORD colour) {
	// Get the number of character cells in the current buffer
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(this->hConsoleOutput_, &csbi));

	// Fill the entire screen area white
	DWORD charsWritten;
	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD cursorHomeCoord{ 0, 0 };
	THROW_IF_CONSOLE_ERROR(
		FillConsoleOutputCharacterA(this->hConsoleOutput_, ' ', consoleSize, cursorHomeCoord, &charsWritten));
	THROW_IF_CONSOLE_ERROR(
		FillConsoleOutputAttribute(this->hConsoleOutput_, colour, consoleSize, cursorHomeCoord, &charsWritten));
}

void ConsoleAPIAdapter::PaintTile(SHORT posX, SHORT posY, WORD color, int ascii) {
	COORD cursorHomeCoord{ posX, posY };
	vector<WORD> attr{
		WORD(color)
	};
	COORD loc;
	loc.X = posX;
	loc.Y = posY;

	DWORD nCharsWritten;

	// Convert ASCII int to char value
	string msg(1, char(ascii));

	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputCharacterA(this->hConsoleOutput_, msg.c_str(), (DWORD)msg.size(), loc, &nCharsWritten));
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputAttribute(this->hConsoleOutput_, attr.data(), (DWORD)attr.size(), loc, &nCharsWritten));

}

void ConsoleAPIAdapter::WriteToConsole(SHORT posX, SHORT posY, WORD color, string message) {
	COORD cursorHomeCoord{ posX, posY };
	
	
	vector<WORD> attr;
	for (int i = 0; i < (int)message.size(); ++i) {
		attr.push_back((WORD(color)));
	}

	COORD loc;
	loc.X = posX;
	loc.Y = posY;

	DWORD nCharsWritten;

	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputCharacterA(this->hConsoleOutput_, message.c_str(), (DWORD)message.size(), loc, &nCharsWritten));
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputAttribute(this->hConsoleOutput_, attr.data(), (DWORD)attr.size(), loc, &nCharsWritten));

}