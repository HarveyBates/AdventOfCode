// AOC: day05
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEEDS 564398605
#define RAW_SEEDS 20

#define LINE_LEN 1024

unsigned long is_digit(char c) { return (c >= '0' && c <= '9'); }
unsigned long* min_value(unsigned long seeds[MAX_SEEDS],
                         unsigned long seeds_idx) {
  unsigned long* min = &seeds[0];
  for (unsigned long i = 0; i < seeds_idx; i++) {
    if (seeds[i] < *min) {
      min = &seeds[i];
    }
  }

  return min;
}

void search_mapping(unsigned long seeds[MAX_SEEDS], unsigned long seeds_idx,
                    unsigned long found_seeds[MAX_SEEDS], char* line) {
  unsigned long dest = 0;
  unsigned long src = 0;
  unsigned long range = 0;
  unsigned long idx = 0;
  char* token = strtok(line, " ");
  if (is_digit(token[0])) {
    while (token) {
      switch (idx) {
        case 0:
          dest = strtoll(token, NULL, 10);
          break;
        case 1:
          src = strtoll(token, NULL, 10);
          break;
        case 2:
          range = strtoll(token, NULL, 10);
          break;
      }
      token = strtok(NULL, " ");
      idx++;
    }
  }

  // dest src range

  unsigned long d = 0;
  for (unsigned long i = src; i < src + range; i++) {
    for (unsigned long s = 0; s < seeds_idx; s++) {
      if (found_seeds[s]) {
        continue;
      }

      if (seeds[s] == i) {
        found_seeds[s] = 1;
        seeds[s] = (dest + d);
      }
    }
    d++;
  }
}

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  unsigned long long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  unsigned long seeds[MAX_SEEDS];
  unsigned long seeds_idx = 0;
  memset(seeds, 0, sizeof(seeds));

  unsigned long found_seeds[MAX_SEEDS];
  memset(found_seeds, 0, sizeof(found_seeds));

  unsigned long new_parameter = 0;
  while (fgets(line, sizeof(line), file)) {
    if (strstr(line, "seeds:")) {
      char* token = strtok(line, " ");
      token = strtok(NULL, " ");
      while (token) {
        seeds[seeds_idx++] = strtoll(token, NULL, 10);
        token = strtok(NULL, " ");
      }
    }

    if (strstr(line, "map:")) {
      new_parameter = 1;
    }

    if (line[0] == '\n') {
      new_parameter = 0;
      memset(found_seeds, 0, sizeof(found_seeds));
      continue;
    }

    if (new_parameter) {
      search_mapping(seeds, seeds_idx, found_seeds, line);
      printf("Searching...\n");
    }
  }

  answer = *min_value(seeds, seeds_idx);

  fclose(file);
  printf("Part 1: %lld\n", answer);
}

static unsigned long seeds[MAX_SEEDS];
unsigned long seeds_idx = 0;

unsigned long seed_range_idx = 0;

unsigned long raw_seeds[RAW_SEEDS];
unsigned long raw_seeds_idx = 0;

static unsigned long found_seeds[MAX_SEEDS];

void solve_pt2(const char* filename) {
  char line[LINE_LEN];
  unsigned long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  memset(raw_seeds, 0, sizeof(raw_seeds));
  memset(found_seeds, 0, sizeof(found_seeds));

  while (fgets(line, sizeof(line), file)) {
    if (strstr(line, "seeds:")) {
      char* token = strtok(line, " ");
      token = strtok(NULL, " ");
      while (token) {
        if (raw_seeds_idx > RAW_SEEDS) {
          fclose(file);
          printf("ERROR");
          return;
        }
        raw_seeds[raw_seeds_idx++] = strtoll(token, NULL, 10);
        token = strtok(NULL, " ");
      }
      break;
    }
  }

  while (seed_range_idx < raw_seeds_idx - 1) {
    memset(seeds, 0, sizeof(seeds));
    memset(found_seeds, 0, sizeof(found_seeds));
    seeds_idx = 0;

    // printf("%lld %lld\n", raw_seeds[seed_range_idx],
    // raw_seeds[seed_range_idx + 1]);
    for (unsigned long s = raw_seeds[seed_range_idx];
         s < raw_seeds[seed_range_idx] + raw_seeds[seed_range_idx + 1]; s++) {
      seeds[seeds_idx++] = s;
    }
    seed_range_idx += 2;

    unsigned long new_parameter = 0;
    while (fgets(line, sizeof(line), file)) {
      if (strstr(line, "map:")) {
        new_parameter = 1;
      }

      if (line[0] == '\n') {
        new_parameter = 0;
        memset(found_seeds, 0, sizeof(found_seeds));
        continue;
      }

      if (new_parameter) {
        search_mapping(seeds, seeds_idx, found_seeds, line);
        // View range
        // for (unsigned long i = 0; i < seeds_idx; i++) {
        //  printf("%lld ", seeds[i]);
        //}
        // printf("\n");

        printf("Searching...\n");
      }
    }

    unsigned long min = *min_value(seeds, seeds_idx);
    if (min < answer || answer == 0) {
      answer = min;
    }
    rewind(file);
  }

  fclose(file);
  printf("Part 2: %ld\n", answer);
}

int main() {
  const char* filename = "input.txt";
  // solve_pt1(filename);
  solve_pt2(filename);
  return 0;
}
