// AOC: day09
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 400

#define N_VALS 50

long long last_elem(long long arr[N_VALS]) {
  for (long long x = 1; x < N_VALS; x++) {
    if (arr[x] == 0) {
      return x;
    }
  }
  return 0;
}

long long all_zeros(long long arr[N_VALS]) {
  for (long long x = 0; x < N_VALS; x++) {
    if (arr[x] != 0) {
      return 0;
    }
  }
  return 1;
}

long long is_div(long long a, long long b) { return (b % a == 0); }

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  long long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  while (fgets(line, sizeof(line), file)) {
    long long input[N_VALS][N_VALS];
    memset(input, 0, sizeof(input));

    long long val = 0;
    long long i = 0;

    char* token = strtok(line, " ");
    while (token) {
      input[i][val++] = atoi(token);
      token = strtok(NULL, " ");
    }

    while (1) {
      if (all_zeros(input[i])) {
        // printf("Complete\n");
        answer += input[0][last_elem(input[0]) - 1];
        printf("%lld (%lld rows)\n", input[0][last_elem(input[0]) - 1], i);
        for (long long s = 0; s < i; s++) {
          for (long long v = 0; v < val; v++) {
            printf("%lld ", input[s][v]);
          }
          printf("\n");
        }
        break;
      }

      // Traverse
      for (long long v = 0; v < val; v++) {
        // printf("%d ", input[i][v]);
        long long res = input[i][v + 1] - input[i][v];
        if (res >= 0) {
          input[i + 1][v] = res;
        }
      }

      // Add elements if divisable
      long long div = 0;
      if (is_div(input[i][1], input[i][0])) {
        div = 1;
        for (long long v = 1; v < val - 1; v++) {
          if (is_div(input[i][v + 1], input[i][v])) {
            div = 1;
          } else {
            div = 0;
            break;
          }
        }
      }

      if (div) {
        long long a = input[i][val - 1] + (input[i][1] % input[i][0]);
        input[i][val] = a;
        printf("e: %lld\n", a);

        for (long long q = i; q > 0; q--) {
          long long ule = last_elem(input[q - 1]);
          long long cle = last_elem(input[q]);

          long long ci = input[q][cle - 1];
          long long ui = input[q - 1][ule - 1];
          long long ni = ci + ui;
          printf("ci: %lld ui: %lld = %lld\n", ci, ui, ni);
          input[q - 1][cle] = ni;
        }
      }

      // printf("\n");
      val--;
      i++;
    }
  }

  fclose(file);
  printf("Part 1: %lld\n", answer);
}

int main() {
  const char* filename = "input.txt";
  solve_pt1(filename);
  // solve_pt2(filename);
  return 0;
}
