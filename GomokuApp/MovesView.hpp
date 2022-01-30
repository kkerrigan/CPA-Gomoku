/*
Kristian Kerrigan
MoveView.hpp
This file contains the concrete observer object responsible for displaying 
the list of moves.
*/

#pragma once
#include <map>
#include <string>
#include "View.hpp"
#include "GameModel.hpp"

namespace GomokuMVC {

	class MovesView : public View {
		GameModel& model;

	public:
		const int OFFSET_X = 80;
		const int OFFSET_Y = 12;
		const int VIEW_WIDTH = 25;
		const int VIEW_HEIGHT = 25;
		const int VIEW_OUTLINE = BACKGROUND_GREEN | BACKGROUND_RED;

		std::map<int, std::string> gridPos;

		MovesView(GameModel& gm);
		void update() override;
		std::string showPosition(COORD coord);
	};
}
