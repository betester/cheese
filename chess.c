
#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_PIECE 12
#define MAX_ROW 8
#define MAX_COL 8

Piece CHAR_MOVEMENTS[TOTAL_PIECE];
int DIRECTION_MOVEMENTS[TOTAL_PIECE][2];

int total_piece_movement_set = -1;

void set_direction_rule(Direction direction, int i, int j) {
  DIRECTION_MOVEMENTS[direction][0] = i;
  DIRECTION_MOVEMENTS[direction][1] = j;
}

Piece *create_piece(char piece_symbol[8],
                           Movements allowed_movements[8],
                           int set_up_movement, Player player) {
  Piece *piece = (struct Piece*) malloc(sizeof(Piece));
  strcpy(piece->piece_symbol, piece_symbol);
  piece->set_up_movement = set_up_movement;
  piece->player = player;

  for (int i = 0; i < set_up_movement; i++) {
    piece->allowed_movements[i] = allowed_movements[i];
  }

  piece->taken_move_state = NULL;

  return piece;
}

Piece *get_move_rule(char *piece) {
  for (int i = 0; i < TOTAL_PIECE; i++) {
    if (strcmp(CHAR_MOVEMENTS[i].piece_symbol, piece) == 0) {
      return &CHAR_MOVEMENTS[i];
    }
  }
  return NULL;
}

bool satisfy_movement_condition(Piece *target_piece_position,
                                MovementCondition condition) {
  return false;
}

bool movement_allowed(Movements *allowed_movements,
                      const Location *curr_loc,
                      const Location *next_location,
                      int total_movement_rule) {
  bool allowed = false;
  for (int i = 0; i < total_movement_rule; i++) {
    for (int j = 1; j <= allowed_movements[i].max_movement; j++) {
      int column_translation = curr_loc->i + DIRECTION_MOVEMENTS[allowed_movements[i].direction][0] * j;
      int row_translation = curr_loc->j + DIRECTION_MOVEMENTS[allowed_movements[i].direction][1] * j;
      allowed = allowed || (next_location->i == column_translation && next_location->j == row_translation);
    }
  }
  return allowed;
};

void move_piece(Piece *board[8][8], Location *curr_loc,
                Location *next_loc) {
  if (next_loc->i < 0 || next_loc->i >= 8 || next_loc->j < 0 ||
      next_loc->j >= 8) {
    printf("Out of bounds move, piece will not be moved");
    return;
  }

  Piece *curr_piece = board[curr_loc->i][curr_loc->j];
  Piece *next_piece = board[next_loc->i][next_loc->j];

  Movements *piece_movement = curr_piece->allowed_movements;

  if (piece_movement == NULL) {
    printf("No rule assigned for the piece %s\n", curr_piece->piece_symbol);
    return;
  }

  bool move_is_legal = movement_allowed(piece_movement, curr_loc, next_loc,
                                        curr_piece->set_up_movement);

  if (!move_is_legal) {
    printf("Movement is not allowed\n");
    return;
  }

  board[next_loc->i][next_loc->j] = curr_piece;
  board[curr_loc->i][curr_loc->j] = next_piece;
}

void render_board(Piece *board[MAX_COL][MAX_ROW]) {
  printf("*");
  for (int i = 0; i < MAX_ROW; i++) {
    printf("%d", i);
  }
  printf("\n");

  for (int i = 0; i < MAX_COL; i++) {
    printf("%d", i);
    for (int j = 0; j < MAX_ROW; j++) {
      printf("%s", board[i][j]->piece_symbol);
    }
    printf("\n");
  }
}
