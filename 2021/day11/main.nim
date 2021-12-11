import std/[strutils, sequtils, enumerate]

var rows = readFile("input.txt").strip().splitLines()

var octopus = newSeq[seq[tuple[val: int, state: bool]]]()
for row in rows:
  var value = row.map(proc(x: char): int = ($x).parseInt)
  var s = newSeq[tuple[val: int, state: bool]]()
  for val in value:
    s.add((val: val, state: false))
  octopus.add(s)


proc solve_one_and_two(): int = 
  var res = 0
  proc eval_pos(x: int, y: int) =
    inc(res)
    if(x > 0):
      if not octopus[y][x-1].state: # Left
        octopus[y][x-1] = (val: octopus[y][x-1].val + 1, state: false)
        if octopus[y][x-1].val > 9:
          octopus[y][x-1] = (val: 0, state: true)
          eval_pos(x-1, y)
      if (y > 0 and not octopus[y-1][x-1].state): # Left up
        octopus[y-1][x-1] = (val: octopus[y-1][x-1].val + 1, state: false)
        if octopus[y-1][x-1].val > 9:
          octopus[y-1][x-1] = (val: 0, state: true)
          eval_pos(x-1, y-1)
      if (y < len(octopus) - 1 and not octopus[y+1][x-1].state): # Left down
        octopus[y+1][x-1] = (val: octopus[y+1][x-1].val + 1, state: false)
        if octopus[y+1][x-1].val > 9:
          octopus[y+1][x-1] = (val: 0, state: true)
          eval_pos(x-1, y+1)

    if(x < len(octopus[0]) - 1):
      if not octopus[y][x+1].state: # Right
        octopus[y][x+1] = (val: octopus[y][x+1].val + 1, state: false)
        if octopus[y][x+1].val > 9:
          octopus[y][x+1] = (val: 0, state: true)
          eval_pos(x+1, y)
      if (y > 0 and not octopus[y-1][x+1].state): # Right up
        octopus[y-1][x+1] = (val: octopus[y-1][x+1].val + 1, state: false)
        if octopus[y-1][x+1].val > 9:
          octopus[y-1][x+1] = (val: 0, state: true)
          eval_pos(x+1, y-1)
      if (y < len(octopus) - 1 and not octopus[y+1][x+1].state): # Right down
        octopus[y+1][x+1] = (val: octopus[y+1][x+1].val + 1, state: false)
        if octopus[y+1][x+1].val > 9:
          octopus[y+1][x+1] = (val: 0, state: true)
          eval_pos(x+1, y+1)

    if(y > 0): # Up
      if not octopus[y-1][x].state:
        octopus[y-1][x] = (val: octopus[y-1][x].val + 1, state: false)
        if octopus[y-1][x].val > 9:
          octopus[y-1][x] = (val: 0, state: true)
          eval_pos(x, y-1)

    if (y < len(octopus) - 1): # Down
      if not octopus[y+1][x].state:
        octopus[y+1][x] = (val: octopus[y+1][x].val + 1, state: false)
        if octopus[y+1][x].val > 9:
          octopus[y+1][x] = (val: 0, state: true)
          eval_pos(x, y+1)

  for i in 0..1000:
    # Run
    for y, oct in enumerate(octopus):
      for x, o in enumerate(oct):
        if not octopus[y][x].state:
          octopus[y][x] = (val: o.val + 1, state: o.state)
        if octopus[y][x].val > 9 and not octopus[y][x].state:
          octopus[y][x] = (val: 0, state: true)
          eval_pos(x, y)

    ## Debug
    #for values in octopus:
    #  var tmp = ""
    #  for val in values:
    #    tmp = tmp & $val.val
    #  echo tmp
    #echo " "

    var cnt = 0
    for y, oct in enumerate(octopus):
      for x, o in enumerate(oct):
        if octopus[y][x].val == 0:
          inc(cnt)
        if octopus[y][x].state:
          octopus[y][x] = (val: 0, state: false)
        else:
          octopus[y][x] = (val: octopus[y][x].val, state: false)
    if cnt == (octopus[0].len * octopus.len):
      echo i + 1 # Pt 2 answer (with sufficiently large i)
      break

  result = res # Pt 1 answer

echo solve_one_and_two()
