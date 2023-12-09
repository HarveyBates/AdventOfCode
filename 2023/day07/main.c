// AOC: day07
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024
#define N_HANDS 1000

struct Dups {
  char c;
  unsigned long occ;
};

unsigned long in_dups(char c, struct Dups dups[N_HANDS]) {
  for (unsigned long d = 0; d < N_HANDS; d++) {
    if (dups[d].c == c) {
      return 1;
    }
  }
  return 0;
}

unsigned long dups_index(char c, struct Dups dups[N_HANDS]) {
  for (unsigned long d = 0; d < N_HANDS; d++) {
    if (dups[d].c == c) {
      return d;
    }
  }
  return 0;
}

enum Hand { HIGH, ONE, TWO, THREE, FULL_HOUSE, FOUR, FIVE };

struct Hand_Eval {
  char raw[5];
  enum Hand hand;
  unsigned long bid;
  int strength;
};

enum Hand get_hand(struct Dups dups[N_HANDS], unsigned long dups_idx) {
  if (dups_idx == 5) {
    return HIGH;
  }

  if (dups[0].occ == 5) {
    return FIVE;
  }

  unsigned long full_house = 0;
  unsigned long pairs = 0;
  for (unsigned long d = 0; d < N_HANDS; d++) {
    if (dups[d].occ == 4) {
      return FOUR;
    }

    if (dups[d].occ == 3) {
      if (pairs > 0) {
        return FULL_HOUSE;
      }
      full_house++;
    }

    if (dups[d].occ == 2) {
      if (full_house > 0) {
        return FULL_HOUSE;
      }
      pairs++;
    }
  }

  if (full_house == 1) {
    return THREE;
  }

  if (pairs == 2) {
    return TWO;
  }

  return ONE;
}

char strengths[13] = {'2', '3', '4', '5', '6', '7', '8',
                      '9', 'T', 'J', 'Q', 'K', 'A'};

int get_strength(char c) {
  for (unsigned long i = 0; i < 13; i++) {
    if (c == strengths[i]) {
      return i;
      break;
    }
  }
  return 0;
}

int sort_by_hand(const void* a, const void* b) {
  struct Hand_Eval* aa = (struct Hand_Eval*)(a);
  struct Hand_Eval* bb = (struct Hand_Eval*)(b);

  if ((int)bb->hand < (int)aa->hand) {
    return -1;
  }

  if ((int)bb->hand > (int)aa->hand) {
    return 1;
  }

  if ((int)bb->strength < (int)aa->strength) {
    return -1;
  }

  if ((int)bb->strength > (int)aa->strength) {
    return 1;
  }

  for (int i = 0; i < 5; i++) {
    int a_str = get_strength(aa->raw[i]);
    int b_str = get_strength(bb->raw[i]);
    if (b_str < a_str) {
      return -1;
    }

    if (b_str > a_str) {
      return 1;
    }
  }

  return 0;
}

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  unsigned long long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  struct Hand_Eval hands[N_HANDS];
  unsigned long hand_idx = 0;
  memset(hands, 0, sizeof(hands));

  struct Dups dups[N_HANDS];
  while (fgets(line, sizeof(line), file)) {
    char* hand = strtok(line, " ");
    memset(dups, 0, sizeof(dups));
    unsigned long dups_idx = 0;
    for (unsigned long i = 0; i < (unsigned long)strlen(hand); i++) {
      if (!in_dups(hand[i], dups)) {
        dups[dups_idx].occ = 1;
        dups[dups_idx++].c = hand[i];
      }
      for (unsigned long q = (i + 1); q < (unsigned long)strlen(hand); q++) {
        if (hand[i] == hand[q]) {
          dups[dups_index(hand[i], dups)].occ++;
          break;
        }
      }
    }
    memcpy(hands[hand_idx].raw, hand, sizeof(hands[hand_idx].raw));
    hands[hand_idx].strength = get_strength(hand[0]);
    hands[hand_idx].hand = get_hand(dups, dups_idx);
    char* bidstr = strtok(NULL, " ");
    hands[hand_idx++].bid = atoi(bidstr);
  }

  qsort(hands, hand_idx, sizeof(struct Hand_Eval), sort_by_hand);

  for (unsigned long i = 0; i < hand_idx; i++) {
    printf("%s %d\n", hands[i].raw, hands[i].hand);
    answer += (unsigned long)((hand_idx - i) * (unsigned long)hands[i].bid);
  }

  fclose(file);
  printf("Part 1: %lld\n", answer);
}

void solve_pt2(const char* filename) {
  char line[LINE_LEN];
  unsigned long long answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  struct Hand_Eval hands[N_HANDS];
  unsigned long hand_idx = 0;
  memset(hands, 0, sizeof(hands));

  struct Dups dups[N_HANDS];
  while (fgets(line, sizeof(line), file)) {
    char* hand = strtok(line, " ");
    memset(dups, 0, sizeof(dups));
    unsigned long dups_idx = 0;
    for (unsigned long i = 0; i < (unsigned long)strlen(hand); i++) {
      if (!in_dups(hand[i], dups)) {
        dups[dups_idx].occ = 1;
        dups[dups_idx++].c = hand[i];
      }
      for (unsigned long q = (i + 1); q < (unsigned long)strlen(hand); q++) {
        if (hand[i] == hand[q]) {
          dups[dups_index(hand[i], dups)].occ++;
          break;
        }
      }
    }
    memcpy(hands[hand_idx].raw, hand, sizeof(hands[hand_idx].raw));
    hands[hand_idx].strength = get_strength(hand[0]);
    hands[hand_idx].hand = get_hand(dups, dups_idx);
    char* bidstr = strtok(NULL, " ");
    hands[hand_idx++].bid = atoi(bidstr);
  }

  qsort(hands, hand_idx, sizeof(struct Hand_Eval), sort_by_hand);

  for (unsigned long i = 0; i < hand_idx; i++) {
    printf("%s %d\n", hands[i].raw, hands[i].hand);
    answer += (unsigned long)((hand_idx - i) * (unsigned long)hands[i].bid);
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
