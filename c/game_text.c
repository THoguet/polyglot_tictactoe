#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_tools.h"

void printGame(game g, outcome o, uint winingLine[]) {
	uint nbChar = 4;
	if (game_width(g) >= 10 || game_height(g) >= 10)
		nbChar = 6;

	for (uint y = 0; y < g->height; y++) {
		for (uint x = 0; x < g->width; x++)
			printf("%*s", nbChar + 1, "-------");
		printf("-\n");
		for (uint x = 0; x < g->width; x++) {
			printf("|");
			if (g->board[x][y] == S_BLANK)
				if (o == PLAYING)
					if (game_width(g) < 10 && game_height(g) < 10)
						printf("%u  %u", x, y);
					else
						printf("%2u  %2u", x, y);
				else
					printf("%*s", nbChar, "      ");
			else if (game_get_square(g, x, y) == S_CIRCLE) {
				if (o == CIRCLE_WON && isXYInWiningLine(x, y, winingLine, game_get_nb_square_to_win(g)))
					printf("%*s⭕️%*s", (nbChar - 1) / 2, "--", (nbChar - 1) / 2, "--");
				else
					printf("%*s⭕️%*s", (nbChar - 1) / 2, "  ", (nbChar - 1) / 2, "  ");
			} else if (game_get_square(g, x, y) == S_CROSS) {
				if (o == CROSS_WON && isXYInWiningLine(x, y, winingLine, game_get_nb_square_to_win(g)))
					printf("%*s❌%*s", (nbChar - 1) / 2, "--", (nbChar - 1) / 2, "--");
				else
					printf("%*s❌%*s", (nbChar - 1) / 2, "  ", (nbChar - 1) / 2, "  ");
			}
		}
		printf("|\n");
	}
	for (uint x = 0; x < g->width; x++)
		printf("%*s", nbChar + 1, "-------");
	printf("-\n");
}

int main(int argc, char** argv) {
	uint height = DEFAULT_SIZE;
	uint width = DEFAULT_SIZE;
	uint nb_square = DEFAULT_NB_SQUARE;
	if (argc > 1) {
		if (argc != 4) {
			printf("Usage: %s [height width nb_square]\n", argv[0]);
			return EXIT_FAILURE;
		}
		height = atoi(argv[1]);
		width = atoi(argv[2]);
		nb_square = atoi(argv[3]);
	}
	uint* winingLine = malloc(sizeof(uint) * nb_square * 2);
	game g = game_new(height, width, nb_square);
	outcome o = PLAYING;
	printGame(g, o, winingLine);
	uint x, y;
	square next_player = S_CIRCLE;
	while (o == PLAYING) {
		printf("\n\nPlayer %s, enter coordinates: ", (next_player == S_CIRCLE) ? "⭕️" : "❌");
		if (scanf(" %u %u", &x, &y) != 2) {
			printf("Invalid input\n");
			scanf("%*[^\n]");
			continue;
		}
		if (x >= g->width || y >= g->height) {
			printf("Too big\n");
			scanf("%*[^\n]");
			continue;
		}
		if (game_get_square(g, x, y) != S_BLANK) {
			printf("Square already played\n");
			scanf("%*[^\n]");
			continue;
		}
		game_set_square(g, x, y, next_player);
		o = game_outcome(g, winingLine);
		printGame(g, o, winingLine);
		next_player = (next_player == S_CIRCLE) ? S_CROSS : S_CIRCLE;
		scanf("%*[^\n]");
	}
	if (o == CIRCLE_WON)
		printf("Circle wins 🎉\n");
	else if (o == CROSS_WON)
		printf("Cross wins 🎉\n");
	else
		printf("Draw 😞\n");
	game_delete(g);
	free(winingLine);
	return EXIT_SUCCESS;
}