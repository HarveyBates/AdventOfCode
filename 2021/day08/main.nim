import std/[sequtils, strutils, tables]

var signals = readFile("input.txt").strip().split('\n')


proc solve_one(): int = 
  var uniques = @[2, 3, 4, 7]
  for signal in signals:
    var io = signal.split('|')
    var outputs = io[1].strip().split(' ')
    for output in items(outputs):
      for unique in uniques:
        if output.len == unique:
          inc(result)


proc solve_two(): int = 
  var positions = {0: "", 1: "", 2: "", 3: "", 4: "", 5: "", 6: "", 7: "", 8: "", 9: ""}.toOrderedTable
  for signal in signals:
    var io = signal.split('|')
    var inputs = io[0].strip().split(' ')
    var outputs = io[1].strip().split(' ')

    # Initialise
    for input in inputs:
      if input.len == 2: # 1
        positions[1] = input
      elif input.len == 4:
        positions[4] = input
      elif input.len == 3:
        positions[7] = input
      elif input.len == 7:
        positions[8] = input

    # Populate
    var finished = false
    var counter = 0
    while not finished:
      for input in inputs:
        if input.len == 5:
          var cnt = 0
          for c in input:
            for p in positions[7]:
              if c == p:
                inc(cnt)
          if cnt == 3:
            positions[3] = input
        if input.len == 6:
          var cnt = 0
          for c in input:
            for p in positions[4]:
              if c == p:
                inc(cnt)
          if cnt == 4:
            positions[9] = input
          else:
            var nCnt = 0
            for c in input:
              for p in positions[7]:
                if c == p:
                  inc(nCnt)
            if nCnt == 3:
              positions[0] = input
            else:
              positions[6] = input
        if input.len == 5 and positions[3] != "" and positions[6] != "":
          var cnt = 0
          for c in input:
            for p in positions[6]:
              if p == c:
                inc(cnt)
          if cnt == 5:
            positions[5] = input
          elif input != positions[3]: 
            positions[2] = input

      if counter > 3:
        finished = true
      inc(counter)
  
    # Evaluate
    var outVal = ""
    for output in outputs:
      for key, value in positions.pairs:
        var cnt = 0
        for v in value:
          for o in output:
            if v == o:
              inc(cnt)
        if cnt == value.len and cnt == output.len:
          outVal = outVal & $key

    result = result + outVal.parseInt

echo solve_one()
echo solve_two()
