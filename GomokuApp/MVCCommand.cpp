/*
Kristian Kerrigan
MVCCommand.cpp
This file contains the implementation for the MVCCommand class.
*/

#include <sstream>
#include "MVCCommand.hpp"
using namespace std;
using namespace GomokuMVC;


void GameSetupCommand::execute() {
	this->model.player1Turn_ = true;
	this->model.done_ = false;
}

ResizeWindowCommand::ResizeWindowCommand(GameModel& gm, PHANDLER_ROUTINE routine, const WORD backgroundColor) : model(gm) {
	this->handle = routine;
	this->background_ = backgroundColor;
}

void ResizeWindowCommand::execute() {
	this->model.windowsFunctions.getOldConsoleMode();
	this->model.windowsFunctions.setConsoleMode(ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	this->model.windowsFunctions.saveConsoleState();
	this->model.windowsFunctions.setNewConsoleTitle("Gomoku");
	this->model.windowsFunctions.resizeConsoleWindow(110, 40);
	this->model.windowsFunctions.hideCursor();
	this->model.windowsFunctions.fillGameBackground(this->background_);
	this->model.windowsFunctions.setCtrlHandle(handle);
}

void RestoreWindowCommand::execute() {
	this->model.windowsFunctions.restoreOriginalWindow();
}

void CheckVictoryCommand::execute() {
	for (int i = 0; i < 19 - 4; ++i) {
		for (int j = 0; j < 19; ++j) {

			bool horizontalWin = false;
			// Once the tile is placed, check the 4 tiles to the right of each taken tile to check
			// for a horizontal win
			if (this->model.boardStatus[i][j] != 0) {
				if (this->model.boardStatus[i][j] == this->model.boardStatus[i + 1][j]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 2][j]
					&&
					this->model.boardStatus[i][j] == model.boardStatus[i + 3][j]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 4][j])
				{
					horizontalWin = true;
				}
			}

			bool verticalWin = false;
			// Once the tile is placed, check the 4 tiles below each taken tile to check for a 
			// vertical win
			if (this->model.boardStatus[j][i] != 0) {
				if (this->model.boardStatus[j][i] == this->model.boardStatus[j][i + 1]
					&&
					this->model.boardStatus[j][i] == this->model.boardStatus[j][i + 2]
					&&
					this->model.boardStatus[j][i] == this->model.boardStatus[j][i + 3]
					&&
					this->model.boardStatus[j][i] == this->model.boardStatus[j][i + 4]
					)
				{
					verticalWin = true;
				}
			}

			bool diagonalWin = false;
			// If you are inside the board and the tile is taken, check the 4 downward diagonal tiles
			// to the left of each tile to check for a diagonal win
			if (i < 19 - 4 && j < 19 - 4 && this->model.boardStatus[i][j] != 0) {
				if (this->model.boardStatus[i][j] == this->model.boardStatus[i + 1][j + 1]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 2][j + 2]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 3][j + 3]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 4][j + 4])
				{
					diagonalWin = true;
				}
			}

			// check the four diagonal tiles to the right of each tile
			if (j > 3 && this->model.boardStatus[i][j] != 0) {
				if (this->model.boardStatus[i][j] == this->model.boardStatus[i + 1][j - 1]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 2][j - 2]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 3][j - 3]
					&&
					this->model.boardStatus[i][j] == this->model.boardStatus[i + 4][j - 4])
				{
					diagonalWin = true;
				}
			}

			if (horizontalWin || verticalWin || diagonalWin) {
				stringstream ss;
				ss << "Player  " << (this->model.player1Turn_ ? "2" : "1") << " wins!\n";
				ss << "Click OK to start a New Game";
				MessageBox(NULL, ss.str().c_str(), "Winner", MB_OK);

				MVCCommand::ptr(new NewGameCommand(this->model))->execute();
			}
		}
	}
}

void NewGameCommand::execute() {
	//Loop through the 2-array and set all values to zero to clear the board
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			this->model.boardStatus[i][j] = 0;
		}
	}
	this->model.previousMoves = stack<COORD>();
	MVCCommand::ptr(new GameSetupCommand(this->model))->execute();

	this->model.notify();
}

void LeftClickCommand::execute() {
	this->model.previousMoves.push(coord_);

	if (this->model.player1Turn_) {
		this->model.boardStatus[coord_.X / 4][coord_.Y / 2] = 1;
	}
	else {
		this->model.boardStatus[coord_.X / 4][coord_.Y / 2] = 2;
	}

	this->model.player1Turn_ = !this->model.player1Turn_;
	
	this->model.notify();
	MVCCommand::ptr(new CheckVictoryCommand(this->model))->execute();
	
}

void UndoMoveCommand::execute() {
	if (!this->model.previousMoves.empty()) {
		COORD lastMove = this->model.previousMoves.top();

		this->model.boardStatus[lastMove.X / 4][lastMove.Y / 2] = 0;
		this->model.previousMoves.pop();
		this->model.notify();
	}
}