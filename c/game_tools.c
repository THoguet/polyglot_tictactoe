#include "game_tools.h"

bool isXYInWiningLine(uint x, uint y, uint winingLine[], uint nb_square) {
	for (uint i = 0; i < nb_square; i++)
		if (winingLine[i * 2] == x && winingLine[i * 2 + 1] == y)
			return true;
	return false;
}

int min(int a, int b) {
	return a < b ? a : b;
}