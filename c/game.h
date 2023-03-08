/**
 * @file game.h
 * @brief Basic Game Functions.
 * @details See @ref index for further details.
 **/

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

/**
 * @brief Standard unsigned integer type.
 **/
typedef unsigned int uint;

/**
 * @brief Size of the default game grid.
 **/
#define DEFAULT_SIZE 3

/**
 * @brief Number of squares in a row needed to win by default.
 **/
#define DEFAULT_NB_SQUARE 3

/**
 * @brief Different squares used in the game.
 **/
typedef enum {
	S_BLANK = 0, /**< a blank square */
	S_CROSS,     /**< a cross square */
	S_CIRCLE,
} square;

typedef enum {
	CROSS_WON = 1,
	CIRCLE_WON,
	PLAYING,
	DRAW,
} outcome;

struct game_s {
	square** board;
	uint height;  // y
	uint width;   // x
	uint nb_square;
};

/**
 * @brief The structure pointer that stores the game state.
 **/
typedef struct game_s* game;

/**
 * @brief Creates a new game.
 * @param height The height of the game grid.
 * @param width The width of the game grid.
 * @param nb_square The number of squares in a row needed to win.
 * @return A pointer to the new game.
 **/
game game_new(uint height, uint width, uint nb_square);

/**
 * @brief Frees the memory used by a game.
 * @param g The game to free.
 **/
void game_delete(game g);

/**
 * @brief Returns the height of a game grid.
 * @param g The game.
 * @return The height of the game grid.
 **/
uint game_height(game g);

/**
 * @brief Returns the width of a game grid.
 * @param g The game.
 * @return The width of the game grid.
 **/
uint game_width(game g);

/**
 * @brief Returns the square at a given position.
 * @param g The game.
 * @param x The x coordinate of the square.
 * @param y The y coordinate of the square.
 * @return The square at the given position.
 **/
square game_get_square(game g, uint x, uint y);

/**
 * @brief Returns the number of squares in a row needed to win.
 * @param g The game.
 * @return The number of squares in a row needed to win.
 **/
uint game_get_nb_square_to_win(game g);
/**
 * @brief Sets the square at a given position.
 * @param g The game.
 * @param x The x coordinate of the square.
 * @param y The y coordinate of the square.
 * @param s The square to set.
 **/
void game_set_square(game g, uint x, uint y, square s);

/**
 * @brief Returns the outcome of a game.
 * @param g The game.
 * @param winingLine An array of size 2*nb_square that will contain the coordinates of the winning line.
 * @return The outcome of the game.
 **/
outcome game_outcome(game g, uint winingLine[]);

#endif