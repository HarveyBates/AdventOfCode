// AOC: day08
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024

#define NETWORK_SIZE 1000

// char* instructions = "LR";
char* instructions =
    "LRRLLRLLRRRLRRLRLRRRLRLLRLRRLRRRLRRRLRRLRRRLRLRRRLRLRRLRLRRRLRRLLRRLLLRRLR"
    "LRRRLRLRRRLRRLRRRLRLLRRLRRLRLRRRLRRRLRRLRRLLRLLRRRLRLRRLRRRLRRLRRRLRRRLLLL"
    "RRLRLRRRLRRRLLRRLLRRLRRRLRRRLRLRLLRRLRLRLRLRLRRLRLRLRRRLRRLRRLRRLRRRLRLRRR"
    "LRLRRLRLLLLRRRLLRRRLRLLRRRLRLLRRRLLRRLRLRLRLRLLLLRRLRRRLRLLRRLRRRLRRRLRLRR"
    "LRRLRLLRRRR";

struct Network {
  char point[4];
  char left[4];
  char right[4];
};

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  struct Network network[NETWORK_SIZE];
  int network_idx = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%3[^ ] = (%3[^,], %3[^)])", network[network_idx].point,
           network[network_idx].left, network[network_idx].right);
    network_idx++;
  }

  int cp = 0;
  for (; cp < network_idx; cp++) {
    if (strstr(network[cp].point, "AAA")) {
      break;
    }
  }

  int idx = 0;
  while (!strstr(network[cp].point, "ZZZ")) {
    struct Network cn = network[cp];

    if (idx > (int)strlen(instructions) - 1) {
      idx = 0;
    }

    char* search = instructions[idx] == 'L' ? cn.left : cn.right;

    for (int i = 0; i < network_idx; i++) {
      if (strstr(network[i].point, search)) {
        cp = i;
        break;
      }
    }

    idx++;
    answer++;
  }

  fclose(file);
  printf("Part 1: %d\n", answer);
}

void solve_pt2(const char* filename) {
  char line[LINE_LEN];
  unsigned long long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  struct Network network[NETWORK_SIZE];
  int network_idx = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%3[^ ] = (%3[^,], %3[^)])", network[network_idx].point,
           network[network_idx].left, network[network_idx].right);
    network_idx++;
  }

  int cp = 0;
  struct Network sn[20];
  int sn_idx = 0;
  for (; cp < network_idx; cp++) {
    if (network[cp].point[2] == 'A') {
      sn[sn_idx++] = network[cp];
    }
  }

  printf("%d\n", sn_idx);

  int idx = 0;
  while (1) {
    for (int s = 0; s < sn_idx; s++) {
      struct Network cn = sn[s];

      if (idx > (int)strlen(instructions) - 1) {
        idx = 0;
      }

      char* search = instructions[idx] == 'L' ? cn.left : cn.right;

      for (int i = 0; i < network_idx; i++) {
        if (strstr(network[i].point, search)) {
          sn[s] = network[i];
          // printf("%c %s\n", instructions[idx], sn[s].point);
          break;
        }
      }

      int all_z = 0;
      for (int i = 0; i < sn_idx; i++) {
        if (sn[i].point[2] == 'Z') {
          all_z++;
        }
      }

      if (all_z >= sn_idx) {
        printf("%lld\n", answer * sn_idx);
        exit(0);
      }
    }

    idx++;
    answer++;
  }

  fclose(file);
  printf("Part 1: %lld\n", answer);
}

int main() {
  const char* filename = "input.txt";
  // solve_pt1(filename);
  solve_pt2(filename);
  return 0;
}
