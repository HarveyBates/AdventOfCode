// AOC: day03
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024

int is_symbol(char c) {
  // Is digit
  if (c >= '0' && c <= '9') {
    return 0;
  }

  // Is a dot
  if (c == '.') {
    return 0;
  }

  // Is a newline
  if (c == '\n') {
    return 0;
  }

  // Is a symbol
  return 1;
}

int search_adjacent(int row, int col, char schema[200][200], int n_rows,
                    int n_columns) {
  if (row > 0) {
    if (is_symbol(schema[row - 1][col])) {
      return 1;
    }
    if (col > 0) {
      if (is_symbol(schema[row - 1][col - 1])) {
        return 1;
      }
    }
    if (col < n_columns) {
      if (is_symbol(schema[row - 1][col + 1])) {
        return 1;
      }
    }
  }

  if (row < n_rows) {
    if (is_symbol(schema[row + 1][col])) {
      return 1;
    }
    if (col > 0) {
      if (is_symbol(schema[row + 1][col - 1])) {
        return 1;
      }
    }
    if (col < n_columns) {
      if (is_symbol(schema[row + 1][col + 1])) {
        return 1;
      }
    }
  }

  if (col > 0) {
    if (is_symbol(schema[row][col - 1])) {
      return 1;
    }
  }

  if (col < n_columns) {
    if (is_symbol(schema[row][col + 1])) {
      return 1;
    }
  }

  return 0;
}

void solve_pt1(const char *filename) {
  char line[LINE_LEN];
  unsigned long answer = 0;

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char schema[200][200];
  int columns = 0, rows = 0;
  while (fgets(line, sizeof(line), file)) {
    columns = strlen(line);
    for (int c = 0; c < strlen(line); c++) {
      schema[rows][c] = line[c];
    }
    rows++;
  }

  for (int row = 0; row < rows; row++) {
    char num[10];
    int num_idx;
    int match = 0;
    for (int col = 0; col < columns; col++) {
      char sym = schema[row][col];
      if ((sym < '0' || sym > '9') && !match) {
        memset(num, 0, sizeof(num));
        num_idx = 0;
        match = 0;
        continue;
      }

      if ((sym < '0' || sym > '9') && match) {
        answer += atoi(num);
        memset(num, 0, sizeof(num));
        num_idx = 0;
        match = 0;
        continue;
      }

      num[num_idx++] = sym;

      if (search_adjacent(row, col, schema, rows - 1, columns)) {
        match = 1;
      }
    }
  }

  fclose(file);
  printf("Part 1: %ld\n", answer);
}

int is_number(char c) {
  if (c >= '0' && c <= '9') {
    return 1;
  }
  return 0;
}

void get_number(int row, int column, char schema[200][200], char number[4],
                int n_rows, int n_columns) {

  int n_idx = 0;
  memset(number, 0, 4);
  if (!is_number(schema[row][column + 1])) {
    int start_point = column;
    for (int q = column; q > 0; q--) {
      if (!is_number(schema[row][q])) {
        break;
      }
      start_point--;
    }
    //  Search backward
    for (int s = start_point; s < column + 1; s++) {
      if (is_number(schema[row][s])) {
        number[n_idx++] = schema[row][s];
      }
    }
  } else if (!is_number(schema[row][column - 1])) {
    // Search forward
    for (int s = column; s < column + 3 && s < n_columns; s++) {
      if (is_number(schema[row][s])) {
        number[n_idx++] = schema[row][s];
      }
    }
  } else {
    //  Take surrounds
    for (int s = column - 1; s < column + 2; s++) {
      if (is_number(schema[row][s])) {
        number[n_idx++] = schema[row][s];
      }
    }
  }
}

int search_adjacent_numbers(int row, int col, char schema[200][200], int n_rows,
                            int n_columns) {
  int adj_numbers = 0;
  char number[4];
  int found_numbers[10];
  int fnd_idx = 0;
  memset(found_numbers, 0, sizeof(found_numbers));
  if (row > 0) {
    if (is_number(schema[row - 1][col])) {
      get_number(row - 1, col, schema, number, n_rows, n_columns);
      found_numbers[fnd_idx++] = atoi(number);
      memset(number, 0, sizeof(number));
      adj_numbers++;
    }
    if (col > 0) {
      if (is_number(schema[row - 1][col - 1])) {
        get_number(row - 1, col - 1, schema, number, n_rows, n_columns);
        found_numbers[fnd_idx++] = atoi(number);
        memset(number, 0, sizeof(number));
        adj_numbers++;
      }
    }
    if (col < n_columns) {
      if (is_number(schema[row - 1][col + 1])) {
        get_number(row - 1, col + 1, schema, number, n_rows, n_columns);
        found_numbers[fnd_idx++] = atoi(number);
        memset(number, 0, sizeof(number));
        adj_numbers++;
      }
    }
  }

  if (row < n_rows) {
    if (is_number(schema[row + 1][col])) {
      get_number(row + 1, col, schema, number, n_rows, n_columns);
      found_numbers[fnd_idx++] = atoi(number);
      memset(number, 0, sizeof(number));
      adj_numbers++;
    }
    if (col > 0) {
      if (is_number(schema[row + 1][col - 1])) {
        get_number(row + 1, col - 1, schema, number, n_rows, n_columns);
        found_numbers[fnd_idx++] = atoi(number);
        memset(number, 0, sizeof(number));
        adj_numbers++;
      }
    }
    if (col < n_columns) {
      if (is_number(schema[row + 1][col + 1])) {
        get_number(row + 1, col + 1, schema, number, n_rows, n_columns);
        found_numbers[fnd_idx++] = atoi(number);
        memset(number, 0, sizeof(number));
        adj_numbers++;
      }
    }
  }

  if (col > 0) {
    if (is_number(schema[row][col - 1])) {
      get_number(row, col - 1, schema, number, n_rows, n_columns);
      found_numbers[fnd_idx++] = atoi(number);
      memset(number, 0, sizeof(number));
      adj_numbers++;
    }
  }

  if (col < n_columns) {
    if (is_number(schema[row][col + 1])) {
      get_number(row, col + 1, schema, number, n_rows, n_columns);
      found_numbers[fnd_idx++] = atoi(number);
      memset(number, 0, sizeof(number));
      adj_numbers++;
    }
  }

  if (adj_numbers > 1) {
    int dups[5];
    int dups_idx = 0;
    for (int i = 0; i < fnd_idx; i++) {
      int found_dup = 0;
      for (int d = 0; d < 5; d++) {
        if (dups[d] == found_numbers[i]) {
          found_dup = 1;
          break;
        }
      }
      if (!found_dup) {
        dups[dups_idx++] = found_numbers[i];
      }
    }

    if (dups_idx != 2) {
      return 0;
    }

    return dups[0] * dups[1];
  }

  return 0;
}

unsigned long find_stars(char schema[200][200], int n_rows, int n_columns) {
  unsigned long sum = 0;
  for (int row = 0; row < n_rows; row++) {
    for (int col = 0; col < n_columns; col++) {
      if (schema[row][col] == '*') {
        sum += search_adjacent_numbers(row, col, schema, n_rows, n_columns);
      }
    }
  }

  return sum;
}

void solve_pt2(const char *filename) {
  char line[LINE_LEN];
  unsigned long answer = 0;

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char schema[200][200];
  int columns = 0, rows = 0;
  while (fgets(line, sizeof(line), file)) {
    columns = strlen(line);
    for (int c = 0; c < strlen(line); c++) {
      schema[rows][c] = line[c];
    }
    rows++;
  }

  answer = find_stars(schema, rows, columns);

  printf("Part 2: %ld\n", answer);
}

int main() {
  const char *filename = "input.txt";

  solve_pt1(filename);
  solve_pt2(filename);

  return 0;
}
