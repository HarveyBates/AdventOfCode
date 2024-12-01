// AOC: day13
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024
#define XY 40

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char pattern[XY][XY];
  int yy = 0, xx = 0;
  memset(pattern, 0, sizeof(pattern));
  while (fgets(line, sizeof(line), file)) {
    for (xx = 0; xx < (int)strlen(line) - 1; xx++) {
      pattern[yy][xx] = line[xx];
    }

    yy++;
  }

  // Get midpoint
  int mid = 0;
  int d = 0;
  if (yy % 2 == 0) {
    mid = yy / 2;
  } else {
    mid = yy / 2;
    mid++;
    d++;
  }
  printf("Middle: %d\n", mid);

  int u = yy;
  for (; d < mid; d++) {
    printf("%s\n", pattern[d]);
    printf("%s\n", pattern[u - 1]);
    for (int x = 0; x < xx - 1; x++) {
      if (pattern[d][x] != pattern[u][x]) {
        printf("Reflect: %d\n", x);
        goto cleanup;
      }
    }
    u--;
  }

cleanup:
  fclose(file);
  printf("Part 1: %d\n", answer);
}

int main() {
  const char* filename = "input.txt";
  solve_pt1(filename);
  return 0;
}
