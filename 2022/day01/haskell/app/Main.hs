import Data.List (sort)
import Data.List.Split
import Data.Maybe (maybe)

-- readInput :: String -> IO [Int]
-- readInput filename = do
--   contents <- readFile filename
--   return . map read . words $ contents

-- Read word and convert to int if parsed correctly
-- (should be no remainder, hence "")
safeRead :: String -> Maybe Int
safeRead s = case reads s of
  [(val, "")] -> Just val
  _ -> Nothing

-- Sum each group rejecting parse errors
processGroup :: String -> Maybe Int
processGroup group = sum <$> traverse safeRead (words group)

-- Sort in reverse then take the top 3 elements
getTopThree :: Maybe [Int] -> Maybe [Int]
getTopThree = fmap (take 3 . reverse)

main :: IO ()
main = do
  -- Open file
  content <- readFile "input.txt"

  -- Split where there is an empty line
  let groups = splitOn "\n\n" content

  -- Calculate the sums of each group (mapping them with map Maybe (mapM))
  let sums = mapM processGroup groups

  -- Part 1:
  case (Just . maximum) =<< sums of
    Just maxVal -> print maxVal
    Nothing -> putStrLn "Error"

  -- Part 2:
  case sum <$> getTopThree (fmap sort sums) of
    Just maxVal -> print maxVal
    Nothing -> putStrLn "Error"
