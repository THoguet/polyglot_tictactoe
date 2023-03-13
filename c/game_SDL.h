#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"

#if !defined(GAME_SDL_H)
#define GAME_SDL_H

#define APP_NAME "TicTacToe in C !"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define DELAY 10

#define FONT "Roboto-Regular.ttf"
#define FONTSIZE 200

typedef struct Env_t Env;

Env* init(SDL_Renderer* ren, int argc, const char* argv[]);
void render(SDL_Window* win, SDL_Renderer* ren, Env* env);
void clean(Env* env);
bool process(SDL_Window* win, Env* env, SDL_Event* e);

#endif  // GAME_SDL_H
