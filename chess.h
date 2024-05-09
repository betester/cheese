
#include <stdint.h>

enum Direction {
  UP,
  LEFT,
  RIGHT,
  DOWN,
  DIAGONAL_UP_LEFT,
  DIAGONAL_UP_RIGHT,
  DIAGONAL_DOWN_LEFT,
  DIAGIONAL_DOWN_RIGHT,
  L_MOVEMENT_TOP_LEFT,
  L_MOVEMENT_TOP_RIGHT,
  L_MOVEMENT_BOTTOM_LEFT,
  L_MOVEMENT_BOTTOM_RIGHT,
};

struct Location {
  unsigned int i : 3;
  unsigned int j : 3;
};

struct Movements {
  unsigned int max_movement : 3;
  enum Direction direction;
};

struct PieceMovement {
  char piece[8];
  struct Movements allowed_movements[8];
};

void move_piece(char board[8][8][8], struct Location curr_loc,
                struct Location next_loc);

void render_board(char board[8][8][8]);

void set_move_rule(struct PieceMovement piece_movement);
