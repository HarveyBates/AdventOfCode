use std::fs;

fn read_input(filename: String) -> Vec<i32> {
    let contents = match fs::read_to_string(&filename) {
        Ok(c) => c,
        Err(e) => panic!("Unable to open {}: {}", &filename, e),
    };

    contents
        .lines()
        .map(|line| match line.parse::<i32>() {
            Ok(r) => r,
            Err(e) => panic!("Error parsing line: {}", e),
        })
        .collect()
}

fn solve_one(input: &Vec<i32>) -> usize {
    // (199, 200), (200, 208)
    let pairs = input.iter().zip(input.iter().skip(1));
    pairs.clone().filter(|(x, y)| x < y).count()
}

fn solve_two(input: &Vec<i32>) {
    let triplets = input
        .iter()
        .zip(input.iter().skip(1))
        .zip(input.iter().skip(2))
}

fn main() {
    let input = &read_input(String::from("input.txt"));
    println!("Problem 1: {}", solve_one(&input));
}
