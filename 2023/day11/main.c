// AOC: day11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024
#define U_SIZE 200

void expand(char* arr, int size, int from_x) {
  arr[from_x] = '.';
  for (int x = size - 1; x > from_x - 1; x--) {
    arr[x + 1] = arr[x];
  }
}

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char uni[U_SIZE][U_SIZE];
  int idx = 0;
  int line_len = 0;
  while (fgets(line, sizeof(line), file)) {
    int all_dots_row = 1;
    // Get line length once
    if (!line_len) {
      line_len = (int)strlen(line) - 1;
    }

    // Populate universe
    for (int i = 0; i < (int)strlen(line) - 1; i++) {
      uni[idx][i] = line[i];
      if (all_dots_row && line[i] != '.') {
        all_dots_row = 0;
      }
    }

    idx++;

    // Add extra row if needed
    if (all_dots_row) {
      for (int i = 0; i < (int)strlen(line) - 1; i++) {
        uni[idx][i] = '.';
      }
      idx++;
    }
  }

  // Add extra columns if needed
  for (int x = 0; x < line_len; x++) {
    int all_dots = 1;
    for (int y = 0; y < idx; y++) {
      if (uni[y][x] != '.') {
        all_dots = 0;
        break;
      }
    }

    if (all_dots) {
      printf("Shift\n");
      // Add extra column
      for (int xx = 0; xx < line_len + 10; xx++) {
        expand(uni[xx], line_len, x);
      }
      x++;
      line_len++;
    }
  }

  char name = '1';
  for (int i = 0; i < idx; i++) {
    for (int x = 0; x < line_len; x++) {
      if (uni[i][x] == '#') {
        uni[i][x] = name++;
      }
      printf("%c", uni[i][x]);
    }
    printf("\n");
  }

  fclose(file);
  printf("Part 1: %d\n", answer);
}

int main() {
  const char* filename = "input.txt";
  solve_pt1(filename);
  return 0;
}
