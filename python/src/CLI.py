#!/usr/bin/env python3

from tictactoe import Grid


def main():
	game = Grid(3)
	outcome = game.outCome()
	while outcome == "playing":
		print(str(game))
		playerInput = input(game.whoIsPlaying() + " to play: ")
		if playerInput == "exit":
			break
		try:
			x = int(playerInput[0])
			y = int(playerInput[2])
			if not game.play(x, y):
				print("Invalid move")
		except:
			print("Invalid move")
		outcome = game.outCome()
	print(str(game))
	if outcome == "draw":
		print("Draw 😞\n")
	else:
		print("Circle wins 🎉\n")


if __name__ == "__main__":
	main()