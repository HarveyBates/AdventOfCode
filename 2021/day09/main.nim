import std/[strutils, sequtils, enumerate, algorithm]

var heightmap = readFile("input.txt").strip().splitLines()

var heights = newSeq[seq[int]]()
for HEIGHT in heightmap:
  var values = HEIGHT.map(proc(x: char): int = ($x).parseInt)
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



proc solve_two(): int =
  var basin = newSeq[int]()
  var searched = newSeq[tuple[x: int, y:int]]()
  var toSearch = newSeq[tuple[x: int, y:int]]()
  var res = newSeq[int]()

  proc eval_pos(x: int, y: int) =
    if(x > 0):
      if heights[y][x-1] != 9:
        toSearch.add((x: x-1, y: y))
    if(x < len(heights[0]) - 1):
      if heights[y][x+1] != 9:
        toSearch.add((x: x+1, y: y))
    if(y > 0):
      if heights[y-1][x] != 9:
        toSearch.add((x: x, y: y-1))
    if (y < len(heights) - 1):
      if heights[y+1][x] != 9:
        toSearch.add((x: x, y: y+1))
  
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
        toSearch.add((x: x, y: y))
        var cnt = 0
        while( cnt < toSearch.len ):
          var found = false
          for completed in searched:
            if (toSearch[cnt] == completed):
              found = true
              break
          if not found:
            eval_pos(toSearch[cnt].x, toSearch[cnt].y)
            searched.add((toSearch[cnt].x, toSearch[cnt].y))
          inc(cnt)

        res.add(deduplicate(toSearch).len)
        toSearch = @[]
  res.sort()
  result = res[^1] * res[^2] * res[^3]
      
  
#echo solve_one()
echo solve_two()
