/*
Kristian Kerrigan
Console.hpp
This file contains a thick wrapper class that performs actions on the console by calling the thin wrapper class.
This file also contains all the state data for the console, set by calling the thin wrapper class.
*/

#pragma once
#include "ConsoleAPIAdapter.hpp"

class Console {
	ConsoleAPIAdapter			consoleApi_;
	CONSOLE_SCREEN_BUFFER_INFO	csbiOriginal_;
	CONSOLE_CURSOR_INFO			cciOriginal_;
	std::vector<CHAR_INFO>		originalBuffer_;
	std::vector<char>			originalConsoleTitle_;
	COORD						originalBufferCoord_;
	DWORD						originalConsoleMode_;

public:
	void setNewConsoleTitle(std::string title) {
		std::vector<char> titleVec = std::vector<char>(title.begin(), title.end());
		titleVec.resize(titleVec.size() + 1);
		this->consoleApi_.SetTitle(titleVec);
	}
	void saveConsoleState() {
		this->consoleApi_.SaveOriginalTitle(this->originalConsoleTitle_);
		this->consoleApi_.GetOldBufferInfo(this->csbiOriginal_);
		this->consoleApi_.GetScreenBufferData(this->originalBuffer_, this->csbiOriginal_);
		this->consoleApi_.SaveCursor(this->cciOriginal_);
	}
	inline void resizeConsoleWindow(WORD width, WORD height) { this->consoleApi_.ResizeWindow(width, height); }
	inline void hideCursor() { this->consoleApi_.HideConsoleCursor(this->cciOriginal_); }
	inline void restoreOriginalWindow() {
		this->consoleApi_.RestoreWindow(this->csbiOriginal_, this->originalBuffer_);
		this->consoleApi_.RestoreTitle(this->originalConsoleTitle_);
		this->consoleApi_.RestoreCursor(this->cciOriginal_, this->csbiOriginal_);
	}
	inline void getOldConsoleMode() { this->consoleApi_.GetOrignalConsoleMode(this->originalConsoleMode_); }
	inline void setConsoleMode(DWORD mode) {
		this->consoleApi_.SetConsoleInputMode(mode);
	}
	inline void setCtrlHandle(PHANDLER_ROUTINE routine) { this->consoleApi_.SetCtrlHandler(routine); }
	inline void fillGameBackground(WORD color) { this->consoleApi_.FillConsoleBackground(color); }
	inline bool readInput(std::vector<INPUT_RECORD>& buffer, DWORD& number) {
		return this->consoleApi_.ReadInput(buffer, number);
	}
	inline void paintTile(SHORT posX, SHORT posY, WORD color, int ascii = 0) {
		this->consoleApi_.PaintTile(posX, posY, color, ascii);
	}
	inline void writeToConsole(SHORT posX, SHORT posY, WORD color, std::string message) {
		this->consoleApi_.WriteToConsole(posX, posY, color, message);
	}
};
