mod input;

fn part_one(puzzle: Vec<String>) {
    let mut rules: Vec<Vec<u32>> = vec![];
    let mut ordering: Vec<Vec<u32>> = vec![];

    // Get the rules
    for line in &puzzle {
        if line.is_empty() {
            break;
        }

        let rule = line
            .split('|')
            .map(|v| v.parse::<u32>().ok().unwrap())
            .collect::<Vec<_>>();
        rules.push(rule.clone());
    }

    // Get the page ordering
    let mut start = false;
    for line in &puzzle {
        if line.is_empty() {
            start = true;
            continue;
        }

        if !start {
            continue;
        }

        let order = line
            .split(',')
            .map(|v| v.parse::<u32>().ok().unwrap())
            .collect::<Vec<_>>();
        ordering.push(order.clone());
    }

    let mut sum: u32 = 0;
    let mut ordered: Vec<Vec<u32>> = vec![];
    let mut prior: Vec<u32> = vec![];
    for order in ordering {
        let mut pass_rules = true;
        for (idx, page) in order.iter().enumerate() {
            for rule in rules.iter() {
                if rule[1] != *page {
                    continue;
                }

                if prior.contains(&rule[0]) {
                    continue;
                }

                if order[idx..order.len()].contains(&rule[0]) {
                    // Fail
                    pass_rules = false;
                    break;
                }
            }

            if !pass_rules {
                break;
            }

            prior.push(*page)
        }

        if pass_rules {
            sum += order[order.len() / 2];
            ordered.push(order);
        }

        prior.clear();
    }

    println!("Part one: {sum}");
}

fn main() {
    let puzzle = input::get_lines("input.txt");
    part_one(puzzle);
}
