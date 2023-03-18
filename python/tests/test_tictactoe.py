from tictactoe import *


def testCase():
	case = Case(CASECONTENT["empty"], 0, 0)
	assert case.what() == "empty"
	assert case.x == 0
	assert case.y == 0
	assert case.isOnWinLine == False
	case = Case(CASECONTENT["circle"], 1, 2)
	assert case.what() == "circle"
	assert case.x == 1
	assert case.y == 2
	assert case.isOnWinLine == False
	case = Case(CASECONTENT["cross"], 2, 1)
	assert case.what() == "cross"
	assert case.x == 2
	assert case.y == 1
	assert case.isOnWinLine == False
	print("testCase passed")


def testGrid():
	game = Grid(3)
	assert game.size == 3
	assert game.turn == 1
	assert game.grid[0][0].what() == "empty"
	assert game.grid[0][0].x == 0
	assert game.grid[0][0].y == 0
	assert game.grid[0][0].isOnWinLine == False
	assert game.grid[1][1].what() == "empty"
	assert game.grid[1][1].x == 1
	assert game.grid[1][1].y == 1
	assert game.grid[1][1].isOnWinLine == False
	assert game.grid[2][2].what() == "empty"
	assert game.grid[2][2].x == 2
	assert game.grid[2][2].y == 2
	assert game.grid[2][2].isOnWinLine == False
	print("testGrid passed")


def testGridStr():
	game = Grid(3)
	assert str(
	    game
	) == "----------------------\n|0    0|1    0|2    0|\n----------------------\n|0    1|1    1|2    1|\n----------------------\n|0    2|1    2|2    2|\n----------------------\n"
	print("testGridStr passed")


def testGridBehavour():
	# testing vertical line win
	game = Grid(3)
	assert game.grid[0][0].what() == "empty"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 0) == True
	assert game.play(0, 0) == False
	assert game.grid[0][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 1) == True
	assert game.play(1, 1) == False
	assert game.grid[1][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(2, 2) == True
	assert game.play(2, 2) == False
	assert game.grid[2][2].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 0) == True
	assert game.play(1, 0) == False
	assert game.grid[1][0].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 2) == True
	assert game.play(0, 2) == False
	assert game.grid[0][2].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 2) == True
	assert game.play(1, 2) == False
	assert game.grid[1][2].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.outCome() == "cross"
	print("vertical line win passed")
	# testing digonal win
	game = Grid(3)
	assert game.grid[0][0].what() == "empty"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 0) == True
	assert game.play(0, 0) == False
	assert game.grid[0][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(0, 1) == True
	assert game.play(0, 1) == False
	assert game.grid[0][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(1, 1) == True
	assert game.play(1, 1) == False
	assert game.grid[1][1].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(0, 2) == True
	assert game.play(0, 2) == False
	assert game.grid[0][2].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(2, 2) == True
	assert game.play(2, 2) == False
	assert game.grid[2][2].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.outCome() == "circle"
	print("diagonal win passed")
	# testing horizontal line win
	game = Grid(3)
	assert game.grid[0][0].what() == "empty"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 0) == True
	assert game.play(0, 0) == False
	assert game.grid[0][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(0, 1) == True
	assert game.play(0, 1) == False
	assert game.grid[0][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(1, 0) == True
	assert game.play(1, 0) == False
	assert game.grid[1][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 1) == True
	assert game.play(1, 1) == False
	assert game.grid[1][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(2, 0) == True
	assert game.play(2, 0) == False
	assert game.grid[2][0].what() == "circle"
	assert game.outCome() == "circle"
	print("horizontal line win passed")
	# testing draw
	game = Grid(3)
	assert game.grid[0][0].what() == "empty"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 0) == True
	assert game.play(0, 0) == False
	assert game.grid[0][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(0, 1) == True
	assert game.play(0, 1) == False
	assert game.grid[0][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(0, 2) == True
	assert game.play(0, 2) == False
	assert game.grid[0][2].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 0) == True
	assert game.play(1, 0) == False
	assert game.grid[1][0].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(1, 1) == True
	assert game.play(1, 1) == False
	assert game.grid[1][1].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(1, 2) == True
	assert game.play(1, 2) == False
	assert game.grid[1][2].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(2, 0) == True
	assert game.play(2, 0) == False
	assert game.grid[2][0].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.play(2, 1) == True
	assert game.play(2, 1) == False
	assert game.grid[2][1].what() == "cross"
	assert game.whoIsPlaying() == "circle"
	assert game.play(2, 2) == True
	assert game.play(2, 2) == False
	assert game.grid[2][2].what() == "circle"
	assert game.whoIsPlaying() == "cross"
	assert game.outCome() == "draw"
	print("draw passed")
