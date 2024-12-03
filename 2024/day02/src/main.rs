mod input;

fn assess_line(line: &[i32], error_idx: &mut usize) -> bool {
    let mut error = false;
    let mut last = line[0];
    let increasing = line[0] < line[1];
    for (i, v) in line[1..].iter().enumerate() {
        if v < &(last - 3) || v > &(last + 3) || v == &last {
            *error_idx = i;
            error = true;
            break;
        }

        if increasing && v < &last {
            *error_idx = i;
            error = true;
            break;
        }

        if !increasing && v > &last {
            *error_idx = i;
            error = true;
            break;
        }

        last = *v;
    }

    !error
}

fn part_one(puzzle: &Vec<Vec<i32>>) {
    let mut safe = 0;
    let mut error_idx = 0;
    for line in puzzle {
        if assess_line(line, &mut error_idx) {
            safe += 1;
        }
    }

    println!("Part one: {safe}");
}

fn part_two(puzzle: &mut [Vec<i32>]) {
    let mut safe = 0;
    for line in puzzle.iter_mut() {
        let mut error_idx = 0;
        if assess_line(line, &mut error_idx) {
            safe += 1;
            continue;
        }

        let mut mod_line = line.clone();
        mod_line.remove(error_idx);
        let mut placeholder = 0;

        if assess_line(&mod_line, &mut placeholder) {
            safe += 1;
            continue;
        }

        let mut mod_line2 = line.clone();
        error_idx = error_idx.saturating_sub(1);
        mod_line2.remove(error_idx);
        let mut placeholder = 0;

        if assess_line(&mod_line2, &mut placeholder) {
            safe += 1;
            continue;
        }
    }

    println!("Part two: {safe}");
}

fn main() {
    let input = input::get_lines("input.txt");
    let mut puzzle: Vec<Vec<i32>> = input
        .iter()
        .map(|v| {
            v.split_whitespace()
                .filter_map(|n| n.parse::<i32>().ok())
                .collect::<Vec<i32>>()
        })
        .collect();

    part_one(&puzzle);
    part_two(&mut puzzle);
}
