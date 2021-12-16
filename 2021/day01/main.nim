import std/strutils
from std/sequtils import map
import std/enumerate

let file = readFile("input.txt").strip()
let rows = file.splitLines().map(parseInt)


proc solve_one(): int = 
  for i, _ in enumerate(rows[1 .. ^1]):
    if rows[i+1] > rows[i]:
      inc(result)


proc solve_two(): int = 
  var prevSum = rows[0] + rows[1] + rows[2]
  for i, _ in enumerate(rows[1 .. ^2]):
    let sum = rows[i] + rows[i+1] + rows[i+2] 
    if sum > prevSum:
      inc(result)
    prevSum = sum

echo solve_one()
echo solve_two()
