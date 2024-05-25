
#include <stdbool.h>
#include <stdint.h>

typedef enum Direction {
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
} Direction;

typedef enum MovementCondition {
  NOT_ATTACKED,
  ONLY_ONCE,
  EN_PASSANT,
  OCCUPIED_BY_OPPS
} MovementCondition;

typedef enum Player { BLACK, WHITE, NEUTRAL } Player;

typedef struct Location {
  unsigned int i;
  unsigned int j;
} Location;

typedef struct Movements {
  unsigned int max_movement : 3;
  Direction direction;
  MovementCondition movement_condition;
} Movements;

typedef struct Piece {
  char piece_symbol[8];
  Movements allowed_movements[8];
  int set_up_movement;
  Player player;
  Location *taken_move_state;
} Piece;

void move_piece(Piece *piece[8][8], Location *curr_loc,
                Location *next_loc);

void render_board(Piece *board[8][8]);

void set_direction_rule(Direction direction, int i, int j);

Piece *create_piece(char piece_symbol[8],
                           Movements allowed_movements[8],
                           int set_up_movement, Player player);

Piece *get_move_rule(char piece[4]);

bool satisfy_movement_condition(Piece *target_piece_position,
                                MovementCondition condition);

bool movement_allowed(Movements *allowed_movements,
                      const Location *curr_loc,
                      const Location *next_location,
                      int total_movement_rule);
