// AOC: day06
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Race {
  unsigned long time;
  unsigned long record;
};

void solve_pt1() {
  int answer = 0;

  struct Race races[4] = {
      {55, 246},
      {82, 1441},
      {64, 1012},
      {90, 1111},
  };

  for (int i = 0; i < 4; i++) {
    int wins = 0;
    struct Race race = races[i];
    for (unsigned long t = 0; t <= race.time; t++) {
      unsigned long distance = (race.time - t) * t;
      if (distance > race.record) {
        wins++;
      }
    }
    if (answer == 0) {
      answer = wins;
    } else {
      answer *= wins;
    }
  }

  printf("Part 1: %d\n", answer);
}

void solve_pt2() {
  unsigned long answer = 0;

  struct Race race = {
      55826490,
      246144110121111,
  };

  for (unsigned long t = 0; t <= race.time; t++) {
    unsigned long distance = (race.time - t) * t;
    if (distance > race.record) {
      answer++;
    }
  }

  printf("Part 2: %ld\n", answer);
}

int main() {
  solve_pt1();
  solve_pt2();
  return 0;
}
