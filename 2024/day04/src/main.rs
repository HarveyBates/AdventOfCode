use regex::Regex;
mod input;

fn get_xmas(puzzle: &str) -> usize {
    let mut sum: usize = 0;
    sum += Regex::new(r"(?:XMAS)").unwrap().find_iter(puzzle).count();
    sum += Regex::new(r"(?:SAMX)").unwrap().find_iter(puzzle).count();
    sum
}

fn part_one(puzzle: &[String]) {
    let rows = puzzle.len();
    let cols = puzzle[0].len();

    let mut concat_puzzle: String = puzzle.concat();

    // Get vertical XMAS
    for x in 0..rows {
        let mut vline: String = String::from("");
        for l in puzzle {
            vline.push(l.chars().nth(x).unwrap());
        }
        vline.push(' ');
        concat_puzzle.push_str(&vline.to_owned());
    }

    // Get right diagonal XMAS (starting top left)
    for x in 0..(rows + cols - 1) {
        let mut vline: String = String::from("");
        for (i, row) in puzzle.iter().enumerate().take(rows) {
            let j = (x as isize) - (i as isize);
            if j >= 0 && j < cols as isize {
                vline.push(row.chars().nth(j as usize).unwrap());
            }
        }
        vline.push(' ');
        if vline.len() > 3 {
            concat_puzzle.push_str(&vline.to_owned());
        }
    }

    // Get left diagonal XMAS (starting top right)
    for x in -(cols as isize - 1)..(rows as isize) {
        let mut vline: String = String::from("");
        for (i, row) in puzzle.iter().enumerate().take(rows) {
            let j = (i as isize) - x;
            if j >= 0 && j < cols as isize {
                vline.push(row.chars().nth(j as usize).unwrap());
            }
        }
        vline.push(' ');
        if vline.len() > 3 {
            concat_puzzle.push_str(&vline.to_owned());
        }
    }

    let sum: usize = get_xmas(&concat_puzzle);

    println!("Part one: {sum}");
}

fn main() {
    let mut puzzle: Vec<String> = input::get_lines("input.txt");
    for s in &mut puzzle {
        s.push(' ');
    }
    part_one(&puzzle);
}
