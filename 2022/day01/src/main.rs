
mod input {

    use std::fs::File;
    use std::io::BufReader;
    use std::io::BufRead;
    use std::error::Error;

    pub fn get(filename: &str) ->Result<Vec<String>, Box<dyn Error>> { 
        let mut lines: Vec<String> = Vec::new();

        let path = File::open(filename).unwrap_or_else(|_| panic!("File: {}, not found. Exiting.", filename));
        let file = BufReader::new(path);

        for line in file.lines(){
            match line {
                Ok(line) => lines.push(line),
                Err(e) => panic!("Line parsing error: {e}"),
            }
        }

        Ok(lines)
    }

}

mod solve {

    pub fn part_one(input: &Vec<String>){
        let mut total_calories: i32 = 0;
        let mut max = 0;
        for line in input.iter() {
            match line.trim().parse::<i32>() {
                Ok(val) => {
                    total_calories += val;
                },
                Err(_) => {
                    if max < total_calories {
                        max = total_calories;
                    }
                    total_calories = 0;
                    continue;
                },
            };
        } 

        println!("Part One: {max}");

    }

    pub fn part_two(input: &Vec<String>){

        let mut totals: Vec<i32> = Vec::new();

        let mut total_calories: i32 = 0;
        for line in input.iter() {
            match line.trim().parse::<i32>() {
                Ok(val) => {
                    total_calories += val;
                },
                Err(_) => {
                    totals.push(total_calories);
                    total_calories = 0;
                    continue;
                },
            };
        } 

        totals.sort();
        totals.reverse();

        let mut sum = 0;
        let depth = 3;
        for (i, calories) in totals.iter().enumerate() {
            if i >= depth { break };
            sum += calories;
        }

        println!("Part Two: {sum}");
    }

}

fn main() {
    let input = input::get("input.txt").unwrap();
    solve::part_one(&input);
    solve::part_two(&input);
}
