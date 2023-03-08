cmake_minimum_required(VERSION 2.6...3.26)

#nom du projet
project ("TicTacToe" C)

# enable testing
enable_testing()
set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --leak-check=full")
include(CTest)

## use pkgconfig to solve SDL2 dependencies (Linux only)
# include(FindPkgConfig) # pkg-config --list-all  | grep -i sdl2
# pkg_search_module(SDL2 REQUIRED sdl2)
# pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
# pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
# pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
# set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
# set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

## use a CMake3 package to solve SDL2 dependencies
find_package(SDL2)
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS})
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image -lSDL2_mixer) # add extra SDL2 libraries


message(STATUS "SDL2 include dir: ${SDL2_ALL_INC}")
message(STATUS "SDL2 all libraries: ${SDL2_ALL_LIBS}")

#positionne la variable
set(CMAKE_C_FLAGS "-std=c99 -Wall")
set(CMAKE_C_FLAGS_DEBUG "-g --coverage -pthread -Wextra -Wunused-parameter -Wpedantic -Werror")    # use CMake option: -DCMAKE_BUILD_TYPE=DEBUG
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")   # use CMake option: -DCMAKE_BUILD_TYPE=RELEASE

######################### COPY IMGAES #########################

file(GLOB ASSETS
  "${CMAKE_CURRENT_SOURCE_DIR}/assets/*"
)
message(STATUS "Assets found: ${ASSETS}")
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


############################# SRC #############################

# game_text
add_executable(game_text game_text.c)
target_link_libraries(game_text game)

# game_tests
add_executable(game_test game_test.c)
target_link_libraries(game_test game)

# game_sdl
# if (SDL2_FOUND)
# 	include_directories(${SDL2_ALL_INC})
# 	add_executable(game_sdl game_SDL.c)
# 	target_link_libraries(game_sdl game ${SDL2_ALL_LIBS})
# endif()

# libgame
add_library (game game.c)


############################# TESTS #############################

add_test(test_game_new ./game_test game_new)
add_test(test_game_delete ./game_test game_delete)
add_test(test_game_height ./game_test game_height)
add_test(test_game_width ./game_test game_width)
add_test(test_game_get_square ./game_test game_get_square)
add_test(test_game_get_nb_square_to_win ./game_test game_get_nb_square_to_win)
add_test(test_game_set_square ./game_test game_set_square)
add_test(test_game_outcome ./game_test game_outcome)