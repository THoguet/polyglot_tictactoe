#include "game.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

game game_new(uint height, uint width, uint nb_square) {
	game g = malloc(sizeof(*g));
	g->board = malloc(sizeof(square*) * width);
	for (uint x = 0; x < width; x++)
		g->board[x] = calloc(height, sizeof(square));
	g->height = height;
	g->width = width;
	g->nb_square = nb_square;
	return g;
}

void game_delete(game g) {
	for (uint x = 0; x < g->width; x++) {
		free(g->board[x]);
		g->board[x] = NULL;
	}
	free(g->board);
	g->board = NULL;
	free(g);
	g = NULL;
}

uint game_height(game g) {
	return g->height;
}

uint game_width(game g) {
	return g->width;
}

square game_get_square(game g, uint x, uint y) {
	return g->board[x][y];
}

void game_set_square(game g, uint x, uint y, square s) {
	g->board[x][y] = s;
}

uint game_get_nb_square_to_win(game g) {
	return g->nb_square;
}

outcome game_outcome(game g, uint winingLine[]) {
	// Directions are: right, left, up, down, right-up, left-down, right-down, left-up
	const uint nbDir = 8;
	int directionsX[] = {1, -1, 0, 0, 1, -1, 1, -1};
	int directionsY[] = {0, 0, 1, -1, 1, -1, -1, 1};
	// count the number of blank squares to check if the game is a draw
	uint nb_blank = 0;
	for (uint x = 0; x < g->width; x++) {
		for (uint y = 0; y < g->height; y++) {
			if (g->board[x][y] == S_BLANK)
				nb_blank++;
			else {
				// Check if there is a row of g->nb_square squares of the same type
				uint nbSquare = 0;
				for (uint i = 0; i < nbDir; i++) {
					// Check if the current square is the first of a new direction
					if (i % 2 == 0)
						nbSquare = 0;
					else
						nbSquare--;
					uint x2 = x;
					uint y2 = y;
					// Check if the next square is out of the board
					bool x2NegativeNext = false;
					bool y2NegativeNext = false;
					bool x2SupNext = false;
					bool y2SupNext = false;
					// Check if the next square is the same as the current one
					while (!(x2NegativeNext || y2NegativeNext || x2SupNext || y2SupNext) && g->board[x2][y2] == g->board[x][y]) {
						// if so increment the number of square and go to the next square
						nbSquare++;
						winingLine[(nbSquare - 1) * 2] = x2;
						winingLine[(nbSquare - 1) * 2 + 1] = y2;
						x2NegativeNext = (x2 == 0 && directionsX[i] == -1);
						y2NegativeNext = (y2 == 0 && directionsY[i] == -1);
						x2SupNext = (x2 == g->width - 1 && directionsX[i] == 1);
						y2SupNext = (y2 == g->height - 1 && directionsY[i] == 1);
						x2 += directionsX[i];
						y2 += directionsY[i];
					}
					if (nbSquare >= g->nb_square)
						return (outcome)g->board[x][y];
				}
			}
		}
	}
	if (nb_blank == 0)
		return DRAW;
	return PLAYING;
}