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

    pub fn part_one(input: &Vec<String>) {
        let mut sum = 0;
        for line in input.iter(){

            let linelength = line.len() / 2;
            let mut first_comp: Vec<char> = Vec::new();
            let mut sec_comp: Vec<char> = Vec::new();
            for (i, c) in line.chars().enumerate() {
                if i < linelength {
                    first_comp.push(c);
                    continue;
                } else {
                    sec_comp.push(c);
                } 
            }
            
            for c1 in first_comp.iter() {
                let mut found = false;
                for c2 in sec_comp.iter() {
                    if c1 == c2 {
                        if c1.is_lowercase() {
                            sum += (*c1 as i8 - 96) as i32;
                        } else {
                            sum += (*c1 as i8 - 38) as i32;
                        }
                        found = true;
                        break;
                    }
                }
                if found { break; }
            }
        }

        println!("Part One: {sum}");
    }


    pub fn part_two(input: &Vec<String>) {

        let mut sum = 0;
        for l in (0..input.len()).step_by(3) {
            let first_line = &input[l + 0];
            let second_line = &input[l + 1];
            let third_line= &input[l + 2];
            for c1 in first_line.chars() {
                let mut found = false;
                for c2 in second_line.chars() {
                    for c3 in third_line.chars() {
                        if c1 == c2 && c2 == c3 {
                            if c1.is_lowercase() {
                                sum += (c1 as i8 - 96) as i32;
                            } else {
                                sum += (c1 as i8 - 38) as i32;
                            }
                            found = true;
                            break;
                        }
                    }
                    if found { break; }
                }
                if found { break; }
            }
        } 

        println!("Part Two: {sum}");
    }

}



fn main() {
    let input = input::get("input.txt").expect("Unable to open problem file.");
    solve::part_one(&input);
    solve::part_two(&input);
}

