from .const import CASECONTENT


class Case:

	def __init__(self, char, x, y):
		self.char = char
		self.x = x
		self.y = y
		self.isOnWinLine = False

	def what(self):
		for key, value in CASECONTENT.items():
			if self.char == value:
				return key

	def __str__(self):
		if self.isOnWinLine:
			return "-" + self.char + "-"
		return " " + self.char + " "
