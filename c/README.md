# TicTacToe in C

## Time spent
- Total : 4 hrs 16 mins 36 secs
- `game.c` : 1 hr 24 mins 10 secs
- `game_test.c` : 1 hr 16 mins 48 secs
- `game_text.c` : 57 mins 59 secs
- `game.h` : 20 mins 38 secs
- `CMakeLists.txt` : 10 mins 32 secs

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