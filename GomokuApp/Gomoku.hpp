/*
Kristian Kerrigan
Gomoku.hpp
This file represents the game logic for the Gomoku Game and inherits from the App class so that it 
is a Singleton.
*/


#pragma once
#include <App.hpp>
#include <Console.hpp>
#include <stack>


// Wrap in a namespace so that constant expressions can be defined for the class and not be in the global scope
namespace GomokuMVC {

	constexpr WORD BACKGROUND_WHITE = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
	constexpr WORD BOARD_OUTLINE = BACKGROUND_WHITE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	class Gomoku : public App {
	public:
		bool done_;

	protected:
		Console gameFunctions;
		int execute() override;
		
	}myApp;

}