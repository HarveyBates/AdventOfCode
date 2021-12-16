import std/strutils
from std/sequtils import map
import std/enumerate

let numbersFile = readFile("input_numbers.txt").strip()
let numbers = numbersFile.split(',').map(parseInt)

let gamesFile = readFile("input_games.txt").strip()
let rawGames = gamesFile.splitLines()


proc solve_one(): int =  
  var games = newSeq[seq[seq[tuple[status: bool, num: int]]]]()
  var game = newSeq[seq[tuple[status: bool, num: int]]]()

  # Formulate sequence of tuples (bool, int)
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

  # Edit value to mark checked off number
  proc edit_game(games: var seq[seq[seq[tuple[status: bool, num: int]]]],
                  gameIdx: int, rowIdx: int, index: int, number: int) = 
    var gameStatus: tuple[status: bool, num: int]
    gameStatus = (true, number)
    for i, item in enumerate(games[gameIdx][rowIdx]):
      if (i == index):
        games[gameIdx][rowIdx][index] = gameStatus

  proc winner(games: var seq[seq[seq[tuple[status: bool, num: int]]]],
                  gameIdx: int, lastNum: int): int = 
    var sumFalse = 0
    for row in games[gameIdx]:
      for item in row:
        if not item.status:
          sumFalse = sumFalse + item.num
    return lastNum * sumFalse


  # Assess each item to see if they match the number
  for val in numbers:
    # Access the games
    for i, game in enumerate(games):
      # Access rows
      for x, row in enumerate(game):
        # Access the items
        for y, item in enumerate(row):
          if (val == item.num and not item.status):
            edit_game(games, i, x, y, val)

    # Evaluate game
    for i, game in enumerate(games):
      for row in game:
        var rowMatch = 0
        for item in row:
          if (item.status):
            inc(rowMatch)
        if (rowMatch == 5):
          echo "Row Bingo"
          var res = winner(games, i, val)
          return res
      for y, row in enumerate(game):
        var colMatch = 0
        for column in game:
          if (column[y].status):
            inc(colMatch)
        if (colMatch == 5):
          echo "Column Bingo"
          var res = winner(games, i, val)
          return res
  return 0


proc solve_two(): int =  
  var games = newSeq[seq[seq[tuple[status: bool, num: int]]]]()
  var game = newSeq[seq[tuple[status: bool, num: int]]]()

  # Formulate sequence of tuples (bool, int)
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

  # Edit value to mark checked off number
  proc edit_game(games: var seq[seq[seq[tuple[status: bool, num: int]]]],
                  gameIdx: int, rowIdx: int, index: int, number: int) = 
    var gameStatus: tuple[status: bool, num: int]
    gameStatus = (true, number)
    for i, item in enumerate(games[gameIdx][rowIdx]):
      if (i == index):
        games[gameIdx][rowIdx][index] = gameStatus

  proc winner(games: var seq[seq[seq[tuple[status: bool, num: int]]]],
                  gameIdx: int, lastNum: int): int = 
    var sumFalse = 0
    for row in games[gameIdx]:
      for item in row:
        if not item.status:
          sumFalse = sumFalse + item.num
    return lastNum * sumFalse


  var winners = newSeq[int]()
  # Assess each item to see if they match the number
  for val in numbers:
    # Access the games
    for i, game in enumerate(games):
      # Access rows
      for x, row in enumerate(game):
        # Access the items
        for y, item in enumerate(row):
          if (val == item.num and not item.status):
            edit_game(games, i, x, y, val)

    # Evaluate game
    for i, game in enumerate(games):
      for row in game:
        var rowMatch = 0
        for item in row:
          if (item.status):
            inc(rowMatch)
        if (rowMatch == 5):
          if find(winners, i) == -1:
            winners.add(i)
      for y, row in enumerate(game):
        var colMatch = 0
        for column in game:
          if (column[y].status):
            inc(colMatch)
        if (colMatch == 5):
          if find(winners, i) == -1:
            winners.add(i)
    if winners.len == games.len:
      var res = winner(games, winners[^1], val)
      echo res, " ", val
      return res
  return 0


echo solve_one()
echo solve_two()

