mod input;

fn main() {
    let mut puzzle = input::get_lines("input.txt")
        .iter()
        .map(|s| s.chars().collect())
        .collect::<Vec<Vec<char>>>();

    let (mut guard_x, mut guard_y): (usize, usize) = puzzle
        .iter()
        .enumerate()
        .find_map(|(y, s)| s.iter().position(|&c| c == '^').map(|x| (x, y)))
        .unwrap_or_else(|| panic!("Guard not found."));

    let start_pos = format!("{guard_y}-{guard_x}").parse::<String>().unwrap();

    let mut moves: Vec<String> = vec![start_pos];
    loop {
        // Peek the next tile
        let next_tile: char = match puzzle[guard_y][guard_x] {
            '^' => {
                if guard_y == 0 {
                    break;
                }
                puzzle[guard_y - 1][guard_x]
            }
            'v' => {
                if guard_y == puzzle.len() - 1 {
                    break;
                }
                puzzle[guard_y + 1][guard_x]
            }
            '>' => {
                if guard_x == puzzle[0].len() - 1 {
                    break;
                }
                puzzle[guard_y][guard_x + 1]
            }
            '<' => {
                if guard_x == 0 {
                    break;
                }
                puzzle[guard_y][guard_x - 1]
            }
            _ => panic!("Unknown next tile."),
        };

        // Store the guards position
        let (tmp_x, tmp_y) = (guard_x, guard_y);

        if next_tile == '#' {
            // Rotate guard
            let rotation: char = match puzzle[guard_y][guard_x] {
                '^' => '>',
                'v' => '<',
                '>' => 'v',
                '<' => '^',
                _ => panic!("Guard couldn't be rotated."),
            };
            puzzle[tmp_y][tmp_x] = '.';
            puzzle[guard_y][guard_x] = rotation;
        } else {
            // Move guard one tile
            match puzzle[guard_y][guard_x] {
                '^' => guard_y -= 1,
                'v' => guard_y += 1,
                '>' => guard_x += 1,
                '<' => guard_x -= 1,
                _ => panic!("Guard disappeared."),
            }
            puzzle[guard_y][guard_x] = puzzle[tmp_y][tmp_x];
            puzzle[tmp_y][tmp_x] = '.';
            let cmb = format!("{guard_y}-{guard_x}").parse::<String>().unwrap();
            if !moves.contains(&cmb) {
                moves.push(cmb);
            }
        }
    }

    let n_moves = moves.len();
    println!("Part one: {n_moves}");
}
