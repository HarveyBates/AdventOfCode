wires = {}
instructions = {}


def create_wire(wire):
    if wire.isalpha() and wire not in wires:
        wires[wire] = None


def evaluate_wire(wire):
    if wire.isdigit():
        print(wire)
        return int(wire)

    if wires[wire] is not None:
        return wires[wire]

    instruction = instructions[wire]
    parts = instruction.split()

    result = 0
    if len(parts) == 1:
        result = evaluate_wire(parts[0])
    elif "AND" in parts:
        result = evaluate_wire(parts[0]) & evaluate_wire(parts[2])
    elif "OR" in parts:
        result = evaluate_wire(parts[0]) | evaluate_wire(parts[2])
    elif "LSHIFT" in parts:
        result = evaluate_wire(parts[0]) << int(parts[2])
    elif "RSHIFT" in parts:
        result = evaluate_wire(parts[0]) >> int(parts[2])
    elif "NOT" in parts:
        result = ~evaluate_wire(parts[1]) & 0xFFFF

    wires[wire] = result

    return int(wire)


with open("input.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip().split(" ")

        output_wire = line[-1]

        instructions[output_wire] = " ".join(line[:-2])

        create_wire(output_wire)

print(evaluate_wire("a"))

print(wires)
print(instructions)
