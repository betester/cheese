
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
  L_STAND_TOP_LEFT,
  L_STAND_TOP_RIGHT,
  L_STAND_BOTTOM_LEFT,
  L_STAND_BOTTOM_RIGHT,
  L_SLEEP_TOP_LEFT,
  L_SLEEP_TOP_RIGHT,
  L_SLEEP_BOTTOM_LEFT,
  L_SLEEP_BOTTOM_RIGHT,
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
  int total_taken_movements;
  Location *taken_move_state;
} Piece;

typedef struct Board {
  Player player_order[2];
  Piece *board[8][8];
  Player current_player;
} Board;

void move_piece(Board *board, Location *curr_loc,
                Location *next_loc);

Board initialize_board(Piece *pieces[8][8], Player player_order[2]);

void render_board(Board *board);

void set_direction_rule(Direction direction, int i, int j);

void set_movement_condition_rule(MovementCondition condition, bool (*f)(Board*, Location, Location));

Piece *create_piece(char piece_symbol[8],
                           Movements allowed_movements[8],
                           int set_up_movement, Player player);

Movements *movement_allowed(Movements *allowed_movements,
                      const Location *curr_loc,
                      const Location *next_location,
                      int total_movement_rule);
