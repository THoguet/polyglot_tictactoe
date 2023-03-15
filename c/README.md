# TicTacToe in C

## Time spent
- Total : 9 hrs 45 mins
- `game_SDL.c` : 2 hrs 46 mins
- `game_text.c` : 2 hrs 5 mins
- `game.c` : 1 hr 24 mins
- `game_test.c` : 1 hr 16 mins
- `c.yml` : 1 hr
- `CMakeLists.txt` : 26 mins
- `game.h` : 21 mins

## Dependencies

```bash
apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev # for Linux Debian/Ubuntu
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer                            # for MacOS
```

## Compilation

With CMake:

```bash
mkdir build ; cd build ; cmake .. ; make
```

## CLI

```bash
./game_text [height width nb_square]
```

## Graphical Interface

```bash
./game_sdl [height width nb_square]
```
