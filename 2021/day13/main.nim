import std/[sequtils, strutils, enumerate]

var rows = readFile("input_coords.txt").strip().splitLines()

var coords = newSeq[tuple[x: int, y: int]]()

var xExtent = 0
var yExtent = 0
for coord in rows:
  var s = coord.split(',')
  var X = s[0].parseInt
  var Y = s[1].parseInt
  coords.add((x: X, y: Y))
  if Y > yExtent:
    yExtent = Y
  if X > xExtent:
    xExtent = X

proc solve_one(): int = 
  var fold = 7 # Y
  var initial = newSeq[string]()
  for y in 0..yExtent:
    var d = ""
    for x in 0..xExtent:
      var match = false
      for c in coords:
        if c.x == x and c.y == y:
          match = true
      if match:
        d = d & '#'
      else:
        d = d & '.'
    initial.add(d)

  var output: array[8, array[11, char]]

  # Fold up
  var rStart = len(initial)
  for i, row in enumerate(initial):
    if i >= 7:
      var ii = i - 7
      for x, c in enumerate(initial[rStart-1]):
        if output[ii][x] != '#':
          output[ii][x] = c
      dec(rStart)
    else:
      for x, c in enumerate(row):
        output[i][x] = c


  for i, o in enumerate(output):
    for c in o:
      if c == '#':
        inc(result)
    echo i, " ", o

  var xOutput: array[8, array[5, char]]

  # Fold left
  for i, row in enumerate(output):
    var ii = 0
    for x, c in row:
      if x >= 5 and ii < 5:
        if xOutput[i][ii] != '#':
          xOutput[i][ii] = c
        else:
          xOutput[i][ii] = 'P'
        inc(ii)
      elif x < 4:
        xOutput[i][x] = c

  for i, o in enumerate(xOutput):
    echo i, " ", o


echo solve_one()
  


