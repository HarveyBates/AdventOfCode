
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
        let mut contained = 0;

        for line in input.iter(){
            let sections = line.split(',');
            let mut first_lower = 0;
            let mut first_upper = 0;
            let mut second_lower = 0;
            let mut second_upper = 0;
            let mut first = true;
            for section in sections {
                let pairs = section.split('-');
                for (i, value) in pairs.enumerate() {
                    if i % 2 == 0 {
                        if first {
                            first_lower = value.trim().parse::<i32>().expect("Parse error");
                        } else {
                            second_lower = value.trim().parse::<i32>().expect("Parse error");
                        }
                    } else {
                        if first {
                            first_upper = value.trim().parse::<i32>().expect("Parse error");
                        } else {
                            second_upper = value.trim().parse::<i32>().expect("Parse error");
                        }
                    }
                }
                first = false;
            }

            if first_lower >= second_lower && first_upper <= second_upper {
                contained += 1;
            } 
            else if second_lower >= first_lower && second_upper <= first_upper {
                contained += 1;
            }
        }

        println!("Part One: {contained}");
    }

    
    pub fn part_two(input: &Vec<String>){
        let mut contained = 0;

        for line in input.iter(){
            let sections = line.split(',');
            let mut first_lower = 0;
            let mut first_upper = 0;
            let mut second_lower = 0;
            let mut second_upper = 0;
            let mut first = true;
            for section in sections {
                let pairs = section.split('-');
                for (i, value) in pairs.enumerate() {
                    if i % 2 == 0 {
                        if first {
                            first_lower = value.trim().parse::<i32>().expect("Parse error");
                        } else {
                            second_lower = value.trim().parse::<i32>().expect("Parse error");
                        }
                    } else {
                        if first {
                            first_upper = value.trim().parse::<i32>().expect("Parse error");
                        } else {
                            second_upper = value.trim().parse::<i32>().expect("Parse error");
                        }
                    }
                }
                first = false;
            }

            if first_lower >= second_lower && first_lower <= second_upper{
                contained += 1;
            }
            else if second_lower >= first_lower && second_lower <= first_upper {
                contained += 1;
            }
        }

        println!("Part Two: {contained}");
    }
}

fn main() {
    let input = input::get("input.txt").expect("Error loading input");
    solve::part_one(&input);
    solve::part_two(&input);
}
