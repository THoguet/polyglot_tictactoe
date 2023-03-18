#!/usr/bin/env python3

import pygame
from tictactoe import Grid

# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

SIZE = 3

game = Grid(SIZE)

# pygame setup
pygame.init()
screen = pygame.display.set_mode((SIZE * 200, SIZE * 200))
pygame.display.set_caption("Tic Tac Toe in Python")
clock = pygame.time.Clock()
running = True

while running:
	outcome = game.outCome()

	# poll for events
	# pygame.QUIT event means the user clicked X to close your window
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False
		if event.type == pygame.MOUSEBUTTONDOWN and outcome == "playing":
			x, y = pygame.mouse.get_pos()
			game.play(x // 200, y // 200)

	# RENDER YOUR GAME HERE
	screen.fill(WHITE)
	for cList in game.grid:
		for c in cList:
			pygame.draw.rect(screen, BLACK, (c.x * 200, c.y * 200, 200, 200), 1)
			if c.what() == "circle":
				pygame.draw.circle(screen, RED, (c.x * 200 + 100, c.y * 200 + 100), 80)
			elif c.what() == "cross":
				pygame.draw.line(screen, RED, (c.x * 200 + 20, c.y * 200 + 20), (c.x * 200 + 180, c.y * 200 + 180), 10)
				pygame.draw.line(screen, RED, (c.x * 200 + 180, c.y * 200 + 20), (c.x * 200 + 20, c.y * 200 + 180), 10)
			if c.isOnWinLine:
				pygame.draw.rect(screen, GREEN, (c.x * 200, c.y * 200, 200, 200), 10)

	# flip() the display to put your work on screen
	pygame.display.flip()

	clock.tick(60)  # limits FPS to 60

pygame.quit()