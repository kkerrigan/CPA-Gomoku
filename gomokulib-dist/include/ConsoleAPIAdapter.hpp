/*
Kristian Kerrigan
ConsoleAPIAdapter.hpp
This file contains a thin wrapper for the Windows Console API. In this class, all the Console API methods needed to change 
the state of the console are called.
*/

#pragma once
#include "XError.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ConsoleAPIAdapter {
	// System Data
	HANDLE						hConsoleInput_, hConsoleOutput_;
	WORD						currentConsoleWidth = 0;

public:
	ConsoleAPIAdapter();

	void SaveOriginalTitle(std::vector<char>& originalTitle);
	inline void SetTitle(std::vector<char>& title) { SetConsoleTitleA(title.data()); }
	inline void SetConsoleInputMode(DWORD mode) {
		SetConsoleMode(this->hConsoleInput_, mode); 
	}
	inline void GetOrignalConsoleMode(DWORD& oldMode) { GetConsoleMode(this->hConsoleInput_, &oldMode); }
	inline void SetCtrlHandler(PHANDLER_ROUTINE routine) {
		SetConsoleCtrlHandler(routine, TRUE);
	}
	inline void GetOldBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi) { THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(this->hConsoleOutput_, &csbi)); }
	void GetScreenBufferData(std::vector<CHAR_INFO>& bufferData, CONSOLE_SCREEN_BUFFER_INFO& csbi);
	inline void SaveCursor(CONSOLE_CURSOR_INFO& cciOriginal) { THROW_IF_CONSOLE_ERROR(GetConsoleCursorInfo(this->hConsoleOutput_, &cciOriginal)); }
	void ResizeWindow(WORD width, WORD height);
	void HideConsoleCursor(CONSOLE_CURSOR_INFO& cci);
	void RestoreWindow(CONSOLE_SCREEN_BUFFER_INFO& csbiOriginal, std::vector<CHAR_INFO>& originalBuffer);
	inline void RestoreTitle(std::vector<char>& originalTitle) { SetConsoleTitleA(originalTitle.data()); }
	inline void RestoreCursor(CONSOLE_CURSOR_INFO& cciOriginal, CONSOLE_SCREEN_BUFFER_INFO& csbiOriginal) {
		THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(this->hConsoleOutput_, &cciOriginal));
		THROW_IF_CONSOLE_ERROR(SetConsoleCursorPosition(this->hConsoleOutput_, csbiOriginal.dwCursorPosition));
	}
	inline bool ReadInput(std::vector<INPUT_RECORD>& buffer, DWORD& number) {
		return ReadConsoleInput(this->hConsoleInput_, buffer.data(), (DWORD)buffer.size(), &number);
	}
	void FillConsoleBackground(WORD colour);
	void PaintTile(SHORT posX, SHORT posY, WORD color, int ascii = 0);
	void WriteToConsole(SHORT posX, SHORT posY, WORD color, std::string message);
};