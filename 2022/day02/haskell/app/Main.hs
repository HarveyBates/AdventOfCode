import Data.List.Split

-- Get score for a corresponding character
getScore :: Char -> Int
-- My scores
getScore 'X' = 1 -- Rock
getScore 'Y' = 2 -- Paper
getScore 'Z' = 3 -- Scissors
-- Thier scores
getScore 'A' = 1 -- Rock
getScore 'B' = 2 -- Paper
getScore 'C' = 3 -- Scissors
getScore _ = 0

---------- Part 1 ----------

-- Winning possibilities (check if an element of)
winner :: (Char, Char) -> Bool
winner input = input `elem` [('A', 'Y'), ('B', 'Z'), ('C', 'X')]

-- Run a round with opponnent and my input
partOne :: Char -> Char -> Int
partOne opponent you
  | winner (opponent, you) = 6 + getScore you -- Win
  | getScore opponent == getScore you = 3 + getScore you -- Draw
  | otherwise = getScore you -- Lose

-- Execute part one
runPartOne :: [Char] -> Int
runPartOne [opponent, _, you] = partOne opponent you

---------- Part 2 ----------

-- Get winning move from opponents move
getWinner :: Char -> Char
getWinner 'A' = 'Y'
getWinner 'B' = 'Z'
getWinner 'C' = 'X'

-- Get losing move from opponents move
getLoser :: Char -> Char
getLoser 'A' = 'Z'
getLoser 'B' = 'X'
getLoser 'C' = 'Y'

-- Evauate a round for part two
partTwo :: Char -> Char -> Int
partTwo opponent you
  | you == 'Z' = 6 + getScore (getWinner opponent) -- Win
  | you == 'Y' = 3 + getScore opponent -- Draw
  | you == 'X' = 0 + getScore (getLoser opponent) -- Lose

-- Execute part two
runPartTwo :: [Char] -> Int
runPartTwo [opponent, _, you] = partTwo opponent you

main :: IO ()
main = do
  content <- readFile "input.txt"
  let lines = filter (not . null) $ splitOn "\n" content

  -- Part 1:
  print $ sum $ map runPartOne lines

  -- Part 2:
  print $ sum $ map runPartTwo lines
