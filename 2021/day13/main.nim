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


proc fold_up(fold: int, input: seq[string]): seq[string] =
  var output = input
  var rStart = len(output)
  for i, row in enumerate(output):
    if i >= fold:
      var ii = i - fold 
      for x, c in enumerate(output[rStart-1]):
        if output[ii][x] != '#':
          output[ii][x] = c
      dec(rStart)
    else:
      for x, c in enumerate(row):
        output[i][x] = c

  output.delete(fold..len(output)-1)

  return output 


proc fold_left(fold: int, input: seq[string]): seq[string] = 
  var output = input
  for i, row in enumerate(output):
    var ii = len(output[0]) - 1
    var xx = 0
    for x, c in row:
      if x > (fold-1):
        if output[i][ii] == '#':
          output[i][xx] = '#'
        dec(ii)
        inc(xx)
      else:
        output[i][x] = c

  for i, row in enumerate(output):
    output[i].delete(int((len(output[i])-1)/2)..len(output[i])-1)

  return output


proc solve_one(): int = 
  var input = newSeq[string]()
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
    input.add(d)

  input = fold_left(655, input)

  for i, o in enumerate(input):
    for c in o:
      if c == '#':
        inc(result)

  input = fold_up(447, input)
  input = fold_left(327, input)
  input = fold_up(223, input)
  input = fold_left(163, input)
  input = fold_up(111, input)
  input = fold_left(81, input)
  input = fold_up(55, input)
  input = fold_left(40, input)
  input = fold_up(27, input)
  input = fold_up(13, input)
  input = fold_up(6, input)

  for i, o in enumerate(input):
    echo i, " ", o


echo solve_one()

