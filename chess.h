
#include <stdbool.h>
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

enum MovementCondition {
  NOT_ATTACKED,
  ONLY_ONCE,
  EN_PASSANT,
  OCCUPIED_BY_OPPS
};

enum Player { BLACK, WHITE, NEUTRAL };

struct Location {
  unsigned int i;
  unsigned int j;
};

struct Movements {
  unsigned int max_movement : 3;
  enum Direction direction;
  enum MovementCondition movement_condition;
};

struct Piece {
  char piece_symbol[4];
  struct Movements allowed_movements[8];
  int set_up_movement;
  enum Player player;
  struct Location *taken_move_state;
};

void move_piece(struct Piece *piece[8][8], struct Location *curr_loc,
                struct Location *next_loc);

void render_board(struct Piece *board[8][8]);

void set_direction_rule(enum Direction direction, int i, int j);

struct Piece *create_piece(char piece_symbol[4],
                           struct Movements allowed_movements[8],
                           int set_up_movement, enum Player player);

struct Piece *get_move_rule(char piece[4]);

bool satisfy_movement_condition(struct Piece *target_piece_position,
                                enum MovementCondition condition);

bool movement_allowed(struct Movements *allowed_movements,
                      const struct Location *curr_loc,
                      const struct Location *next_location,
                      int total_movement_rule);
