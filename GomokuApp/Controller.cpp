/*
Kristian Kerrigan
Controller.cpp
This file contains the implementation for the Controller class.
*/

#include <vector>
#include "Controller.hpp"
#include "MVCCommand.hpp"
#include "Helpers.hpp"
using namespace std;
using namespace GomokuMVC;

BOOL GomokuMVC::CtrlHandler(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
		Controller::done = true;
		return TRUE;
	}
	return FALSE;
}

bool Controller::done = false;

void Controller::beginGame() {
	MVCCommand::ptr(new ResizeWindowCommand(this->model, (PHANDLER_ROUTINE)CtrlHandler, this->model.BACKGROUND_WHITE))->execute();
	MVCCommand::ptr(new GameSetupCommand(this->model))->execute();
}

void Controller::gameLoop() {

	// Setup game board
	this->model.attach(&this->board);
	this->model.notify();

	// Setup score view
	this->model.attach(&this->score);
	this->model.notify();

	//Setup moves view
	this->model.attach(&this->movesList);
	this->model.notify();

	vector<INPUT_RECORD> inBuffer(128);
	while (!this->model.done_) {
		// Catch mouse events
		DWORD numEvents;
		if (!this->model.windowsFunctions.readInput(inBuffer, numEvents)) {
			cerr << "Failed to read console input\n";
			break;
		}
		for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
			switch (inBuffer[iEvent].EventType) {
			case MOUSE_EVENT:
				MouseEventProc(inBuffer[iEvent].Event.MouseEvent);
				break;
			case KEY_EVENT:
				ProcessKeyEvent(inBuffer[iEvent].Event.KeyEvent);
				break;
			}
		}

		if (Controller::done)
			this->model.done_ = true;
	}
}

void Controller::exitGame() {
	MVCCommand::ptr(new RestoreWindowCommand(this->model))->execute();
}

void Controller::MouseEventProc(MOUSE_EVENT_RECORD const& mer) {
#if !defined(MOUSE_HWHEELED)
#define MOUSE_HWHEELED 0X0008
#endif
	switch (mer.dwEventFlags) {
	case 0: // button pressed or released
	{
		auto mask = mer.dwButtonState;
		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED) {
			COORD coord = mer.dwMousePosition;
			Helpers::mapToGrid(coord);

			if (!Helpers::isValidCoord(coord))
				return;
			if (!Helpers::isEmptySquare(coord, this->model))
				return;

			MVCCommand::ptr(new LeftClickCommand(this->model, coord))->execute();

		}

		if (mask&RIGHTMOST_BUTTON_PRESSED)
			MVCCommand::ptr(new UndoMoveCommand(this->model))->execute();
	} break;
	}
}

void Controller::ProcessKeyEvent(KEY_EVENT_RECORD const& ker) {
	//lets us keyup events as they dont repeat
	if (!ker.bKeyDown) {
		if (ker.uChar.AsciiChar == 'r') {
			MVCCommand::ptr(new NewGameCommand(this->model))->execute();
		}
	}
}



