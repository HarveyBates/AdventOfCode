#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cube {
  int red;
  int green;
  int blue;
};

void solve_pt1(const char *filename) {
  char line[1024];

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  struct Cube dc = {12, 13, 14}; // Default

  int game_sum = 0;
  while (fgets(line, sizeof(line), file)) {
    int n_cubes;
    int game_id = 0;
    int valid = 1;

    char *token = strtok(line, ":");
    while (token) {
      if (strstr(token, "Game")) {
        sscanf(token, "Game %d:", &game_id);
      } else {
        if (strstr(token, "red")) {
          sscanf(token, " %d red", &n_cubes);
          if (n_cubes > dc.red) {
            valid = 0;
          }
        } else if (strstr(token, "blue")) {
          sscanf(token, " %d blue", &n_cubes);
          if (n_cubes > dc.blue) {
            valid = 0;
          }
        } else if (strstr(token, "green")) {
          sscanf(token, " %d green", &n_cubes);
          if (n_cubes > dc.green) {
            valid = 0;
          }
        }
      }

      token = strtok(NULL, ";,");
    }
    if (valid) {
      game_sum += game_id;
    }
  }

  fclose(file);
  printf("Part 1: %d\n", game_sum);
}

void solve_pt2(const char *filename) {
  char line[1024];

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  int game_sum = 0;
  while (fgets(line, sizeof(line), file)) {
    struct Cube c = {};
    int n_cubes;

    char *token = strtok(line, ":");
    while (token) {
      if (!strstr(token, "Game")) {
        if (strstr(token, "red")) {
          sscanf(token, " %d red", &n_cubes);
          if (n_cubes > c.red) {
            c.red = n_cubes;
          }
        } else if (strstr(token, "blue")) {
          sscanf(token, " %d blue", &n_cubes);
          if (n_cubes > c.blue) {
            c.blue = n_cubes;
          }
        } else if (strstr(token, "green")) {
          sscanf(token, " %d green", &n_cubes);
          if (n_cubes > c.green) {
            c.green = n_cubes;
          }
        }
      }

      token = strtok(NULL, ";,");
    }

    game_sum += c.red * c.green * c.blue;
  }

  fclose(file);

  printf("Part 2: %d\n", game_sum);
}

int main() {
  const char *filename = "input.txt";

  solve_pt1(filename);
  solve_pt2(filename);

  return 0;
}
