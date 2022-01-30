#include <Gomoku.hpp>
#include <iostream>
#include <vector>
using namespace std;

namespace Game {

	int Gomoku::execute() {
		// Game Window initialization
		gameFunctions.getOldConsoleMode();
		gameFunctions.setConsoleMode(ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
		gameFunctions.saveConsoleState();
		gameFunctions.setNewConsoleTitle("Gomoku");
		gameFunctions.resizeConsoleWindow(100, 40);
		gameFunctions.hideCursor();
		gameFunctions.fillGameBackground(BACKGROUND_WHITE);
		gameFunctions.setCtrlHandle(CtrlHandler);

		// Draw game board
		drawGameBoard();

		vector<INPUT_RECORD> inBuffer(128);
		while (!done_) {
			// Catch mouse events
			DWORD numEvents;
			if (!gameFunctions.readInput(inBuffer, numEvents)) {
				cerr << "Failed to read console input\n";
				break;
			}
			for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
				switch (inBuffer[iEvent].EventType) {
				case MOUSE_EVENT:
					MouseEventProc(inBuffer[iEvent].Event.MouseEvent);
					break;
				}
			}
		}

		gameFunctions.restoreOriginalWindow();

		return 0;
	}

	void Gomoku::setStartingValues() {

		applicationQuitting_ = false;
		done_ = false;
		player1Turn_ = true;
	}

	void Gomoku::drawGameBoard() {
		int width = 19;
		int height = 19;

		for (int x = 0; x < ((width * 4) + 1); ++x) {
			for (int y = 0; y < ((height * 2) + 1); ++y) {

				//first row
				if (y == 0) {
					if (x == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 201);
					}
					else if (x == (width * 4)) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 187);
					}
					else if (x % 4 == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 203);
					}
					else {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 205);
					}
				}
				else if (y == (height * 2)) {
					if (x == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 200);
					}
					else if (x == (width * 4)) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 188);
					}
					else if (x % 4 == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 202);
					}
					else {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 205);
					}
				}
				else {
					if (x == 0) {
						if (y % 2 == 0) {
							gameFunctions.paintTile(x, y, BOARD_OUTLINE, 204);
						}
						else {
							gameFunctions.paintTile(x, y, BOARD_OUTLINE, 186);
						}
					}
					else if (x == (width * 4)) {
						if (y % 2 == 0) {
							gameFunctions.paintTile(x, y, BOARD_OUTLINE, 185);
						}
						else {
							gameFunctions.paintTile(x, y, BOARD_OUTLINE, 186);
						}
					}
					else if (y % 2 == 0 && x % 4 == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 206);
					}
					else if (y % 2 == 0 && x % 4 != 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 205);
					}
					else if (y % 2 != 0 && x % 4 == 0) {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE, 186);
					}
					else {
						gameFunctions.paintTile(x, y, BOARD_OUTLINE);
					}
				}
			}
		}
	}

	void Gomoku::MouseEventProc(MOUSE_EVENT_RECORD const& mer) {
	#if !defined(MOUSE_HWHEELED)
		#define MOUSE_HWHEELED 0X0008
	#endif
		switch (mer.dwEventFlags) {
		case 0: // button pressed or released
		{
			auto mask = mer.dwButtonState;
			if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
					leftMouseClick(mer.dwMousePosition);
			if (mask&RIGHTMOST_BUTTON_PRESSED)
				cout << " right pressed";
		} break;
		}
	}

	void Gomoku::ProcessKeyEvent(KEY_EVENT_RECORD const& ker) {
		//lets us keyup events as they dont repeat
		if (!ker.bKeyDown) {
			if (ker.uChar.AsciiChar == 'r') {
				//resetGame();
			}
		}
	}

	void Gomoku::mapToGrid(COORD& coord) {
		//correct x 
		int xDiff = coord.X % 4;
		if (xDiff == 3) {
			coord.X -= 2;
		}
		else if (xDiff == 2) {
			coord.X -= 1;
		}
	}

	bool Gomoku::isValidCoord(COORD coord) {
		if (coord.X >= 0 && coord.X <= 19 * 4) {
			if (coord.Y >= 0 && coord.Y <= 19 * 2) {
				if (coord.X % 4 == 1 && coord.Y % 2) {
					return true;
				}
			}
		}
		return false;
	}

	void Gomoku::leftMouseClick(COORD coord) {
		mapToGrid(coord);

		if (!isValidCoord(coord))
			return;
		if (!isTileAvailable(coord))
			return;
		previousMoves.push(coord);
		if (player1Turn_) {
			gameFunctions.paintTile(coord.X, coord.Y, BACKGROUND_RED);

			boardStatus[coord.X / 4][coord.Y / 2] = 1;
		}
		else {
			gameFunctions.paintTile(coord.X, coord.Y, BACKGROUND_BLUE);

			boardStatus[coord.X / 4][coord.Y / 2] = 2;
		}
		isVictory();
		player1Turn_ = !player1Turn_;
	}

	bool Gomoku::isTileAvailable(COORD coord) {
		return boardStatus[coord.X / 4][coord.Y / 2] == 0;
	}

	bool Gomoku::isVictory() {
		for (int i = 0; i < 19 - 4; ++i) {
			for (int j = 0; j < 19; ++j) {

				bool horz = false;
				if (boardStatus[i][j] != 0) {
					if (boardStatus[i][j] == boardStatus[i + 1][j]
						&&
						boardStatus[i][j] == boardStatus[i + 2][j]
						&&
						boardStatus[i][j] == boardStatus[i + 3][j]
						&&
						boardStatus[i][j] == boardStatus[i + 4][j])
					{
						horz = true;
					}
				}

				bool vert = false;
				if (boardStatus[j][i] != 0) {
					if (boardStatus[j][i] == boardStatus[j][i + 1]
						&&
						boardStatus[j][i] == boardStatus[j][i + 2]
						&&
						boardStatus[j][i] == boardStatus[j][i + 3]
						&&
						boardStatus[j][i] == boardStatus[j][i + 4]
						)
					{
						vert = true;
					}
				}

				bool diag = false;
				if (i < 19 - 4 && j < 19 - 4 && boardStatus[i][j] != 0) {
					if (boardStatus[i][j] == boardStatus[i + 1][j + 1]
						&&
						boardStatus[i][j] == boardStatus[i + 2][j + 2]
						&&
						boardStatus[i][j] == boardStatus[i + 3][j + 3]
						&&
						boardStatus[i][j] == boardStatus[i + 4][j + 4])
					{
						diag = true;
					}
				}

				if (j > 3 && boardStatus[i][j] != 0) {
					if (boardStatus[i][j] == boardStatus[i + 1][j - 1]
						&&
						boardStatus[i][j] == boardStatus[i + 2][j - 2]
						&&
						boardStatus[i][j] == boardStatus[i + 3][j - 3]
						&&
						boardStatus[i][j] == boardStatus[i + 4][j - 4])
					{
						diag = true;
					}
				}

				if (horz || vert || diag) {
					stringstream ss;
					ss << "Player  " << (player1Turn_ ? "1" : "2") << " wins!";
					MessageBox(NULL, ss.str().c_str(), "Winner", MB_OK);

					//resetGame();
					return true;
				}
			}
		}

		return false;
	}
}