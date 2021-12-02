import std/strutils
#from std/sequtils import map
#import std/math

let file = readFile("input.txt").strip()
var rows = file.splitLines()

proc solve_one(): int = 
  var pos = 0
  var depth = 0
  for row in rows:
    let item = row.split(" ")
    let command = item[0]
    let unit = item[1].parseInt
    if(command == "forward"):
      pos = pos + unit
    elif (command == "down"):
      depth = depth + unit
    elif (command == "up"):
      depth = depth - unit
  return pos * depth


proc solve_two(): int = 
  var pos = 0
  var depth = 0
  var aim = 0
  for row in rows:
    let item = row.split(" ")
    let command = item[0]
    let unit = item[1].parseInt
    if(command == "forward"):
      pos = pos + unit
      depth = depth + aim * unit
    elif (command == "down"):
      aim = aim + unit
    elif (command == "up"):
      aim = aim - unit
  return pos * depth 


echo solve_one()
echo solve_two()
