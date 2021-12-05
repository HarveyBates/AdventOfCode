import std/strutils
import std/enumerate

let file = readFile("input.txt").strip()
let rows = file.splitLines()

# x1, y1 -> x2, y2

proc solve_one(): int = 
  # Horribly inefficient solution ~ 20 sec to run
  # Formulate tuple of coordinates 
  var res = newSeq[tuple[x: int, y: int]]()
  for row in rows:
    let coords = row.split(" ")
    let x1 = coords[0].split(",")[0].parseInt
    let y1 = coords[0].split(",")[1].parseInt
    let x2 = coords[2].split(",")[0].parseInt
    let y2 = coords[2].split(",")[1].parseInt
    if (x1 < x2 and y1 == y2):
      for x in x1 .. x2:
        var coord: tuple[x: int, y: int] = (x, y1)
        res.add(coord)
    elif (x1 > x2 and y1 == y2):
      for x in x2 .. x1:
        var coord: tuple[x: int, y: int] = (x, y1)
        res.add(coord)
    elif (y1 < y2 and x1 == x2):
      for y in y1 .. y2: 
        var coord: tuple[x: int, y: int] = (x1, y)
        res.add(coord)
    elif (y1 > y2 and x1 == x2):
      for y in y2 .. y1: 
        var coord: tuple[x: int, y: int] = (x1, y)
        res.add(coord)

  # Determine 2 or more matches
  var overlap = 0
  var matches = newSeq[tuple[x: int, y: int]]()
  for i, _ in enumerate(res):
    var match = 0
    if find(matches, res[i]) == -1:
      for val in res[i..^1]:
        if (res[i] == val):
          inc(match)
        if match == 2:
          var coord: tuple[x: int, y: int] = res[i]
          matches.add(coord)
          break
    if (match == 2):
      inc(overlap)

  return overlap


proc solve_two(): int = 
  var res = newSeq[tuple[x: int, y: int]]()
  for row in rows:
    let coords = row.split(" ")
    let x1 = coords[0].split(",")[0].parseInt
    let y1 = coords[0].split(",")[1].parseInt
    let x2 = coords[2].split(",")[0].parseInt
    let y2 = coords[2].split(",")[1].parseInt

    let xDiff = x1 - x2
    let yDiff = y1 - y2

    # Positive slope and hline
    if (xDiff > 0):
      var yPos = y1
      var xPos = x1
      for x in x2..x1:
        var coord: tuple[x: int, y:int] = (xPos, yPos)
        res.add(coord)
        if(yDiff < 0 and yPos != y2):
          inc(yPos)
        elif(yPos != y2):
          dec(yPos)
        dec(xPos)
    # Negative slope and hline
    elif (xDiff < 0):
      var yPos = y1
      for x in x1..x2:
        var coord: tuple[x: int, y: int] = (x, yPos)
        res.add(coord)
        if(yDiff < 0 and yPos != y2):
          inc(yPos)
        elif(yPos != y2):
          dec(yPos)
    # Vertical straight line
    else:
      if(yDiff > 0):
        for y in y2..y1:
          var coord: tuple[x: int, y: int] = (x1, y)
          res.add(coord)
      else:
        for y in y1..y2:
          var coord: tuple[x: int, y: int] = (x1, y)
          res.add(coord)

  echo "Done First"

  # Evaluate
  var overlap = 0
  var matches = newSeq[tuple[x: int, y: int]]()
  for i, _ in enumerate(res):
    var match = 0
    if find(matches, res[i]) == -1:
      for val in res[i..^1]:
        if (res[i] == val):
          inc(match)
        if match == 2:
          var coord: tuple[x: int, y: int] = res[i]
          matches.add(coord)
          break
    if (match == 2):
      inc(overlap)

  return overlap

#echo solve_one()
echo solve_two()
