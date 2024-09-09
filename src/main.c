#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <stdbool.h>

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

bool firstRowFirstCellCollision(Vector2 mousePosition) {
	return mousePosition.x < 200 && mousePosition.y < 200 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool firstRowSecondCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 200 && mousePosition.x < 400 && mousePosition.y < 200 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool firstRowThirdCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 400 && mousePosition.y < 200 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool secondRowFirstCellCollision(Vector2 mousePosition) {
	return mousePosition.x < 200 && mousePosition.y > 200 && mousePosition.y < 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool secondRowSecondCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 200 && mousePosition.x < 400 && mousePosition.y > 200 && mousePosition.y < 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool secondRowThirdCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 400 && mousePosition.y > 200 && mousePosition.y < 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool thirdRowFirstCellCollision(Vector2 mousePosition) {
	return mousePosition.x < 200 && mousePosition.y > 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool thirdRowSecondCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 200 && mousePosition.x < 400 && mousePosition.y > 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool thirdRowThirdCellCollision(Vector2 mousePosition) {
	return mousePosition.x > 400 && mousePosition.y > 400 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void drawBoard() {
	// Vertical Lines
	for (int i = 1; i < 3; ++i) {
		int x = i * CELLSIZE;
		DrawRectangle(x, 0, 1, BOARDSIZE, WHITE);
	}

	// Horizontal Lines
	for (int i = 1; i < 3; ++i) {
		int y = i * CELLSIZE;
		DrawRectangle(0, y, BOARDSIZE, 1, WHITE);
	}
}

void squareColliders(Board* board, Vector2 mousePosition) {
	// First Row
	if (firstRowFirstCellCollision(mousePosition)) {
		DrawCircle(100, 100, 10, RED);  
	}
	if (firstRowSecondCellCollision(mousePosition)) {
		DrawCircle(300, 100, 10, RED);  
	}
	if (firstRowThirdCellCollision(mousePosition)) {
		DrawCircle(500, 100, 10, RED);
	}

	// Second Row
	if (secondRowFirstCellCollision(mousePosition)) {
		DrawCircle(100, 300, 10, RED);
	}
	if (secondRowSecondCellCollision(mousePosition)) {
		DrawCircle(300, 300, 10, RED);
	}
	if (secondRowThirdCellCollision(mousePosition)) {
		DrawCircle(500, 300, 10, RED);
	}

	// Third Row
	if (thirdRowFirstCellCollision(mousePosition)) {
		DrawCircle(100, 500, 10, RED);
	}
	if (thirdRowSecondCellCollision(mousePosition)) {
		DrawCircle(300, 500, 10, RED);
	}
	if (thirdRowThirdCellCollision(mousePosition)) {
		DrawCircle(500, 500, 10, RED);
	}
	
}

int main () {
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
	
	while (!WindowShouldClose())
	{
		mousePosition = GetMousePosition();

		squareColliders(&board, mousePosition);

		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		
		drawBoard();
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}