/*
Kristian Kerrigan
Gomoku.cpp
This file contains all of the implementation code for the Gomoku class.
*/


#include "Gomoku.hpp"
#include "Controller.hpp"
#include <iostream>
using namespace std;
using namespace GomokuMVC;

int Gomoku::execute() {
	Controller gomokuController;
	
	gomokuController.beginGame();
	gomokuController.gameLoop();
	gomokuController.exitGame();

	return 0;
}
