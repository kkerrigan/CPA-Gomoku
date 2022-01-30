/*
Kristian Kerrigan
Controller.hpp
This file contains the controller for the MVC framework all commands originate from here.
*/

#pragma once
#include "GameModel.hpp"
#include "BoardView.hpp"
#include "ScoreView.hpp"
#include "MovesView.hpp"

namespace GomokuMVC {

	BOOL CtrlHandler(DWORD ctrlType);

	class Controller {
		GameModel model;
		BoardView board;
		ScoreView score;
		MovesView movesList;

	public:
		bool static done;
		void beginGame();
		void gameLoop();
		void exitGame();
		void MouseEventProc(MOUSE_EVENT_RECORD const& mer);
		void ProcessKeyEvent(KEY_EVENT_RECORD const& ker);

		//Contructor
		Controller() : board(BoardView(this->model)), score(ScoreView(this->model)), movesList(MovesView(this->model)) {};

	};

	
}
