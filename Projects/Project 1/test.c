#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  uint8_t tiles[4][4];
} Board;

uint8_t to_power_of_two(uint32_t number) {
  if (((number & (number - 1)) == 0) &&
      number > 0) { // If the number is a power of two
    int32_t x = 0;
    for (x = 0; x < 32; x++) { // unsigned int
      if (number & (1 << x)) {
        return x;
      }
    }
  }

  return 0;
}

uint32_t max(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
  uint32_t max = a;

  if (b > max) {
    max = b;
  }

  if (c > max) {
    max = c;
  }

  if (d > max) {
    max = d;
  }

  return max;
}

void read_in_board(Board *board) {
  int32_t x, y;
  uint32_t temporary[4][4];

  for (y = 0; y < 4; y++) {
    scanf("%d %d %d %d", &temporary[0][y], &temporary[1][y], &temporary[2][y],
          &temporary[3][y]);
  }

  for (x = 0; x < 4; x++) {
    for (y = 0; y < 4; y++) {
      board->tiles[x][y] = to_power_of_two(temporary[x][y]);
    }
  }
}

Board *copy_board(Board *board) {
  Board *copy = malloc(sizeof(Board));
  memcpy(copy->tiles, board, sizeof(copy->tiles));
  return copy;
}

uint32_t largest_tile_value(Board *board) {
  uint32_t greatest = 0;
  uint8_t x, y;

  for (x = 0; x < 4; x++) {
    for (y = 0; y < 4; y++) {
      if (board->tiles[x][y] > greatest) {
        greatest = board->tiles[x][y];
      }
    }
  }
  if (greatest == 0) {
    return 0;
  } else {
    return 1 << greatest;
  }
}

Board *shift_left(Board *board) {
  Board *b = copy_board(board);
  int32_t x, y;
  bool did_nothing = true;

  for (y = 0; y < 4; y++) {
    bool no_move = false;
    while (!no_move) {
      no_move = true;
      for (x = 1; x < 4; x++) {
        if (b->tiles[x - 1][y] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x - 1][y] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }

    for (x = 1; x < 4; x++) {
      if (b->tiles[x - 1][y] == b->tiles[x][y] && b->tiles[x][y] != 0) {
        b->tiles[x - 1][y]++;
        b->tiles[x][y] = 0;
        did_nothing = false;
      }
    }

    no_move = false;
    while (!no_move) {
      no_move = true;
      for (x = 1; x < 4; x++) {
        if (b->tiles[x - 1][y] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x - 1][y] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }
  }
  if (did_nothing) return NULL;

  return b;
}

Board *shift_right(Board *board) {
  Board *b = copy_board(board);
  int32_t x, y;
  bool did_nothing = true;

  for (y = 0; y < 4; y++) {
    bool no_move = false;
    while (!no_move) {
      no_move = true;
      for (x = 2; x >= 0; x--) {
        if (b->tiles[x + 1][y] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x + 1][y] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }

    for (x = 2; x >= 0; x--) {
      if (b->tiles[x + 1][y] == b->tiles[x][y] && b->tiles[x][y] != 0) {
        b->tiles[x + 1][y]++;
        b->tiles[x][y] = 0;
        did_nothing = false;
      }
    }

    no_move = false;
    while (!no_move) {
      no_move = true;
      for (x = 2; x >= 0; x--) {
        if (b->tiles[x + 1][y] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x + 1][y] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }
  }
  if (did_nothing) return NULL;

  return b;
}

Board *shift_up(Board *board) {
  Board *b = copy_board(board);
  int32_t x, y;
  bool did_nothing = true;

  for (x = 0; x < 4; x++) {
    bool no_move = false;
    while (!no_move) {
      no_move = true;
      for (y = 1; y < 4; y++) {
        if (b->tiles[x][y - 1] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x][y - 1] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }

    for (y = 1; y < 4; y++) {
      if (b->tiles[x][y - 1] == b->tiles[x][y] && b->tiles[x][y] != 0) {
        b->tiles[x][y - 1]++;
        b->tiles[x][y] = 0;
        did_nothing = false;
      }
    }

    no_move = false;
    while (!no_move) {
      no_move = true;
      for (y = 1; y < 4; y++) {
        if (b->tiles[x][y - 1] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x][y - 1] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }
  }
  if (did_nothing) return NULL;

  return b;
}

Board *shift_down(Board *board) {
  Board *b = copy_board(board);
  int32_t x, y;
  bool did_nothing = true;

  for (x = 0; x < 4; x++) {
    bool no_move = false;
    while (!no_move) {
      no_move = true;
      for (y = 2; y >= 0; y--) {
        if (b->tiles[x][y + 1] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x][y + 1] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }

    for (y = 2; y >= 0; y--) {
      if (b->tiles[x][y + 1] == b->tiles[x][y] && b->tiles[x][y] != 0) {
        b->tiles[x][y + 1]++;
        b->tiles[x][y] = 0;
        did_nothing = false;
      }
    }

    no_move = false;
    while (!no_move) {
      no_move = true;
      for (y = 2; y >= 0; y--) {
        if (b->tiles[x][y + 1] == 0 && b->tiles[x][y] != 0) {
          b->tiles[x][y + 1] = b->tiles[x][y];
          b->tiles[x][y] = 0;
          no_move = false;
          did_nothing = false;
        }
      }
    }
  }
  if (did_nothing) return NULL;

  return b;
}

uint32_t calculate_greatest_tile(Board *current_state, uint32_t moves_left) {
  uint32_t current_value = largest_tile_value(current_state);
  if (moves_left == 0) {
    free(current_state);
    return current_value;
  }

  if (moves_left > 0) {
    Board *left = shift_left(current_state);
    Board *right = shift_right(current_state);
    Board *up = shift_up(current_state);
    Board *down = shift_down(current_state);
    uint32_t value = max(
        left == NULL ? current_value
                     : calculate_greatest_tile(left, moves_left - 1),
        right == NULL ? current_value
                      : calculate_greatest_tile(right, moves_left - 1),
        up == NULL ? current_value : calculate_greatest_tile(up, moves_left - 1),
        down == NULL ? current_value
                     : calculate_greatest_tile(down, moves_left - 1));

    free(current_state);
    return value;
  }
}

int main() {
  Board *board = malloc(sizeof(Board));
  read_in_board(board);

  int total = calculate_greatest_tile(board, 13);

  printf("%i\n", total);
  return 0;
}