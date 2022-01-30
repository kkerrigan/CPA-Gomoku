/*
Kristian Kerrigan
ScoreView.hpp
This file contains the concrete observer object responsible for drawing the
current score.
*/

#pragma once
#include "View.hpp"
#include "GameModel.hpp"

namespace GomokuMVC {
	class ScoreView : public View {
		GameModel& model;

	public:
		const int OFFSET_X = 80;
		const int VIEW_OUTLINE = BACKGROUND_GREEN | BACKGROUND_RED;
		const int VIEW_WIDTH = 25;
		const int VIEW_HEIGHT = 10;
		ScoreView(GameModel& gm) : model(gm) {};
		void update() override;
	};
}
