import std/strutils
import std/enumerate
import std/parseutils

let file = readFile("input.txt").strip()
let rows = file.splitLines()


proc solve_one(): int =
  var gammaRate: string
  var epsilonRate: string
  for pos, _ in enumerate(rows[0]):
    var zeroBits: int
    var oneBits: int
    for row in rows:
      case row[pos]:
        of '0':
          inc(zeroBits)
        else:
          inc(oneBits)
    if (zeroBits > oneBits):
      epsilonRate = epsilonRate & $0
      gammaRate = gammaRate & $1
    else:
      epsilonRate = epsilonRate & $1
      gammaRate = gammaRate & $0
  var gRate: int
  var eRate: int
  discard parseBin(gammaRate, gRate)
  discard parseBin(epsilonRate, eRate)

  return gRate * eRate


proc solve_two(): int = 
  var oxyGenerator = 0
  var co2Generator = 0

  var oxyPool = newSeq[string]()
  var co2Pool = newSeq[string]()
  for row in rows:
    oxyPool.add(row)
    co2Pool.add(row)

  for pos, _ in enumerate(rows[0]):
    var zeroBits: int
    var oneBits: int
    for row in oxyPool:
      case row[pos]:
        of '0':
          inc(zeroBits)
        else:
          inc(oneBits)

    var oxyConsider = '1'
    if (zeroBits > oneBits):
      oxyConsider = '0'

    zeroBits = 0
    oneBits = 0
    for row in co2Pool:
      case row[pos]:
        of '0':
          inc(zeroBits)
        else:
          inc(oneBits)

    var oxygen = newSeq[string]()
    var co2 = newSeq[string]()

    var co2Consider = '0'
    if (zeroBits > oneBits):
      co2Consider = '1'
    
    for row in oxyPool:
      if (row[pos] == oxyConsider):
        oxygen.add(row)

    for row in co2Pool:
      if (row[pos] == co2Consider):
        co2.add(row)

    if (oxygen.len == 1):
      discard parseBin(oxygen[0], oxyGenerator)
    elif (co2.len == 1):
      discard parseBin(co2[0], co2Generator)

    oxyPool = oxygen
    co2Pool = co2

  return oxyGenerator * co2Generator


echo solve_one()
echo solve_two()


