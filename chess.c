
#include "chess.h"
#include <stdio.h>
#include <string.h>

#define TOTAL_PIECE 12
#define MAX_ROW 8
#define MAX_COL 8

struct PieceMovement CHAR_MOVEMENTS[TOTAL_PIECE];
int DIRECTION_MOVEMENTS[TOTAL_PIECE][2];

int total_piece_movement_set = -1;

void set_move_rule(struct PieceMovement piece_movement) {

  int next_position = total_piece_movement_set + 1;

  for (int i = 0; i < total_piece_movement_set; i++) {

    if (CHAR_MOVEMENTS[i].piece == piece_movement.piece) {
      printf("Already assign %s movement rule replacing the rule\n",
             piece_movement.piece);
      next_position = i;
      break;
    }
  }

  if (next_position >= TOTAL_PIECE) {
    printf("Cannot set more than 12 rules for piece movement for now\n");
    return;
  }

  printf("Setting up rule for piece %s\n", piece_movement.piece);

  strcpy(CHAR_MOVEMENTS[next_position].piece, piece_movement.piece);
  CHAR_MOVEMENTS[next_position].set_up_movement =
      piece_movement.set_up_movement;

  for (int i = 0; i < piece_movement.set_up_movement; i++) {
    CHAR_MOVEMENTS[next_position].allowed_movements[i] =
        piece_movement.allowed_movements[i];
  }

  if (next_position > total_piece_movement_set) {
    total_piece_movement_set = next_position;
  }
}

void set_direction_rule(enum Direction direction, int i, int j) {
  DIRECTION_MOVEMENTS[direction][0] = i;
  DIRECTION_MOVEMENTS[direction][1] = j;
}

struct PieceMovement *get_move_rule(char *piece) {
  for (int i = 0; i < TOTAL_PIECE; i++) {
    if (strcmp(CHAR_MOVEMENTS[i].piece, piece) == 0) {
      return &CHAR_MOVEMENTS[i];
    }
  }
  return NULL;
}

bool movement_allowed(struct Movements *allowed_movements,
                      const struct Location *curr_loc,
                      const struct Location *next_location,
                      int total_movement_rule) {
  bool allowed = false;
  printf("%d", total_movement_rule);
  for (int i = 0; i < total_movement_rule; i++) {
    for (int j = 1; j <= allowed_movements[i].max_movement; j++) {
      int column_translation =
          curr_loc->i +
          DIRECTION_MOVEMENTS[allowed_movements[i].direction][0] * j;
      int row_translation =
          curr_loc->j +
          DIRECTION_MOVEMENTS[allowed_movements[i].direction][1] * j;
      printf("(%d %d) (%d %d)\n", column_translation, row_translation,
             next_location->i, next_location->j);
      allowed = allowed || (next_location->i == column_translation &&
                            next_location->j == row_translation);
    }
  }
  return allowed;
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
    printf("No rule assigned for the piece %s\n", curr_piece);
    return;
  }

  // check if the movements allowed
  struct Movements *allowed_movements = piece_movement->allowed_movements;
  bool move_is_legal = movement_allowed(allowed_movements, curr_loc, next_loc,
                                        piece_movement->set_up_movement);

  if (!move_is_legal) {
    printf("Movement is not allowed\n");
    return;
  }

  char temp[8];

  strcpy(temp, board[curr_loc->i][curr_loc->j]);
  strcpy(board[curr_loc->i][curr_loc->j], board[next_loc->i][next_loc->j]);
  strcpy(board[next_loc->i][next_loc->j], temp);
}

void render_board(char (*board)[MAX_COL][MAX_ROW]) {
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
