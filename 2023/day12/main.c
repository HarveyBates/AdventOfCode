// AOC: day12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024

char operational = '.';
char damaged = '#';
char unknown = '?';

int explore(char* input, int i, int size, int target, int* count) {
  if (target == *count) {
    return 1;
  }

  switch (input[i]) {
    case '.':
      break;
    case '#':
      break;
    case '?':
      input[i + 1] = '#';
      explore(input, i + 1, size, target, count);
      input[i + 1] = '?';
      break;
    default:
      break;
  }

  if (input[i] == '?') {
  }

  return 0;
}

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  int arr[10];  // Arrangements
  int arr_idx = 0;
  while (fgets(line, sizeof(line), file)) {
    char* input = strtok(line, " ");

    char* result = strtok(NULL, ",");
    while (result) {
      if (arr_idx > (int)sizeof(arr_idx)) {
        printf("Exit...\n");
        goto exit;
      }
      arr[arr_idx++] = atoi(result);
      result = strtok(NULL, ",");
    }
    if (result) {
      printf("%s%s\n", result, input);
    }

    for (int i = 0; i < arr_idx; i++) {
      int n_hash = 0;
      for (int c = 0; c < (int)strlen(input) - 1; c++) {
        switch (input[c]) {
          case '.':
            continue;
          case '#':
            n_hash++;
            break;
          case '?':
            // Replace
            break;
          default:
            printf("Error\n");
            goto exit;
        }
        if (n_hash == arr[i]) {
          break;
        }
      }
      printf("%d ", arr[i]);
    }
    printf("\n%s\n", input);
  }

exit:
  fclose(file);
  // printf("Part 1: %d\n", answer);
}

int main() {
  const char* filename = "input.txt";
  solve_pt1(filename);
  return 0;
}
