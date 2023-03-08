#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_game_new(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				if (g->height != testHeight || g->width != testWidth || g->nb_square != testNbSquare)
					return false;
				for (uint x = 0; x < g->width; x++) {
					for (uint y = 0; y < g->height; y++) {
						if (g->board[x][y] != S_BLANK)
							return false;
						g->board[x][y] = S_CIRCLE;
						if (g->board[x][y] != S_CIRCLE)
							return false;
						g->board[x][y] = S_CROSS;
						if (g->board[x][y] != S_CROSS)
							return false;
					}
				}
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_delete(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_height(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				if (game_height(g) != testHeight)
					return false;
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_width(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				if (game_width(g) != testWidth)
					return false;
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_get_square(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				for (uint x = 0; x < g->width; x++) {
					for (uint y = 0; y < g->height; y++) {
						if (game_get_square(g, x, y) != S_BLANK)
							return false;
						g->board[x][y] = S_CIRCLE;
						if (game_get_square(g, x, y) != S_CIRCLE)
							return false;
						g->board[x][y] = S_CROSS;
						if (game_get_square(g, x, y) != S_CROSS)
							return false;
					}
				}
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_set_square(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testHeight = 3; testHeight < 50; testHeight++) {
		for (uint testWidth = 3; testWidth < 50; testWidth++) {
			for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
				game g = game_new(testHeight, testWidth, testNbSquare);
				for (uint x = 0; x < g->width; x++) {
					for (uint y = 0; y < g->height; y++) {
						game_set_square(g, x, y, S_CIRCLE);
						if (g->board[x][y] != S_CIRCLE)
							return false;
						game_set_square(g, x, y, S_CROSS);
						if (g->board[x][y] != S_CROSS)
							return false;
						game_set_square(g, x, y, S_BLANK);
						if (g->board[x][y] != S_BLANK)
							return false;
					}
				}
				game_delete(g);
			}
		}
	}
	return true;
}

bool test_game_get_nb_square_to_win(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	for (uint testNbSquare = 2; testNbSquare < 25; testNbSquare++) {
		game g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, testNbSquare);
		if (game_get_nb_square_to_win(g) != testNbSquare)
			return false;
		game_delete(g);
	}
	return true;
}

bool test_game_outcome(bool whoami, char** name) {
	if (whoami) {
		*name = (char*)__func__;
		return false;
	}
	game g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_NB_SQUARE);
	uint winingLine[DEFAULT_NB_SQUARE * 2];
	// test circle line win
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 2, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 0, S_CIRCLE);
	if (game_outcome(g, winingLine) != CIRCLE_WON)
		return false;
	else {
		bool nb11 = true;
		bool nb12 = true;
		bool nb10 = true;
		for (int i = 0; i < DEFAULT_NB_SQUARE; i++) {
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 1)
				nb11 = false;
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 2)
				nb12 = false;
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 0)
				nb10 = false;
		}
		if (nb11 || nb12 || nb10)
			return false;
	}
	game_delete(g);
	// test cross line win
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 2, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 0, S_CROSS);
	if (game_outcome(g, winingLine) != CROSS_WON)
		return false;
	else {
		bool nb11 = true;
		bool nb12 = true;
		bool nb10 = true;
		for (int i = 0; i < DEFAULT_NB_SQUARE; i++) {
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 1)
				nb11 = false;
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 2)
				nb12 = false;
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 0)
				nb10 = false;
		}
		if (nb11 || nb12 || nb10)
			return false;
	}
	game_delete(g);
	// test circle column win
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != CIRCLE_WON)
		return false;
	else {
		bool nb11 = true;
		bool nb21 = true;
		bool nb01 = true;
		for (int i = 0; i < DEFAULT_NB_SQUARE; i++) {
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 1)
				nb11 = false;
			if (winingLine[i * 2] == 2 && winingLine[i * 2 + 1] == 1)
				nb21 = false;
			if (winingLine[i * 2] == 0 && winingLine[i * 2 + 1] == 1)
				nb01 = false;
		}
		if (nb11 || nb21 || nb01)
			return false;
	}
	game_delete(g);
	// test cross column win
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 1, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 1, S_CROSS);
	if (game_outcome(g, winingLine) != CROSS_WON)
		return false;
	else {
		bool nb11 = true;
		bool nb21 = true;
		bool nb01 = true;
		for (int i = 0; i < DEFAULT_NB_SQUARE; i++) {
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 1)
				nb11 = false;
			if (winingLine[i * 2] == 2 && winingLine[i * 2 + 1] == 1)
				nb21 = false;
			if (winingLine[i * 2] == 0 && winingLine[i * 2 + 1] == 1)
				nb01 = false;
		}
		if (nb11 || nb21 || nb01)
			return false;
	}
	game_delete(g);
	// test circle diagonal win
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 2, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 0, S_CIRCLE);
	if (game_outcome(g, winingLine) != CIRCLE_WON)
		return false;
	else {
		bool nb11 = true;
		bool nb22 = true;
		bool nb00 = true;
		for (int i = 0; i < DEFAULT_NB_SQUARE; i++) {
			if (winingLine[i * 2] == 1 && winingLine[i * 2 + 1] == 1)
				nb11 = false;
			if (winingLine[i * 2] == 2 && winingLine[i * 2 + 1] == 2)
				nb22 = false;
			if (winingLine[i * 2] == 0 && winingLine[i * 2 + 1] == 0)
				nb00 = false;
		}
		if (nb11 || nb22 || nb00)
			return false;
	}
	game_delete(g);
	// test cross diagonal win
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 2, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 0, S_CROSS);
	if (game_outcome(g, winingLine) != CROSS_WON)
		return false;
	game_delete(g);
	// test a game with a board of size 3x3 and 3 squares to win + draw
	g = game_new(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
	game_set_square(g, 1, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 2, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 1, 0, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 1, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 1, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 0, S_CROSS);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 2, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 0, 2, S_CROSS);
	if (game_outcome(g, winingLine) != CROSS_WON)
		return false;
	game_set_square(g, 0, 2, S_CIRCLE);
	if (game_outcome(g, winingLine) != PLAYING)
		return false;
	game_set_square(g, 2, 0, S_CROSS);
	if (game_outcome(g, winingLine) != DRAW)
		return false;
	game_set_square(g, 2, 0, S_CIRCLE);
	if (game_outcome(g, winingLine) != CIRCLE_WON)
		return false;
	game_delete(g);
	return true;
}

/* ********** USAGE ********** */

int usage(char* argv[]) {
	fprintf(stderr, "Usage: %s <testname>\n", argv[0]);
	exit(EXIT_FAILURE);
}

/* ********** MAIN ********** */

int main(int argc, char* argv[]) {
	if (argc != 2) {
		usage(argv);
	}
	// function type
	typedef bool (*func_p)(bool, char**);
	// array of all tests functions
	func_p tab_fct[] = {test_game_new,        test_game_delete, test_game_height, test_game_width, test_game_get_square, test_game_get_nb_square_to_win,
	                    test_game_set_square, test_game_outcome};
	// array of the tests functions's name
	char* tab_fct_name[sizeof(tab_fct) / sizeof(tab_fct[0])];
	// get each function's name from tab_fct by calling the function with its first parm set to true and the second one with a pointer on tab_fct_name to fill
	// it to get the name of the i-th element of tab_fct, get it with tab_fct_name[i]
	for (uint index_tab_fct = 0; index_tab_fct < sizeof(tab_fct) / sizeof(tab_fct[0]); index_tab_fct++) {
		func_p f = tab_fct[index_tab_fct];
		(*f)(true, tab_fct_name + index_tab_fct);
		// remove the test_ from the functions's name
		tab_fct_name[index_tab_fct] = tab_fct_name[index_tab_fct] + 5;
	}
	fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
	bool test_success = false;
	bool test_found = false;
	for (uint index_tab_fct = 0; index_tab_fct < sizeof(tab_fct) / sizeof(tab_fct[0]); index_tab_fct++) {
		if (strcmp(argv[1], tab_fct_name[index_tab_fct]) == 0) {
			test_success = tab_fct[index_tab_fct](false, NULL);
			test_found = true;
		}
	}
	if (!test_found) {
		fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	// print test result
	if (test_success) {
		fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
		return EXIT_SUCCESS;
	} else {
		fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
		return EXIT_FAILURE;
	}
}