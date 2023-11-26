mod input {

    use std::fs::File;
    use std::io::BufReader;
    use std::io::BufRead;
    use std::error::Error;

    pub fn get(filename: &str) ->Result<Vec<String>, Box<dyn Error>> { 
        let mut lines: Vec<String> = Vec::new();

        let path = File::open(filename).unwrap_or_else(|_| panic!("File: {}, not found. Exiting.", filename));
        let file = BufReader::new(path);

        for line in file.lines(){
            match line {
                Ok(line) => lines.push(line),
                Err(e) => panic!("Line parsing error: {e}"),
            }
        }

        Ok(lines)
    }

}

mod solve {

    struct Moves {
        rock: char,
        paper: char,
        sissors: char,
    }

    impl Moves {
        pub fn as_array(&self) -> [char; 3] {
            [self.rock, self.paper, self.sissors]
        }
    }

    struct Scores {
        rock: i32,
        paper: i32,
        sissors: i32,
        win: i32,
        lose: i32,
        draw: i32,
    }

    pub fn part_one(input: &Vec<String>){

        let scores = Scores {
            rock: 1, 
            paper: 2, 
            sissors: 3, 
            win: 6,
            lose: 0,
            draw: 3,
        };

        let my_rules = Moves {
            rock: 'A',
            paper: 'B',
            sissors: 'C'
        };

        let their_rules = Moves {
            rock: 'X',
            paper: 'Y',
            sissors: 'Z'
        };

        let mut my_score = 0;
        let mut their_score = 0;
        for line in input.iter() {
            let turns = line.split_whitespace();

            let mut my_move = '0';
            let mut their_move = '0';
            for (i, turn) in turns.enumerate() {
                let t = turn.chars().next().expect("Error parsing turn");
                if i % 2 == 0 {
                    my_move = t;
                } else {
                    their_move = t;
                }
            }


            for mm in my_rules.as_array(){
                if mm == my_move {
                    for tm in their_rules.as_array(){
                        if tm == their_move {
                            if mm == my_rules.rock {
                                if tm == their_rules.rock {
                                    // Draw 
                                    my_score += scores.draw + scores.rock;
                                    their_score += scores.draw + scores.rock;
                                }
                                else if tm == their_rules.sissors {
                                    // Win
                                    my_score += scores.rock + scores.win;
                                    their_score += scores.lose + scores.sissors;
                                }
                                else if tm == their_rules.paper {
                                    // Loss
                                    my_score += scores.lose + scores.rock;
                                    their_score += scores.paper + scores.win;
                                }

                            } 
                            else if mm == my_rules.paper {
                                if tm == their_rules.rock {
                                    // Win
                                    my_score += scores.paper + scores.win;
                                    their_score += scores.lose + scores.rock;
                                }
                                else if tm == their_rules.sissors {
                                    // Loss
                                    my_score += scores.lose + scores.paper;
                                    their_score += scores.sissors + scores.win;
                                }
                                else if tm == their_rules.paper {
                                    // Draw
                                    my_score += scores.draw + scores.paper;
                                    their_score += scores.draw + scores.paper;
                                }
                                
                            }
                            else if mm == my_rules.sissors {
                                if tm == their_rules.rock {
                                    // Loss
                                    my_score += scores.lose + scores.sissors;
                                    their_score += scores.rock + scores.win;
                                }
                                else if tm == their_rules.sissors {
                                    // Draw
                                    my_score += scores.draw + scores.sissors;
                                    their_score += scores.draw + scores.sissors;
                                }
                                else if tm == their_rules.paper {
                                    // Win
                                    my_score += scores.sissors + scores.win;
                                    their_score += scores.lose + scores.paper;
                                }
                            }
                        }
                    }
                }
            }
        }
        println!("Part One: {their_score}");
    }


    pub fn part_two(input: &Vec<String>){

        let scores = Scores {
            rock: 1, 
            paper: 2, 
            sissors: 3, 
            win: 6,
            lose: 0,
            draw: 3,
        };

        let their_rules = Moves {
            rock: 'A',
            paper: 'B',
            sissors: 'C'
        };

        let my_rules = Moves {
            rock: 'X',
            paper: 'Y',
            sissors: 'Z'
        };

        let mut my_score = 0;
        let mut their_score = 0;
        for line in input.iter() {
            let turns = line.split_whitespace();

            let mut my_move = '0';
            let mut their_move = '0';
            for (i, turn) in turns.enumerate() {
                let t = turn.chars().next().expect("Error parsing turn");
                if i % 2 == 0 {
                    their_move = t;
                } else {
                    my_move = t;
                }
            }

            if my_move == 'Y' {
                // Draw 
                if their_move == their_rules.rock {
                    my_score += scores.rock + scores.draw;
                    their_score += scores.rock + scores.draw;
                }
                else if their_move == their_rules.paper {
                    my_score += scores.paper + scores.draw;
                    their_score += scores.paper + scores.draw;
                }
                else if their_move == their_rules.sissors {
                    my_score += scores.sissors + scores.draw;
                    their_score += scores.sissors + scores.draw;
                }
            }
            else if my_move == 'X' {
                // Lose 
                if their_move == their_rules.rock {
                    my_score += scores.sissors;
                    their_score += scores.rock + scores.win;
                }
                else if their_move == their_rules.paper {
                    my_score += scores.rock;
                    their_score += scores.paper + scores.win;
                }
                else if their_move == their_rules.sissors {
                    my_score += scores.paper;
                    their_score += scores.sissors + scores.win;
                }
            }
            else if my_move == 'Z' {
                // Win
                if their_move == their_rules.rock {
                    my_score += scores.paper + scores.win;
                    their_score += scores.rock;
                }
                else if their_move == their_rules.paper {
                    my_score += scores.sissors + scores.win;
                    their_score += scores.paper;
                }
                else if their_move == their_rules.sissors {
                    my_score += scores.rock + scores.win;
                    their_score += scores.sissors;
                }
            }
        }
        println!("Part Two: {my_score}");
    }
}

fn main() {
    let input = input::get("input.txt").unwrap();

    solve::part_one(&input);
    solve::part_two(&input);
}
