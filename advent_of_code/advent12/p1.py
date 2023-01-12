from string import ascii_lowercase
from heapq import heappop, heappush

with open("test.txt") as file:
    lines = file.read().strip().split()

print lines

grid = [list(line) for line in lines]
n = len(grid)
m = len(grid[0])
