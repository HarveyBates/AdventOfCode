


with open("../input_day8.txt", 'r') as f:
    rows = [r for r in f]
    acc = 0
    for i in range(len(rows)):
        inst = rows[i][0:3]
        op = rows[i][4]
        arg = int(rows[i][5:])

        if inst == "acc":
            if op == "+":
                acc += arg
            else:
                acc -= arg

        if inst == "jmp":
            if op == "+":
                i += arg
            else:
                i -= arg

        print(inst, op, arg, acc, i)
