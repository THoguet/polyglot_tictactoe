#include "game_SDL.h"
#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_tools.h"

struct Env_t {
	game g;  // the game
	uint* winingLine;
	outcome o;

	SDL_Texture* cross;   // array of two texture one white and one red for each number (red color = r:255 g:50 b:50)
	SDL_Texture* circle;  // Same

	SDL_Texture* new_game;  // texture of the new game button

	SDL_Rect* rec_game;      // rectangle of the grid
	SDL_Rect* rec_new_game;  // ^^

	square next_player;  // next player to play

	int i;
	int j;
};

Env* init(SDL_Renderer* ren, int argc, const char* argv[]) {
	Env* env = malloc(sizeof(Env));
	if (!env)
		fprintf(stderr, "Error: malloc env (%s)", SDL_GetError());

	env->cross = IMG_LoadTexture(ren, "cross.png");
	if (!env->cross)
		fprintf(stderr, "Error: IMG_LoadTexture cross (%s)", SDL_GetError());
	env->circle = IMG_LoadTexture(ren, "circle.png");
	if (!env->circle)
		fprintf(stderr, "Error: IMG_LoadTexture circle (%s)", SDL_GetError());

	TTF_Font* font = TTF_OpenFont(FONT, FONTSIZE);
	if (!font)
		fprintf(stderr, "TTF_OpenFont: %s\n", FONT);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	SDL_Color color = {0, 0, 0, 255};
	SDL_Surface* surf = TTF_RenderText_Blended(font, "New game", color);
	env->new_game = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	env->rec_game = malloc(sizeof(SDL_Rect));
	env->rec_game->x = 0;
	env->rec_game->y = 0;
	env->rec_game->w = 0;
	env->rec_game->h = 0;
	env->rec_new_game = malloc(sizeof(SDL_Rect));
	env->rec_new_game->x = 0;
	env->rec_new_game->y = 0;
	env->rec_new_game->w = 0;
	env->rec_new_game->h = 0;
	env->i = 0;
	env->j = 0;
	env->next_player = S_CROSS;
	env->o = PLAYING;

	/* create game */
	uint height = DEFAULT_SIZE;
	uint width = DEFAULT_SIZE;
	uint nb_square = DEFAULT_NB_SQUARE;
	if (argc > 1) {
		if (argc != 4) {
			printf("Usage: %s [height width nb_square]\n", argv[0]);
			return NULL;
		}
		height = atoi(argv[1]);
		width = atoi(argv[2]);
		nb_square = atoi(argv[3]);
	}
	env->winingLine = malloc(sizeof(uint) * nb_square * 2);
	env->g = game_new(height, width, nb_square);
	return env;
}

void render_border_square(SDL_Renderer* ren, SDL_Rect* rec) {
	SDL_SetRenderDrawColor(ren, 200, 200, 200, SDL_ALPHA_OPAQUE);  // gray
	// render the border of the square
	SDL_RenderDrawRect(ren, rec);
}

void render_blank(SDL_Renderer* ren, SDL_Rect* rec, bool onWiningLine) {
	SDL_Color backg;
	if (onWiningLine)
		backg = (SDL_Color){50, 255, 50, SDL_ALPHA_OPAQUE};
	else
		backg = (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE};
	SDL_SetRenderDrawColor(ren, backg.r, backg.g, backg.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, rec);
	render_border_square(ren, rec);
}

void render_square(SDL_Renderer* ren, SDL_Rect* rec, square s, bool onWiningLine, SDL_Texture* cross, SDL_Texture* circle) {
	SDL_Rect sqr;
	render_blank(ren, rec, onWiningLine);
	sqr.h = rec->h * 0.8;
	sqr.w = rec->w * 0.8;
	sqr.h = rec->h - rec->h / 4;
	sqr.w = rec->w - rec->w / 4;
	sqr.x = rec->x + rec->w / 2 - sqr.w / 2;
	sqr.y = rec->y + rec->h / 2 - sqr.h / 2;
	if (s == S_CROSS)
		SDL_RenderCopy(ren, cross, NULL, rec);
	else if (s == S_CIRCLE)
		SDL_RenderCopy(ren, circle, NULL, rec);
	render_border_square(ren, rec);
}

void render(SDL_Window* win, SDL_Renderer* ren, Env* env) {
	int win_w, win_h, h, w;
	SDL_GetWindowSize(win, &win_w, &win_h);
	if (win_h > win_w) {  // used to keep the ratio of the buttons
		h = win_w;
		w = win_w;
	} else {
		h = win_h;
		w = win_h;
	}
	h -= h / 7;  // used by the buttons
	// set background color
	SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);
	SDL_Rect rec;
	int size_rec = min(w / game_width(env->g), h / game_height(env->g));
	rec.h = size_rec;
	rec.w = size_rec;
	int rec_x = w / 2 - size_rec * game_width(env->g) / 2;
	int rec_y = h / 2 - size_rec * game_height(env->g) / 2 + win_h / 7;
	rec.x = rec_x;
	rec.y = rec_y;
	env->rec_game->x = rec.x;
	env->rec_game->y = rec.y;
	env->rec_game->h = size_rec * game_height(env->g);
	env->rec_game->w = size_rec * game_width(env->g);

	/* draw board */
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (uint i = 0; i < game_height(env->g); i++) {
		for (uint j = 0; j < game_width(env->g); j++) {
			bool onWiningLine = false;
			if (env->o != PLAYING && env->o != DRAW)
				onWiningLine = isXYInWiningLine(i, j, env->winingLine, game_get_nb_square_to_win(env->g));
			render_square(ren, &rec, game_get_square(env->g, i, j), onWiningLine, env->cross, env->circle);
			rec.x += size_rec;
		}
		rec.y += size_rec;
		rec.x = rec_x;
	}

	/* draw new game button */
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	env->rec_new_game->h = win_h / 7;
	env->rec_new_game->w = win_w * 0.8;
	env->rec_new_game->x = win_w / 2 - env->rec_new_game->w / 2;
	env->rec_new_game->y = 0;
	SDL_RenderCopy(ren, env->new_game, NULL, env->rec_new_game);
}

bool process(SDL_Window* win, Env* env, SDL_Event* e) {
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	if (e->type == SDL_QUIT)
		return true;
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		SDL_Point mouse;
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&mouse.x, &mouse.y);
			if (SDL_PointInRect(&mouse, env->rec_new_game)) {
				game_delete(env->g);
				env->g = game_new(env->g->height, env->g->width, env->g->nb_square);
				env->o = game_outcome(env->g, env->winingLine);
			} else if (env->o == PLAYING) {
				if (SDL_PointInRect(&mouse, env->rec_game)) {
					env->i = (((float)mouse.y - (float)env->rec_game->y) / (float)env->rec_game->h * game_height(env->g)) - 0.00001;
					env->j = (((float)mouse.x - (float)env->rec_game->x) / (float)env->rec_game->w * game_width(env->g)) - 0.00001;
					if (game_get_square(env->g, env->i, env->j) != S_BLANK) {
						return false;
					}
					game_set_square(env->g, env->i, env->j, env->next_player);
					env->o = game_outcome(env->g, env->winingLine);
					env->next_player = (env->next_player == S_CIRCLE) ? S_CROSS : S_CIRCLE;
				}
			}
		}
	}
	return false;
}

void clean(Env* env) {
	SDL_DestroyTexture(env->cross);
	SDL_DestroyTexture(env->circle);
	SDL_DestroyTexture(env->new_game);
	free(env->rec_game);
	free(env->rec_new_game);
	game_delete(env->g);
	free(env->winingLine);
	free(env);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char const* argv[]) {
	/* initialize SDL2 and some extensions */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stderr, "Error: SDL_Init VIDEO (%s)", SDL_GetError());
	if (IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG)
		fprintf(stderr, "Error: IMG_Init PNG (%s)", SDL_GetError());
	if (TTF_Init() != 0)
		fprintf(stderr, "Error: TTF_Init (%s)", SDL_GetError());
	/* create window and renderer */
	SDL_Window* win =
	    SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!win)
		fprintf(stderr, "Error: SDL_CreateWindow (%s)", SDL_GetError());
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!ren)
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	if (!ren)
		fprintf(stderr, "Error: SDL_CreateRenderer (%s)", SDL_GetError());

	/* initialize your environment */
	Env* env = init(ren, argc, argv);
	if (env == NULL)
		return EXIT_FAILURE;
	/* main render loop */
	SDL_Event e;
	bool quit = false;
	render(win, ren, env);  // first frame
	SDL_RenderPresent(ren);
	while (!quit) {
		/* manage events */
		while (SDL_PollEvent(&e)) {
			/* process your events */
			quit = process(win, env, &e);
			if (quit)
				break;
		}

		/* background in gray */
		SDL_SetRenderDrawColor(ren, 0xA0, 0xA0, 0xA0, 0xFF);
		SDL_RenderClear(ren);

		/* render all what you want */
		render(win, ren, env);
		SDL_RenderPresent(ren);
		SDL_Delay(DELAY);
	}

	/* clean your environment */
	clean(env);

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}