
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

    pub fn part_one(input: &Vec<String>, input2: &Vec<String>){

        const height: usize = 4;
        const width: usize = 3;
        let mut crates: [[char; width]; height] = [[' '; width]; height];

        for (y, row) in input.iter().enumerate() {
            let columns = row.split_whitespace();
            for (x, column) in columns.enumerate() {
                if !column.contains("X") {
                    crates[x][y] = column.chars().nth(1).unwrap();
                } 
            }
        }

        let mut movements: Vec<i32> = Vec::new();
        let mut from_positions: Vec<i32> = Vec::new();
        let mut to_positions: Vec<i32> = Vec::new();

        for line in input2.iter(){
            let mut parts = line.split_whitespace();
            for (i, part) in parts.enumerate(){
                if i == 1 {
                    movements.push(part.parse::<i32>().expect("Parse error"));
                }
                else if i == 3 {
                    from_positions.push(part.parse::<i32>().expect("Parse error"));
                }
                else if i == 5 {
                    to_positions.push(part.parse::<i32>().expect("Parse error"));
                }
            }
        }

        for (i, mov) in movements.iter().enumerate() {
            let from = from_positions[i] as usize;
            let to = to_positions[i] as usize;
            // Move
            for m in 0..*mov {
                // From
                let mut from_top = 0;
                for y in crates[from-1] {
                    if y != ' ' {
                        // To
                        let mut to_top = 0;
                        let mut exit = false;
                        for y2 in crates[to-1] {
                            if y2 != ' ' {
                                crates[to-1][to_top-1] = y;
                                crates[from-1][from_top] = ' ';
                                exit = true;
                                break;
                            }
                            to_top += 1;
                        }
                        if exit { break; }
                    }
                    from_top += 1;
                }
            }
        }
        println!("");
        
        // Visualise
        for y in 0..height {
            for x in 0..width {
                print!("[{}] ", crates[x][y]);
            }
            println!("");
        }

    }

}

fn main() {
    let input = input::get("input.txt").expect("Unable to open input file");
    let input_movements = input::get("input2.txt").expect("Unable to open input file");
    solve::part_one(&input, &input_movements);


}
