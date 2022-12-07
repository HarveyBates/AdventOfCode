
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

    use std::collections::VecDeque;

    pub fn part_one(input: &Vec<String>, distinct_characters: usize){


        let mut input_buf: VecDeque<char> = VecDeque::new();

        for line in input.iter(){
            for (i, c) in line.chars().enumerate() {
                input_buf.push_back(c);

                if i < (distinct_characters - 1) {
                    continue;
                }

                let mut identical = false;
                for (x, c_1) in input_buf.iter().enumerate() {
                    for (x1, c_n) in input_buf.iter().enumerate() {
                        if c_1 == c_n && x != x1 {
                            identical = true;
                        }
                    }
                }

                if !identical{
                    println!("Solution: {}", i+1);
                    break;
                }

                input_buf.pop_front();

            }
        }
    }
}


fn main() {
    let input = input::get("input.txt").expect("Error opening input file.");
    solve::part_one(&input, 4); // Part one
    solve::part_one(&input, 14); // Part two
}
