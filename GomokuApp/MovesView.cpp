/*
Kristian Kerrigan
MovesView.cpp
This file contains the implementation for the MovesView class.
*/

#include "MovesView.hpp"
#include "Helpers.hpp"
using namespace GomokuMVC;
using namespace std;

MovesView::MovesView(GameModel& gm) : model(gm) {
	this->gridPos = map<int, string>();
	gridPos[0] = "A";
	gridPos[1] = "B";
	gridPos[2] = "C";
	gridPos[3] = "D";
	gridPos[4] = "E";
	gridPos[5] = "F";
	gridPos[6] = "G";
	gridPos[7] = "H";
	gridPos[8] = "I";
	gridPos[9] = "J";
	gridPos[10] = "K";
	gridPos[11] = "L";
	gridPos[12] = "M";
	gridPos[13] = "N";
	gridPos[14] = "O";
	gridPos[15] = "P";
	gridPos[16] = "Q";
	gridPos[17] = "R";
	gridPos[18] = "S";
}

void MovesView::update() {

	for (int i = 0; i < this->VIEW_WIDTH; ++i) {
		for (int j = 0; j < this->VIEW_HEIGHT; ++j) {
			this->model.windowsFunctions.paintTile(this->OFFSET_X + i, this->OFFSET_Y + j, this->model.BACKGROUND_WHITE);
		}
	}

	// Print the outline of the view
	for (int i = 0; i < this->VIEW_WIDTH; ++i) {
		this->model.windowsFunctions.paintTile(this->OFFSET_X + i, this->OFFSET_Y, this->VIEW_OUTLINE);
		this->model.windowsFunctions.paintTile(this->OFFSET_X + i, this->OFFSET_Y + this->VIEW_HEIGHT, this->VIEW_OUTLINE);
	}

	for (int i = 0; i < this->VIEW_HEIGHT + 1; ++i) {
		this->model.windowsFunctions.paintTile(this->OFFSET_X, this->OFFSET_Y + i, this->VIEW_OUTLINE);
		this->model.windowsFunctions.paintTile(this->OFFSET_X + this->VIEW_WIDTH, this->OFFSET_Y + i, this->VIEW_OUTLINE);
	}

	// Print view title
	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 2, this->OFFSET_Y + 1, this->model.BACKGROUND_WHITE, "Moves List");

	std::stack<COORD> previousMovesClone = this->model.previousMoves;
	std::vector<COORD> movesList;

	while (previousMovesClone.size() != 0) {
		movesList.push_back(previousMovesClone.top());
		previousMovesClone.pop();
	}

	//reverse the vector since stacks are LIFO
	std::reverse(movesList.begin(), movesList.end());

	int count = 0;
	for (auto i = 0; i < (int)(movesList.size()); ++i) {

		int color = 0;
		if (count % 2 == 0) {
			color = this->model.PLAYER_1_TEXT_COLOR;
		}
		else {
			color = this->model.PLAYER_2_TEXT_COLOR;
		}

		std::string stringToWrite = showPosition(movesList.at(i));
		this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 2, this->OFFSET_Y + 2 + count, color, stringToWrite);

		movesList.erase(movesList.begin());
		//increment counter so color changes
		++count;
		i--; // decrement here so that the beginning is at the right spot
	}
}

string MovesView::showPosition(COORD coord) {
	return this->gridPos[coord.X / 4] + " : " + to_string((coord.Y / 2) + 1);
}