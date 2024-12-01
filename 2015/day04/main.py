import hashlib


def solve(search_term):
    n = 0

    with open("input.txt", "r") as f:
        key = f.readline().strip()

        while True:
            encoded_key = key + str(n)
            md5 = hashlib.md5()
            md5.update(encoded_key.encode("utf-8"))
            hex_hash = md5.hexdigest()
            if hex_hash.startswith(search_term):
                break
            n += 1

        f.close()

    return n


# Part 1
print(solve("00000"))

# Part 2
print(solve("000000"))
