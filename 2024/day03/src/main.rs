mod input;
use regex::Regex;

fn part_one(puzzle: &Vec<String>) {
    let mut sum: i32 = 0;

    for line in puzzle {
        sum += Regex::new(r"mul\(\d+\,\d+\)")
            .unwrap()
            .find_iter(line)
            .map(|mul| Some(mul.as_str()))
            .map(|mul| {
                mul.expect("None")
                    .trim_start_matches("mul(")
                    .trim_end_matches(")")
                    .split(',')
                    .map(|s| s.chars().filter(|c| c.is_ascii_digit()).collect::<String>())
                    .filter_map(|v| v.parse::<i32>().ok())
                    .product::<i32>()
            })
            .collect::<Vec<i32>>()
            .iter()
            .sum::<i32>();
    }

    println!("Part 1: {sum}");
}

fn main() {
    let puzzle = input::get_lines("input.txt");
    part_one(&puzzle);
}
