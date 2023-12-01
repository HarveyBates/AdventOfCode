#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 255

void solve_pt1(const char *filename) {
  char line[LINE_LENGTH];
  char digits[LINE_LENGTH];

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  int idx = 0;
  int sum = 0;
  while (fgets(line, sizeof(line), file)) {
    memset(digits, 0, sizeof(digits));
    idx = 0;
    for (int c = 0; c < strlen(line); c++) {
      if (line[c] >= '0' && line[c] <= '9') {
        digits[idx++] = line[c];
      }
    }

    if (idx == 1) {
      digits[idx] = digits[0];
    }

    char final[3] = {digits[0], digits[idx - 1], '\0'};

    sum += atoi(final);
  }

  printf("Part 1: %d\n", sum);
  fclose(file);
}

struct Word {
  char *spelling;
  char value;
};

struct Word words[9] = {{"one", '1'},   {"two", '2'},   {"three", '3'},
                        {"four", '4'},  {"five", '5'},  {"six", '6'},
                        {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

void solve_pt2(const char *filename) {
  char line[LINE_LENGTH];
  char digits[LINE_LENGTH];

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  int idx = 0;
  size_t sum = 0;
  while (fgets(line, sizeof(line), file)) {
    memset(digits, 0, sizeof(digits));
    idx = 0;

    for (int x = 0; x < strlen(line); x++) {

      char window_chars[6];
      for (int c = 0; c < sizeof(window_chars) - 1; c++) {
        if (x + c < strlen(line)) {
          window_chars[c] = line[x + c];
        }

        if (c < 3) {
          if (window_chars[c] >= '0' && window_chars[c] <= '9') {
            digits[idx++] = window_chars[c];
          }
        }
      }

      for (int w = 0; w < 9; w++) {
        if (strstr(window_chars, words[w].spelling)) {
          digits[idx++] = words[w].value;
        }
      }
    }

    if (idx == 1) {
      digits[idx] = digits[0];
    }

    char final[3] = {digits[0], digits[idx - 1], 0};

    sum += atoi(final);
  }

  printf("Part 2: %ld\n", sum);
  fclose(file);
}

int main() {
  const char *filename = "input.txt";

  solve_pt1(filename);
  solve_pt2(filename);

  return 0;
}
