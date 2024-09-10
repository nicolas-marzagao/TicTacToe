#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARDSIZE 600
#define CELLSIZE 200
#define NUMBEROFCELLS 3

typedef enum CellState {
	X,
	O,
	NONE
} CellState;

typedef struct Board {
	CellState cells[NUMBEROFCELLS][NUMBEROFCELLS];
} Board;

bool isCellCollision(Vector2 mousePosition, int row, int col) {
    int cellX = col * CELLSIZE;
    int cellY = row * CELLSIZE;
    return mousePosition.x > cellX && mousePosition.x < cellX + CELLSIZE &&
           mousePosition.y > cellY && mousePosition.y < cellY + CELLSIZE &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void cellColliders(Board* board, Vector2 mousePosition, bool* aiTurn) {
    for (int row = 0; row < NUMBEROFCELLS; row++) {
        for (int col = 0; col < NUMBEROFCELLS; col++) {
            if (isCellCollision(mousePosition, row, col)) {
				if (board->cells[row][col] == NONE) {
					board->cells[row][col] = X;
					(*aiTurn) = true;
				}
            }
        }
    }
}

void drawCell(int row, int col, CellState cell) {
    int cellX = col * CELLSIZE + CELLSIZE / 2;
    int cellY = row * CELLSIZE + CELLSIZE / 2;
	
	if (cell == X) {
    	DrawCircle(cellX, cellY, 20, BLUE);
	}
	else {
		DrawCircle(cellX, cellY, 20, RED);
	}
}

void drawBoard(Board* board) {
	// Vertical Lines
	for (int i = 1; i < NUMBEROFCELLS; i++) {
		DrawRectangle(i * CELLSIZE, 0, 1, BOARDSIZE, WHITE);
	}

	// Horizontal Lines
	for (int i = 1; i < NUMBEROFCELLS; i++) {
		DrawRectangle(0, i * CELLSIZE, BOARDSIZE, 1, WHITE);
	}

	for (int row = 0; row < NUMBEROFCELLS; row++) {
		for (int col = 0; col < NUMBEROFCELLS; col++) {
			if (board->cells[row][col] != NONE) {
				drawCell(row, col, board->cells[row][col]);
			}
		}
	}
}

CellState getWinner(Board* board) {
	for (int i = 0; i < NUMBEROFCELLS; i++) {
		if (board->cells[i][0] == board->cells[i][1] && board->cells[i][1] == board->cells[i][2]) return board->cells[i][0];
	}

	for (int i = 0; i < NUMBEROFCELLS; i++) {
		if (board->cells[0][i] == board->cells[1][i] && board->cells[1][i] == board->cells[2][i]) return board->cells[i][0];
	}

	if (board->cells[0][0] == board->cells[1][1] && board->cells[1][1] == board->cells[2][2]) return board->cells[0][0];
	if (board->cells[0][2] == board->cells[1][1] && board->cells[1][1] == board->cells[2][0]) return board->cells[0][2];

	return NONE;
}

int main () {
	srand(time(NULL));

	Board board;
	// Initialize cells to NONE
    for (int i = 0; i < NUMBEROFCELLS; i++) {
        for (int j = 0; j < NUMBEROFCELLS; j++) {
            board.cells[i][j] = NONE;
        }
    }

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(BOARDSIZE, BOARDSIZE, "TicTacToe");
	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");
	// Texture wabbit = LoadTexture("wabbit_alpha.png");

	Vector2 mousePosition;
	int aichoice[2];
	bool aiTurn = false;
	CellState winner;


	while (!WindowShouldClose())
	{
		winner = getWinner(&board);

		if (winner != NONE) {
			if (winner == X) printf("X wins!\n");
			else printf("O wins!\n");
			break;
		}
		else {
			mousePosition = GetMousePosition();

			cellColliders(&board, mousePosition, &aiTurn);

			if (aiTurn) {
				aichoice[0] = rand() % 3;
				aichoice[1] = rand() % 3;

				printf("Ai row: %d col %d\n", aichoice[0], aichoice[1]);

				if (board.cells[aichoice[0]][aichoice[1]] == NONE) {
					board.cells[aichoice[0]][aichoice[1]] = O;
					aiTurn = false;
				}
			}

			// drawing
			BeginDrawing();

			// Setup the backbuffer for drawing (clear color and depth buffers)
			ClearBackground(BLACK);
			
			drawBoard(&board);
			
			// end the frame and get ready for the next one  (display frame, poll input, etc...)
			EndDrawing();
		}
	}

	// UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}