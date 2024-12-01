# Part 1
floor = 1
with open("input.txt", "r") as f:
    for bracket in f.readline():
        if bracket == "(":
            floor += 1
        else:
            floor -= 1
    f.close()
print(floor)

# Part 2
floor = 1
with open("input.txt", "r") as f:
    for i, bracket in enumerate(f.readline()):
        if bracket == "(":
            floor += 1
        else:
            floor -= 1
        if floor == -1:
            print(i)
            break
    f.close()
