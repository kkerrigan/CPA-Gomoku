/*
Kristian Kerrigan
GameModel.hpp
This file contains the concrete subject and model for the MVC framework.
Holds all the state data for the game.
*/

#pragma once
#include <Console.hpp>
#include <stack>
#include "Subject.hpp"

namespace GomokuMVC {

	class GameModel : public Subject {
	public:
		Console windowsFunctions;

		const int BACKGROUND_WHITE = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
		const int BOARD_OUTLINE = 0 | FOREGROUND_GREEN;
		const int PLAYER_1_TEXT_COLOR = BACKGROUND_WHITE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		const int PLAYER_2_TEXT_COLOR = BACKGROUND_WHITE | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		
		const int BOARD_WIDTH = 19;
		const int BOARD_HEIGHT = 19;

		int boardStatus[19][19];
		bool player1Turn_;
		bool done_;
		std::stack<COORD> previousMoves;
		WORD player1Color = BACKGROUND_RED;
		WORD player2Color = BACKGROUND_BLUE;
		std::string player1Name = "Player 1";
		std::string player2Name = "Player 2";
	};

}