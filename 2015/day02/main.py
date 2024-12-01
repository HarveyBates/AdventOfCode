# Part 1
class Cuboid:
    def __init__(self, length, width, height):
        self.length = length
        self.width = width
        self.height = height

    def get_surface_area(self):
        return (
            2 * self.length * self.width
            + 2 * self.width * self.height
            + 2 * self.height * self.length
        )

    def get_smallest_face(self):
        values = sorted((self.length, self.width, self.height))
        return values[0] * values[1]


wrapping_paper_feet = 0

with open("input.txt", "r") as f:
    for line in f.readlines():
        (length, width, height) = map(int, line[:-1].split("x"))
        cuboid = Cuboid(length, width, height)
        wrapping_paper_feet += cuboid.get_surface_area() + cuboid.get_smallest_face()

    f.close()
print(wrapping_paper_feet)


# Part 2
ribbon_feet = 0
with open("input.txt", "r") as f:
    for line in f.readlines():
        (length, width, height) = map(int, line[:-1].split("x"))
        dims = sorted((length, width, height))
        perimeter = dims[0] * 2 + dims[1] * 2
        volume = length * width * height
        ribbon_feet += perimeter + volume
    f.close()
print(ribbon_feet)
