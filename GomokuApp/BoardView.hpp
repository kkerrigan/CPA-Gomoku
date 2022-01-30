/*
Kristian Kerrigan
BoardView.hpp
This file contains the concrete observer object responsible for drawing the 
game board.
*/

#pragma once
#include "View.hpp"
#include "GameModel.hpp"

namespace GomokuMVC {

	class BoardView : public View {
		GameModel& model;

	public: 
		BoardView(GameModel& gm) : model(gm){}
		void update() override;
	};
}