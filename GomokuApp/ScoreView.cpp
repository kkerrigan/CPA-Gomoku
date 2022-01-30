/*
Kristian Kerrigan
ScoreView.cpp
This file contains the implementation for the ScoreView class.
*/

#include "ScoreView.hpp"
using namespace GomokuMVC;
using namespace std;

void ScoreView::update() {
	// print the outline of the view

	for (int i = 0; i < this->VIEW_WIDTH; ++i) {
		this->model.windowsFunctions.paintTile(this->OFFSET_X + i, 0, this->VIEW_OUTLINE);
		this->model.windowsFunctions.paintTile(this->OFFSET_X + i, this->VIEW_HEIGHT, this->VIEW_OUTLINE);
	}

	for (int i = 0; i < this->VIEW_HEIGHT + 1; ++i) {
		this->model.windowsFunctions.paintTile(this->OFFSET_X, i, this->VIEW_OUTLINE);
		this->model.windowsFunctions.paintTile(this->OFFSET_X + this->VIEW_WIDTH, i, this->VIEW_OUTLINE);
	}

	// Print Total Score label
	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 2, 2, this->model.BACKGROUND_WHITE, "Total Moves");

	//get total moves from the model's stack
	int totalMoves = this->model.previousMoves.size();
	string moves = std::to_string(totalMoves);

	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 4, 4, this->model.BACKGROUND_WHITE, "    ");
	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 4, 4, this->model.BACKGROUND_WHITE, moves);

	//Print player labels for streak count
	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 2, 6, this->model.PLAYER_1_TEXT_COLOR, this->model.player1Name);
	this->model.windowsFunctions.writeToConsole(this->OFFSET_X + 2, 8, this->model.PLAYER_2_TEXT_COLOR, this->model.player2Name);
}