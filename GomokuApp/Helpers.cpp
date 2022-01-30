/*
Kristian Kerrigan
Helpers.cpp
This file contains the implementation for the Helpers class.
*/

#include "Helpers.hpp"
using namespace GomokuMVC;
using namespace std;

// Board View Helpers
bool Helpers::isValidCoord(COORD coord) {
	// Each tile is 4 pixels wide and 2 pixels high, so check that the x and y values fall within that range
	// Otherwise you are not clicking on the coord
	if (coord.X >= 0 && coord.X <= 19 * 4) {
		if (coord.Y >= 0 && coord.Y <= 19 * 2) {
			if (coord.X % 4 == 1 && coord.Y % 2) {
				return true;
			}
		}
	}
	return false;
}

void Helpers::mapToGrid(COORD& coord) {
	//Mod the x coord by 4 since each board tile is 4 pixels wide
	// If it is zero it is the correct values, otherwise correct for the difference
	int rawCoord = coord.X % 4;
	if (rawCoord == 3) {
		coord.X -= 2;
	}
	else if (rawCoord == 2) {
		coord.X -= 1;
	}
}

bool Helpers::isEmptySquare(COORD coord, GameModel& model) {
	// divide the x coord by 4 (4 pixels wide) and y coord by 2 (2 pixels high) and check that the value at 
	// that position is 0, otherwise tile is taken
	return model.boardStatus[coord.X / 4][coord.Y / 2] == 0;
}