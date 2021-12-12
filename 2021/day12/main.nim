import std/[strutils, sequtils, enumerate]

var rows = readFile("input.txt").strip().splitLines()

var routes = newSeq[tuple[c1: tuple[cave: string, state: bool], c2: tuple[cave: string, state: bool]]]() # Cave 1, Cave 2
for route in rows:
  var splitRoute = route.split('-')
  var s = $splitRoute[0]
  var e = $splitRoute[1]
  routes.add((c1: (cave: s, state: false), c2: (cave: e, state: false)))


proc find_connection(r: tuple[c1: tuple[cave: string, state: bool], c2: tuple[cave: string, state: bool]], currentNode: int) =
  echo "Finding connection"
  echo r

  var isSmallC1 = false
  for c in r.c1.cave:
    if c.isLowerAscii:
      isSmallC1 = true
      break
  if isSmallC1:
    routes[currentNode].c1.state = true

  var isSmallC2 = false
  for c in r.c2.cave:
    if c.isLowerAscii:
      isSmallC2 = true
      break
  if isSmallC2:
    routes[currentNode].c2.state = true

  for i, route in enumerate(routes):
    if i != currentNode:
      if r.c1.cave == route.c2.cave and not route.c1.state:
        echo "c1"
        find_connection(route, i)
      if r.c2.cave == route.c1.cave and not route.c2.state:
        echo "c2"
        find_connection(route, i)
      if r.c1.cave == "end":
        echo "stop1"
        return
      if r.c2.cave == "end":
        echo "stop2"
        return 


proc solve_one(): int = 
  for i, route in enumerate(routes):
    if (route.c1.cave == "start"):
      find_connection(route, i)


echo solve_one()


