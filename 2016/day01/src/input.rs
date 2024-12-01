use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;
use std::path::Path;

fn get_file(filename: &str) -> File {
    let manifest_dir = std::env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR is not set");

    let path = Path::new(&manifest_dir).join(filename);

    File::open(path).unwrap_or_else(|error|
        panic!("File: {filename}, not found. Error: {error}"))
}

#[allow(dead_code)]
pub fn get_line(filename: &str) -> String {
    let mut line = String::new();

    let file = get_file(filename);

    let mut reader = BufReader::new(file);

    reader.read_line(&mut line).unwrap_or_else(|error| panic!("File: {filename}, error: {error}"));

    line
}

#[allow(dead_code)]
pub fn get_lines(filename: &str) -> Vec<String> {
    let mut lines: Vec<String> = Vec::new();

    let file = get_file(filename);

    for line in BufReader::new(file).lines() {
        match line {
            Ok(line) => lines.push(line),
            Err(error) => panic!("Error parsing line: {error}")
        };
    }

    lines
}


