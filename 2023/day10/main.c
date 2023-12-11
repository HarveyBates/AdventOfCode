// AOC: day10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024
#define N_TILES 1000

struct Pipe {
  int x;
  int y;
};

void search(struct Pipe pp, struct Pipe cp, char tiles[N_TILES][N_TILES],
            int* moves) {
  char ct = tiles[cp.y][cp.x];
  *moves += 1;

  if (*moves > 100000) {
    printf("overflow\n");
    exit(0);
  }

  printf("%c\n", ct);

  struct Pipe np = {cp.x, cp.y};
  int err = 0;
  switch (ct) {
    case '|':
      if (pp.x != cp.x) {
        err = 1;
        break;
      }

      if (pp.y == cp.y - 1) {
        np.y = cp.y + 1;
        break;
      }

      if (pp.y == cp.y + 1) {
        np.y = cp.y - 1;
        break;
      }

      err = 1;
      break;
    case '-':
      if (pp.y != cp.y) {
        err = 1;
        break;
      }

      if (pp.x == cp.x - 1) {
        np.x = cp.x + 1;
        break;
      }

      if (pp.x == cp.x + 1) {
        np.x = cp.x - 1;
        break;
      }

      err = 1;
      break;
    case 'L':
      if (pp.y == cp.y - 1 && pp.x == cp.x) {
        // Go east
        np.x = cp.x + 1;
        break;
      }

      if (pp.y == cp.y && pp.x == cp.x + 1) {
        // Go north
        np.y = cp.y - 1;
        break;
      }

      err = 1;
      break;
    case 'J':
      if (pp.y == cp.y - 1 && pp.x == cp.x) {
        // Go west
        np.x = cp.x - 1;
        break;
      }
      if (pp.y == cp.y && pp.x == cp.x - 1) {
        // Go north
        np.y = cp.y - 1;
        break;
      }

      err = 1;
      break;
    case '7':
      if (pp.y == cp.y + 1 && pp.x == cp.x) {
        // Go west
        np.x = cp.x - 1;
        break;
      }

      if (pp.y == cp.y && pp.x == cp.x - 1) {
        // Go south
        np.y = cp.y + 1;
        break;
      }

      err = 1;
      break;
    case 'F':
      if (pp.y == cp.y + 1 && pp.x == cp.x) {
        // Go east
        np.x = cp.x + 1;
        break;
      }

      if (pp.y == cp.y && pp.x == cp.x + 1) {
        // Go south
        np.y = cp.y + 1;
        break;
      }

      err = 1;
      break;
    case '.':
      return;
    case 'S':
      printf("Done. N-Moves: %d\n", *moves / 2);
      exit(0);
      break;
    default:
      printf("Unknown");
      return;
  }

  if (err) {
    printf("err\n");
    return;
  }

  search(cp, np, tiles, moves);
}

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char tiles[N_TILES][N_TILES];
  int idx_y = 0, idx_x = 0;
  while (fgets(line, sizeof(line), file)) {
    int i = 0;
    for (; i < (int)strlen(line) - 1; i++) {
      tiles[idx_y][i] = line[i];
    }
    if (idx_x == 0) {
      idx_x = i;
    }
    idx_y++;
  }

  for (int y = 0; y < idx_y; y++) {
    for (int x = 0; x < idx_x; x++) {
      if (tiles[y][x] == 'S') {
        printf("(%d, %d)\n", x, y);
        struct Pipe pp = {x, y};
        struct Pipe cp = {x, y + 1};
        int moves = 0;
        search(pp, cp, tiles, &moves);
      }
    }
  };

  fclose(file);
  printf("Part 1: %d\n", answer);
}

int main() {
  const char* filename = "input.txt";
  solve_pt1(filename);
  return 0;
}
