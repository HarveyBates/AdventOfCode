import std/strutils
from std/sequtils import map
import std/enumerate

let numbersFile = readFile("input_numbers.txt").strip()
let numbers = numbersFile.split(',').map(parseInt)

let gamesFile = readFile("input_games.txt").strip()
let rawGames = gamesFile.splitLines()


var games = newSeq[seq[seq[tuple[status: bool, num: int]]]]()
var game = newSeq[seq[tuple[status: bool, num: int]]]()

for i, row in enumerate(rawGames):
  if row != "":
    var gm = row.splitWhitespace().map(parseInt)
    var s = newSeq[tuple[status: bool, num: int]]()
    for x in gm:
      var gameStatus: tuple[status: bool, num: int]
      gameStatus = (false, x)
      s.add(gameStatus)

    game.add([s])
  else:
    games.add([game])
    game = newSeq[seq[tuple[status: bool, num: int]]]()
games.add([game])


for x in games:
  for y in x:
    echo y
  echo " "


