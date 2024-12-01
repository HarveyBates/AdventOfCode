import numpy as np

lights = np.zeros((1000, 1000))


def part_one():
    with open("input.txt", "r") as f:
        for line in f.readlines():
            line = line.strip().split(" ")
            if line[0] == "turn":
                line.pop(0)

            instruction = line[0]
            start_x, start_y = map(int, line[1].split(","))
            end_x, end_y = map(int, line[3].split(","))

            for x in range(start_x, end_x + 1):
                for y in range(start_y, end_y + 1):
                    if instruction == "on":
                        lights[x][y] = 1
                    if instruction == "off":
                        lights[x][y] = 0
                    if instruction == "toggle":
                        lights[x][y] = 1 if lights[x][y] == 0 else 0

        print(np.count_nonzero(lights))
    f.close()


lights = np.zeros((1000, 1000))


def part_two():
    with open("input.txt", "r") as f:
        for line in f.readlines():
            line = line.strip().split(" ")
            if line[0] == "turn":
                line.pop(0)

            instruction = line[0]
            start_x, start_y = map(int, line[1].split(","))
            end_x, end_y = map(int, line[3].split(","))

            for x in range(start_x, end_x + 1):
                for y in range(start_y, end_y + 1):
                    if instruction == "on":
                        lights[x][y] += 1
                    if instruction == "off":
                        lights[x][y] -= 1
                        if lights[x][y] < 0:
                            lights[x][y] = 0
                    if instruction == "toggle":
                        lights[x][y] += 2

        print(int(np.sum(lights)))
    f.close()


# part_one()
part_two()
