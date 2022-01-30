/*
Kristian Kerrigan
MVCCommand.hpp
This file contains the Command object and all the concrete command classes for the
game.
*/

#pragma once
#include <memory>
#include "GameModel.hpp"

namespace GomokuMVC {

	class MVCCommand {
	public:
		using ptr = std::shared_ptr<MVCCommand>;
		virtual void execute() = 0;
	};

	class ResizeWindowCommand : public MVCCommand {
		GameModel& model;
		PHANDLER_ROUTINE handle;
		WORD background_;
	public:
		ResizeWindowCommand(GameModel& gm, PHANDLER_ROUTINE routine, WORD backgroundColor);
		void execute() override;
	};

	class RestoreWindowCommand : public MVCCommand {
		GameModel& model;

	public:
		RestoreWindowCommand(GameModel& gm) : model(gm) {};
		void execute() override;
	};

	class CheckVictoryCommand : public MVCCommand {
		GameModel& model;

	public:
		CheckVictoryCommand(GameModel& gm) : model(gm) {};
		void execute() override;
	};

	class GameSetupCommand : public MVCCommand {
		GameModel& model;

	public:
		GameSetupCommand(GameModel& gm) : model(gm){}
		void execute() override;
	};

	class NewGameCommand : public MVCCommand {
		GameModel& model;

	public:
		NewGameCommand(GameModel& gm) : model(gm) {};
		void execute() override;
	};

	class LeftClickCommand : public MVCCommand {
		GameModel& model;
		COORD coord_;

	public:
		LeftClickCommand(GameModel& gm, COORD coord) : model(gm), coord_(coord){};
		void execute() override;
	};

	class UndoMoveCommand : public MVCCommand {
		GameModel& model;

	public:
		UndoMoveCommand(GameModel& gm) : model(gm) {};
		void execute() override;
	};
}