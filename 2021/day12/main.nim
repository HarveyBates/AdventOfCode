import std/[strutils, sequtils, enumerate]

var rows = readFile("input.txt").strip().splitLines()

var routes = newSeq[tuple[c1: tuple[cave: string, state: bool], c2: tuple[cave: string, state: bool]]]() # Cave 1, Cave 2
for route in rows:
  var splitRoute = route.split('-')
  var s = $splitRoute[0]
  var e = $splitRoute[1]
  routes.add((c1: (cave: s, state: false), c2: (cave: e, state: false)))


proc solve_one(): int = 
  for i, route in enumerate(routes):
    if (route.c1.cave == "start"):
      echo route.c1.cave
      find_connection(route, i)


echo solve_one()


