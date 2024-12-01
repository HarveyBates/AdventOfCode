def part_one():
    vowels = ["a", "e", "i", "o", "u"]
    disallowed = ["ab", "cd", "pq", "xy"]

    with open("input.txt", "r") as f:
        nice = 0
        for line in f.readlines():
            n_vowels = 0
            n_doubles = 0
            err = False
            last_c = None
            for c in line.strip():
                for v in vowels:
                    if c == v:
                        n_vowels += 1
                        break
                if last_c == c:
                    n_doubles += 1

                for dis in disallowed:
                    if last_c == dis[0] and c == dis[1]:
                        err = True
                        break
                last_c = c

            if n_vowels >= 3 and n_doubles > 0 and not err:
                nice += 1

        print(nice)
        f.close()


def part_two():
    with open("input.txt", "r") as f:
        nice = 0
        for line in f.readlines():
            line = line.strip()

            has_pair = False

            for i in range(len(line) - 1):
                offset = i + 2
                pair = line[i:offset]
                if pair in line[offset:]:
                    has_pair = True
                    break

            has_triple = False
            for i in range(len(line) - 2):
                if line[i] == line[i + 2]:
                    has_triple = True
                    break

            if has_pair and has_triple:
                nice += 1
        print(nice)


# part_one()
part_two()
