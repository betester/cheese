
#include "chess.h"
#include <stdio.h>

// 1 indexed because why not ?
struct PieceMovement char_movements[13];
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

void move_piece(char (*board)[8][8], struct Location curr_loc,
                struct Location next_loc) {}

void render_board(char (*board)[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%s", board[i][j]);
    }
    printf("\n");
  }
}
