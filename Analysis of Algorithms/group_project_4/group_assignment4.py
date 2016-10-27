from pulp import *
from math import *

def bestFit(f):
	prob = LpProblem("min abs dev", LpMinimize)
	x0 = LpVariable("x0")
	x1 = LpVariable("x1")
	x2 = LpVariable("x2")
	x3 = LpVariable("x3")
	x4 = LpVariable("x4")
	x5 = LpVariable("x5")
	t = LpVariable("t")
	prob += t
	for line in f:
		values = line.strip("\n")
		values = line.split(";")
		values = values[7:]
		values = map(float, values)
		prob += x0 + (x1 * values[1]) + (x2 * cos((2 * pi * values[1]) / 365.25)) + (x3 * sin((2 * pi * values[1]) / 365.25)) + (x4 * cos((2 * pi * values[1]) / (365.25 * 10.7))) + (x5 * sin((2 * pi * values[1]) / (365.25 * 10.7))) - values[0] <= t
		prob += -x0 - (x1 * values[1]) - (x2 * cos((2 * pi * values[1]) / 365.25)) - (x3 * sin((2 * pi * values[1]) / 365.25)) - (x4 * cos((2 * pi * values[1]) / (365.25 * 10.7))) - (x5 * sin((2 * pi * values[1]) / (365.25 * 10.7))) + values[0] <= t
	status = prob.solve()
	print LpStatus[status]
	answers = []
	answers.append(value(x0))
	answers.append(value(x1))
	answers.append(value(x2))
	answers.append(value(x3))
	answers.append(value(x4))
	answers.append(value(x5))
	print answers

if __name__ == "__main__":
	f = open("Corvallis_data.csv")
	bestFit(f)