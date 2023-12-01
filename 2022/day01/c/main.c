#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 20

int compare(const void *val1, const void *val2) {
  int a = *((int *)val1);
  int b = *((int *)val2);
  return (a > b) - (a < b);
}

void solve(FILE *file) {
  int sums[1000];
  char buffer[MAX_LINE_LEN];

  int idx = 0;
  int sum = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    if (buffer[0] == '\n') {
      sums[idx++] = sum;
      sum = 0;
      continue;
    }
    sum += atoi(buffer);
  }

  qsort(sums, idx, sizeof(int), compare);

  int top_three = 0;
  for (int i = idx - 1; i > idx - 4; i--) {
    top_three += sums[i];
  }

  printf("Part 1: %d\nPart 2: %d\n", sums[idx - 1], top_three);
}

o
