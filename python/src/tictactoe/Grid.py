from .Case import Case
from .const import CASECONTENT, DIRECTIONS


class Grid:

	def __init__(self, size):
		self.size = size
		self.grid = [[Case(CASECONTENT["empty"], x, y) for x in range(size)] for y in range(size)]
		self.turn = 1

	def whoIsPlaying(self):
		return list(CASECONTENT.keys())[self.turn % 2]

	def __str__(self):
		ret = ""
		for _ in range(self.size):
			ret += "-------"
		ret += "-\n"
		for y in range(self.size):
			ret += "|"
			for x in range(self.size):
				ret += str(x) + str(self.grid[x][y]) + str(y)
				if x != self.size - 1:
					ret += "|"
			ret += "|\n"
			for _ in range(self.size):
				ret += "-------"
			ret += "-\n"
		return ret

	def getCaseDir(self, case: Case, dir):
		retX = case.x + dir[0]
		retY = case.y + dir[1]
		if retX < 0 or retX >= self.size or retY < 0 or retY >= self.size:
			return None
		return self.grid[retX][retY]

	def nbCaseEmpty(self):
		ret = 0
		for cList in self.grid:
			for c in cList:
				if c.what() == "empty":
					ret += 1
		return ret

	def outCome(self):
		if self.nbCaseEmpty() == 0:
			return "draw"
		for cList in self.grid:
			for c in cList:
				for dir in DIRECTIONS:
					case1 = self.getCaseDir(c, DIRECTIONS[dir])
					if case1 is None:
						continue
					case2 = self.getCaseDir(case1, DIRECTIONS[dir])
					if case2 is None:
						continue
					if (c.what() == case1.what()) and (c.what() == case2.what()) and (c.what() != "empty"):
						c.isOnWinLine = True
						case1.isOnWinLine = True
						case2.isOnWinLine = True
						return c.what()
		return "playing"

	def play(self, x, y):
		if self.grid[x][y].what() == "empty":
			self.grid[x][y] = Case(list(CASECONTENT.values())[self.turn % 2], x, y)
			self.turn += 1
			return True
		return False
