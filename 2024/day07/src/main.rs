mod input;

// 0 = '+', 1 = '*'
fn get_possible_combinations(length: usize) -> Vec<Vec<char>> {
    (0..i64::pow(2, length as u32))
        .map(|v| format!("{:0length$b}", v).chars().collect())
        .collect()
}

fn main() {
    let puzzle = input::get_lines("input.txt");

    let mut sum = 0;
    for equation in puzzle {
        let parts: Vec<_> = equation.split(':').collect::<Vec<_>>();
        let target = parts[0].parse::<u64>().unwrap();
        let components: Vec<u64> = parts[1]
            .trim()
            .split(' ')
            .map(|p| p.parse::<u64>().unwrap())
            .collect::<Vec<u64>>();

        let n_components = components.len() - 1;

        let combinations = get_possible_combinations(n_components);

        for combination in &combinations {
            let mut total = components[0];
            for (i, _) in (0..n_components).enumerate() {
                match combination[i] {
                    '0' => total += components[i + 1],
                    '1' => total *= components[i + 1],
                    _ => panic!("What have you done..."),
                }

                if total == target {
                    break;
                }
            }

            if total == target {
                sum += total;
                break;
            }
        }
    }
    println!("Part 1: {sum}");
}
