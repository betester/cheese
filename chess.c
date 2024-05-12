
#include "chess.h"
#include <stdio.h>
#include <string.h>

#define EMPTY_VALUE -10

// 1 indexed because why not ?
struct PieceMovement char_movements[13];
int direction_movement[12][2];

int total_piece_movement_set = 0;

void set_move_rule(struct PieceMovement piece_movement) {

  int next_position = total_piece_movement_set + 1;

  for (int i = 0; i <= total_piece_movement_set; i++) {

    if (char_movements[i].piece == piece_movement.piece) {
      printf("Already assign %s movement rule replacing the rule\n",
             piece_movement.piece);
      next_position = i;
      break;
    }
  }

  if (next_position >= 13) {
    printf("Cannot set more than 8 rules for piece movement for now\n");
    return;
  }

  printf("Setting up rule for piece %s\n", piece_movement.piece);
  for (int i = 0; i < 8; i++) {
    char_movements[next_position].allowed_movements[i] =
        piece_movement.allowed_movements[i];
  }

  if (next_position > total_piece_movement_set) {
    total_piece_movement_set = next_position;
  }
}

void set_direction_rule(enum Direction direction, int i, int j) {
  direction_movement[direction][0] = i;
  direction_movement[direction][1] = j;
}

struct PieceMovement *get_move_rule(char *piece) {
  for (int i = 0; i < 13; i++) {
    if (char_movements[i].piece == piece) {
      return &char_movements[i];
    }
  }
  return NULL;
}

bool movement_allowed(struct Movements *allowed_movements,
                      const struct Location *curr_loc,
                      const struct Location *next_location) {
  return false;
};

void move_piece(char (*board)[8][8], struct Location *curr_loc,
                struct Location *next_loc) {
  if (next_loc->i < 0 || next_loc->i >= 8 || next_loc->j < 0 ||
      next_loc->j >= 8) {
    printf("Out of bounds move, piece will not be moved");
    return;
  }

  char *curr_piece = board[curr_loc->i][curr_loc->j];
  char *next_piece = board[next_loc->i][next_loc->j];

  struct PieceMovement *piece_movement = get_move_rule(curr_piece);

  if (piece_movement == NULL) {
    printf("No rule assigned for the piece %s", curr_piece);
    return;
  }

  // check if the movements allowed
  struct Movements *allowed_movements = piece_movement->allowed_movements;
  bool move_is_legal = movement_allowed(allowed_movements, curr_loc, next_loc);

  if (!move_is_legal) {
    printf("Movement is not allowed");
    return;
  }

  strcpy(board[curr_loc->i][curr_loc->j], next_piece);
  strcpy(board[curr_loc->i][curr_loc->j], curr_piece);
}

void render_board(char (*board)[8][8]) {
  printf("*");
  for (int i = 0; i < 8; i++) {
    printf("%d", i);
  }
  printf("\n");

  for (int i = 0; i < 8; i++) {
    printf("%d", i);
    for (int j = 0; j < 8; j++) {
      printf("%s", board[i][j]);
    }
    printf("\n");
  }
}
