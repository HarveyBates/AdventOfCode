import std/strutils
import std/sequtils
import std/algorithm

var positions = readFile("input.txt").strip().split(',').map(parseInt)

positions.sort()
var mid = int(len(positions) / 2)

proc solve_one(): int = 
  var aimValue = positions[mid]
  for pos in positions:
    var newPos = pos
    while (newPos > aimValue):
      dec(newPos)
      inc(result)
    while(newPos < aimValue):
      inc(newPos)
      inc(result)

proc solve_two(): int = 
  var minVal: int
  var initial = true
  for item in min(positions)..max(positions):
    var res = 0
    for pos in positions:
      var newPos = pos
      var steps = 1
      while (newPos > item):
        dec(newPos)
        res = res + steps
        inc(steps)
      while(newPos < item):
        inc(newPos)
        res = res + steps
        inc(steps)
    if initial:
      minVal = res
      initial = false
    else:
      if (minVal > res):
        minVal = res
  return minVal


echo solve_one()
echo solve_two()
