// AOC: day04
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024

void solve_pt1(const char *filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  while (fgets(line, sizeof(line), file)) {
    int game_score = 0;
    char *token = strtok(line, ":");
    token = strtok(NULL, " ");
    int winners[12];
    int my_hand[50];
    int winner_idx = 0, my_hand_idx = 0;
    int split = 0;
    while (token) {
      if (token[0] == '|') {
        split = 1;
      }
      if (token[0] >= '0' && token[0] <= '9') {
        if (!split) {
          winners[winner_idx++] = atoi(token);
        } else {
          my_hand[my_hand_idx++] = atoi(token);
        }
      }

      token = strtok(NULL, " ");
    }

    // Evaluate scratchcards
    for (int w = 0; w < winner_idx; w++) {
      for (int m = 0; m < my_hand_idx; m++) {
        if (winners[w] == my_hand[m]) {
          if (game_score < 2) {
            game_score++;
          } else {
            int current_game_score = game_score;
            game_score = current_game_score * 2;
          }
          break;
        }
      }
    }
    answer += game_score;
  }

  fclose(file);
  printf("Part 1: %d\n", answer);
}

void solve_pt2(const char *filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  int sc[300];
  int current_sc = 0;
  memset(sc, 0, sizeof(sc));
  while (fgets(line, sizeof(line), file)) {
    char *token = strtok(line, ":");
    token = strtok(NULL, " ");
    int winners[12];
    int my_hand[50];
    int winner_idx = 0, my_hand_idx = 0;
    int split = 0;
    while (token) {
      if (token[0] == '|') {
        split = 1;
      }
      if (token[0] >= '0' && token[0] <= '9') {
        if (!split) {
          winners[winner_idx++] = atoi(token);
        } else {
          my_hand[my_hand_idx++] = atoi(token);
        }
      }

      token = strtok(NULL, " ");
    }

    sc[current_sc]++;
    int matches = 0;
    for (int w = 0; w < winner_idx; w++) {
      for (int m = 0; m < my_hand_idx; m++) {
        if (winners[w] == my_hand[m]) {
          int next_card = sc[current_sc + matches + 1];
          sc[current_sc + matches + 1] += sc[current_sc];
          matches++;
          break;
        }
      }
    }

    current_sc++;
  }

  for (int i = 0; i < 300; i++) {
    answer += sc[i];
  }

  fclose(file);
  printf("Part 2: %d\n", answer);
}

int main() {
  const char *filename = "input.txt";
  solve_pt1(filename);
  solve_pt2(filename);
  return 0;
}
