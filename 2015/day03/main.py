import numpy as np

ARR_SIZE = 200
assert ARR_SIZE % 2 == 0


def move_location(direction, x, y):
    if direction == "^":
        y -= 1
    elif direction == "v":
        y += 1
    elif direction == ">":
        x += 1
    elif direction == "<":
        x -= 1
    return x, y


# Part 1
houses = np.zeros((ARR_SIZE, ARR_SIZE))
x = int(ARR_SIZE / 2)
y = int(ARR_SIZE / 2)
with open("input.txt", "r") as f:
    directions = f.readline().strip()
    for direction in directions:
        x, y = move_location(direction, x, y)
        houses[x][y] += 1
    print(np.count_nonzero(houses))
    f.close()


# Part 2
houses = np.zeros((ARR_SIZE, ARR_SIZE))
x1, y1 = int(ARR_SIZE / 2), int(ARR_SIZE / 2)
x2, y2 = int(ARR_SIZE / 2), int(ARR_SIZE / 2)
houses[x1][y1] = 2
with open("input.txt", "r") as f:
    directions = f.readline().strip()
    for idx, direction in enumerate(directions):
        if idx % 2 == 0:
            x1, y1 = move_location(direction, x1, y1)
            houses[x1][y1] += 1
        else:
            x2, y2 = move_location(direction, x2, y2)
            houses[x2][y2] += 1

    print(np.count_nonzero(houses))
    f.close()
