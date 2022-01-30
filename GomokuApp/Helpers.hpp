/*
Kristian Kerrigan
Helpers.hpp
This file contains some static helper methods for determining if the click is on the game board and
that the tile is available.
*/

#pragma once
#include <Console.hpp>
#include "GameModel.hpp"

namespace GomokuMVC {
	
	class Helpers {
	
	public:
		static bool isValidCoord(COORD coord);
		static void mapToGrid(COORD& coord);
		static bool isEmptySquare(COORD coord, GameModel& model);
	};
}