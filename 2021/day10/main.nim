import std/[sequtils, strutils, algorithm]

var chunks = readFile("input.txt").strip().splitLines()

var opening = @['{', '[', '(', '<']
var closing = @['}', ']', ')', '>']
var points = @[1197, 57, 3, 25137] # Pt 1
var altPoints = @[3, 2, 1, 4] # Pt 2

proc solve_one(): int = 
  for chunk in chunks:
    var pos = find(opening, chunk[0])
    var open = newSeq[char]()
    var close = newSeq[char]()
    for bracket in chunk:
      pos = find(opening, bracket)
      if pos != -1: # Check if bracket is opening
        open.add(bracket)
        close.add(closing[pos])
      else:
        if bracket == close[^1]:
          open.delete(len(open))
          close.delete(len(close))
        else:
          pos = find(closing, bracket)
          result = result + points[pos]
          break


proc solve_two(): int = 
  var res = newSeq[int]()
  for chunk in chunks:
    var pos = find(opening, chunk[0])
    var open = newSeq[char]()
    var close = newSeq[char]()
    var error = false
    for bracket in chunk:
      pos = find(opening, bracket)
      if pos != -1: # Check if bracket is opening
        open.add(bracket)
        close.add(closing[pos])
      else:
        if bracket == close[^1]:
          open.delete(len(open))
          close.delete(len(close))
        else:
          pos = find(closing, bracket)
          error = true
    if (len(close) != 0 and not error):
      result = 0
      for i in countdown(len(close)-1, 0):
        pos = find(closing, close[i])
        var score = altPoints[pos]
        result = 5 * result + score
      res.add(result)
  sort(res)
  var mid = int(len(res) / 2)
  result = res[mid]
        

echo solve_one()
echo solve_two()
