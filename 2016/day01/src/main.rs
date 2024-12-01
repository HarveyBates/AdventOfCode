mod input;

struct Instructions {
    direction: char,
    distance: u16
}


fn main() {
    let line = input::get_line("input.txt");
    let puzzle: Vec<_> = line.split(',').map(|s| s.trim())

    for row in puzzle {
        println!("{:?}", row);
    }
}
