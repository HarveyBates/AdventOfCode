mod input;

fn part_one((list_one, list_two): (&mut Vec<u32>, &mut Vec<u32>)) {
    list_one.sort();
    list_two.sort();

    let sum: u32 = list_one
        .iter()
        .zip(list_two.iter())
        .map(|(a, b)| a.abs_diff(*b))
        .sum::<u32>();

    println!("Part one: {sum}");
}

fn part_two((list_one, list_two): (Vec<u32>, Vec<u32>)) {
    let mut sum: u32 = 0;

    for item in list_one {
        sum += item * list_two.iter().filter(|&&n| n == item).count() as u32;
    }

    println!("Part two: {sum}");
}

fn main() {
    let lines = input::get_lines("input.txt");
    let (list_one, list_two): (Vec<u32>, Vec<u32>) = lines
        .iter()
        .filter_map(|line| {
            let mut sp = line.split_whitespace();
            let first = sp.next()?.parse::<u32>().ok();
            let second = sp.next()?.parse::<u32>().ok();
            Some((first?, second?))
        })
        .collect();

    part_one((&mut list_one.clone(), &mut list_two.clone()));
    part_two((list_one.clone(), list_two.clone()));
}
