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

bool isCellCollision(Vector2 mousePosition, int row, int col) {
    int cellX = col * CELLSIZE;
    int cellY = row * CELLSIZE;
    return mousePosition.x > cellX && mousePosition.x < cellX + CELLSIZE &&
           mousePosition.y > cellY && mousePosition.y < cellY + CELLSIZE &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void drawCell(int row, int col, Color color) {
    int cellX = col * CELLSIZE + CELLSIZE / 2;
    int cellY = row * CELLSIZE + CELLSIZE / 2;
    DrawCircle(cellX, cellY, 10, color);
}

void cellColliders(Board* board, Vector2 mousePosition) {
    for (int row = 0; row < NUMBEROFCELLS; ++row) {
        for (int col = 0; col < NUMBEROFCELLS; ++col) {
            if (isCellCollision(mousePosition, row, col)) {
                drawCell(row, col, RED);
                board->cells[row][col] = X;
            }
        }
    }
}

void drawBoard() {
	// Vertical Lines
	for (int i = 1; i < NUMBEROFCELLS; i++) {
		DrawRectangle(i * CELLSIZE, 0, 1, BOARDSIZE, WHITE);
	}

	// Horizontal Lines
	for (int i = 1; i < NUMBEROFCELLS; i++) {
		DrawRectangle(0, i * CELLSIZE, BOARDSIZE, 1, WHITE);
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

		cellColliders(&board, mousePosition);

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