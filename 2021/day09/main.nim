import std/[strutils, sequtils, enumerate]

var heightmap = readFile("input.txt").strip().splitLines()

var heights = newSeq[seq[int]]()
for height in heightmap:
  var values = height.map(proc(x: char): int = ($x).parseInt)
  heights.add(@[values])

var visited = newSeq[tuple[x: int, y: int]]()

proc solve_one(): int = 
  for y, row in enumerate(heights):
    for x, value in enumerate(row):
      var center, left, right, up, down: tuple[num: int, state: bool]
      center = (num: value, state: true)
      if(x > 0):
        left = (num: row[x-1], state: true)
      if(x < len(row) - 1):
        right = (num: row[x+1], state: true)
      if (y > 0):
        up = (num: heights[y-1][x], state: true)
      if (y < heights.len - 1):
        down = (num: heights[y+1][x], state: true)

      var positions = @[left, right, up, down]

      var cnt, stateCnt: int
      for pos in positions:
        if (center.num < pos.num):
          inc(cnt)
        if (pos.state):
          inc(stateCnt)
      if(cnt == stateCnt):
        result = result + center.num + 1


# No go for part 2 yet

echo solve_one()
