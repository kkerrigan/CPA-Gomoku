/*
Kristian Kerrigan
BoardView.cpp
This file contains the implementation for the BoardView class.
*/

#include "BoardView.hpp"
#include "Helpers.hpp"
using namespace GomokuMVC;

void BoardView::update() {
	// board drawing logic
	for (int x = 0; x < ((this->model.BOARD_WIDTH * 4) + 1); ++x) {
		for (int y = 0; y < ((this->model.BOARD_HEIGHT * 2) + 1); ++y) {

			// Check if tile is occupied
			COORD tile;
			tile.X = x;
			tile.Y = y;

			Helpers::mapToGrid(tile);

			if (Helpers::isValidCoord(tile)) {

				int player = this->model.boardStatus[tile.X / 4][tile.Y / 2];
				int color = 0;

				if (player == 1) {
					color = this->model.player1Color;
				}
				else if (player == 2) {
					color = this->model.player2Color;
				}
				else {
					color = this->model.BACKGROUND_WHITE;
				}

				this->model.windowsFunctions.paintTile(tile.X, tile.Y, color);
				this->model.windowsFunctions.paintTile(tile.X + 1, tile.Y, color);
			}

			//first row
			if (y == 0) {
				if (x == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 201);
				}
				else if (x == (model.BOARD_WIDTH * 4)) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 187);
				}
				else if (x % 4 == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 203);
				}
				else {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 205);
				}
			}
			else if (y == (this->model.BOARD_HEIGHT * 2)) {
				if (x == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 200);
				}
				else if (x == (this->model.BOARD_WIDTH * 4)) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 188);
				}
				else if (x % 4 == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 202);
				}
				else {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 205);
				}
			}
			else {
				if (x == 0) {
					if (y % 2 == 0) {
						this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 204);
					}
					else {
						this->model.windowsFunctions.paintTile(x, y, this-> model.BOARD_OUTLINE, 186);
					}
				}
				else if (x == (this->model.BOARD_WIDTH * 4)) {
					if (y % 2 == 0) {
						this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 185);
					}
					else {
						this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 186);
					}
				}
				else if (y % 2 == 0 && x % 4 == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 206);
				}
				else if (y % 2 == 0 && x % 4 != 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 205);
				}
				else if (y % 2 != 0 && x % 4 == 0) {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE, 186);
				}
				else {
					this->model.windowsFunctions.paintTile(x, y, this->model.BOARD_OUTLINE);
				}
			}
		}
	}
}