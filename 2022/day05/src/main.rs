
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

        const BORDER_BUFFER: usize = 42;
        const HEIGHT: usize = 9 + BORDER_BUFFER;
        const WIDTH: usize = 9 + BORDER_BUFFER;
        let mut crates: [[char; WIDTH]; HEIGHT] = [[' '; WIDTH]; HEIGHT];

        for (y, row) in input.iter().enumerate() {
            let columns = row.split_whitespace();
            for (x, column) in columns.enumerate() {
                let letter = column.chars().nth(1).unwrap();
                if letter != 'X'{
                    crates[x][y + BORDER_BUFFER] = letter;
                } else {
                    crates[x][y + BORDER_BUFFER] = ' ';
                }
            }
        }

        // Visualise
        for y in BORDER_BUFFER-2..HEIGHT {
            for x in 0..WIDTH - BORDER_BUFFER {
                print!("[{}] ", crates[x][y]);
            }
            println!();
        }

        let mut movements: Vec<i32> = Vec::new();
        let mut from_positions: Vec<i32> = Vec::new();
        let mut to_positions: Vec<i32> = Vec::new();

        for line in input2.iter(){
            let parts = line.split_whitespace();
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
            let from = (from_positions[i] - 1) as usize;
            let to = (to_positions[i] - 1) as usize;
            println!("move {mov} from {from} to {to}");
            // Move
            for _m in 0..*mov {
                // From
                let mut from_top = 0;
                for y in crates[from] {
                    if y != ' ' {
                        // To
                        let mut to_top = 0;
                        let mut exit = false;
                        for y2 in crates[to] {
                            if y2 != ' ' {
                                crates[to][to_top-1] = y;
                                crates[from][from_top] = ' ';
                                exit = true;
                                break;
                            }
                            else if to_top == (HEIGHT - 1) {
                                crates[to][to_top] = y;
                                crates[from][from_top] = ' ';
                                exit = true;
                                break;
                            }
                            to_top += 1;
                        }
                        if exit {
                            break;
                        }
                    }
                    from_top += 1;
                }
            }

            println!();

            // Visualise
            for y in BORDER_BUFFER-2..HEIGHT {
                for x in 0..WIDTH - BORDER_BUFFER {
                    print!("[{}] ", crates[x][y]);
                }
                println!();
            }
        }
    }

}

fn main() {
    let input = input::get("input.txt").expect("Unable to open input file");
    let input_movements = input::get("input2.txt").expect("Unable to open input file");
    solve::part_one(&input, &input_movements);


}
