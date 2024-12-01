
mod input {
    use std::fs::File;
    use std::io::BufReader;
    use std::io::BufRead;
    use std::error::Error;

    pub fn get(filename: &str) -> Result<Vec<String>, Box<dyn Error>> {

        let mut lines: Vec<String> = Vec::new();

        let path = File::open(filename).unwrap_or_else(|_| panic!("File {filename}, not found."));
        let file = BufReader::new(path);

        for line in file.lines() {
            match line {
                Ok(line) => lines.push(line),
                Err(error) => panic!("Line parse error: {error}")
            }
        }

        Ok(lines)
    }

}

mod solve {
    use std::iter::Peekable;
    use std::str::Chars;
    
    fn group_repeats(input: &String) -> Vec<String> {
        let mut groups = Vec::new();
        let mut chars: Peekable<Chars> = input.chars().peekable();

        while let Some(current_char) = chars.next() {
            if !current_char.is_digit(10) {
                continue;
            }

            let mut group = current_char.to_string();

            while let Some(&next_char) = chars.peek() {
                if current_char != next_char {
                    break;
                }
                group.push(chars.next().unwrap());
            }

            groups.push(group);
        }

        return groups

    }

    pub fn part_one(input: &Vec<String>) {
        let mut input_copy: Vec<String> = input.clone();
        println!("{:?}", input_copy);

        for _ in 0..1 {
            let groups: Vec<String> = group_repeats(&input_copy[0]);
            println!("{:?}", groups);

            input_copy.clear();
            for group in groups {
                input_copy.push(group.len().to_string() + &group.chars().next().unwrap().to_string())
            }
            println!("{:?}", input_copy.join(""))


        }
    }
}



fn main() {
    let input = input::get("data/input.txt").unwrap();
    solve::part_one(&input);
}
