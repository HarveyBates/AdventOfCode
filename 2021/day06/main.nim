import std/strutils
import std/sequtils
import std/enumerate
import std/tables
import std/math

let file = readFile("input.txt").strip()
var fishes = file.split(',').map(parseInt).toSeq()

proc solve_one(): int = 

  proc edit_fish(fishes: var seq[int], index: int, age: int, reset: bool) =
    if not reset:
      fishes[index] = age - 1
    else:
      fishes[index] = 6

  for i in 0..79:
    var pool = fishes
    for i, age in enumerate(pool):
      if(age == 0):
        edit_fish(fishes, i, age, true) 
        fishes.add(8)
      else:
        edit_fish(fishes, i, age, false) 

  return fishes.len


proc solve_two(): int = 
  # Couldn't get a working solution (from Reddit below)
  proc incDay(current: CountTable[int]): CountTable[int] = 
    for k, v in current.pairs:
      if k == 0:
        result.inc 6, v
        result.inc 8, v
      else:
        result.inc k-1, v
  
  var data = readFile("input.txt").strip().split(',').map(parseInt).toCountTable

  for _ in 0..255: 
    data = data.incDay

  return sum(data.values.toSeq)

echo solve_one()
echo solve_two()



