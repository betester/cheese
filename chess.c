
#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_PIECE 12
#define MAX_ROW 8
#define MAX_COL 8
#define MAX_PLAYER 2
#define MAX_MOVEMENT_CONDITION 4

Piece CHAR_MOVEMENTS[TOTAL_PIECE];
int DIRECTION_MOVEMENTS[TOTAL_PIECE][2];
bool (*MOVEMENT_CONDITION[MAX_MOVEMENT_CONDITION]) (Board *board, Location opps_location, Location our_location);

int total_piece_movement_set = -1;

void set_direction_rule(Direction direction, int i, int j) {
  DIRECTION_MOVEMENTS[direction][0] = i;
  DIRECTION_MOVEMENTS[direction][1] = j;
}

Piece *create_piece(PieceType piece_type,
                    char piece_symbol[8],
                    Movements allowed_movements[8],
                    int set_up_movement, 
                    Player player) {

  Piece *piece = (struct Piece*) malloc(sizeof(Piece));

  strcpy(piece->piece_symbol, piece_symbol);
  piece->set_up_movement = set_up_movement;
  piece->player = player;
  piece->piece_type = piece_type;

  for (int i = 0; i < set_up_movement; i++) {
    piece->allowed_movements[i] = allowed_movements[i];
  }

  piece->taken_move_state = NULL;

  return piece;
}


void set_movement_condition_rule(MovementCondition condition, bool (*f)(Board *, Location, Location)) {
  MOVEMENT_CONDITION[condition] = f;
}

Board initialize_board(Piece* pieces[8][8], Player* player_order) {

  Board board;

  for (int i = 0; i < MAX_PLAYER; i++) {
    board.player_order[i] = player_order[i];
  }

  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j <MAX_COL; j++) {
      board.board[i][j] = pieces[i][j];
    }
  }

  board.current_player = 0;

  return board;
}

Movements *movement_allowed(Board * board,
                            Movements *allowed_movements,
                            const Location *curr_loc, 
                            const Location *next_location, 
                            int total_movement_rule) {

  for (int i = 0; i < total_movement_rule; i++) {

    for (int j = 1; j <= allowed_movements[i].max_movement; j++) {
      // i dont know why i wrote it as column instead of rows
      int column_translation = curr_loc->i + DIRECTION_MOVEMENTS[allowed_movements[i].direction][0] * j;
      int row_translation = curr_loc->j + DIRECTION_MOVEMENTS[allowed_movements[i].direction][1] * j;

      // invalid can't move while there is a piece blocking the way
      bool occupied = board->board[column_translation][row_translation] != NULL;
      bool can_reach_loc = next_location->i == column_translation && next_location->j == row_translation;

      if (!can_reach_loc && occupied) {
        break;
      } else if (can_reach_loc) {
        return &allowed_movements[i];
      } 
    }
  }
  return NULL;
};

void __update_piece_movement_state(Piece *piece, const Location taken_step) {
  // i have no idea whehter i should save the pointer towards location or the copy, for now just the copy?
  piece->total_taken_movements += 1;
  piece->taken_move_state = realloc(piece->taken_move_state, piece->total_taken_movements);
  piece->taken_move_state[piece->total_taken_movements - 1] = taken_step;
}

void move_piece(Board *board, Location *curr_loc,
                Location *next_loc) {

  if (next_loc->i < 0 || next_loc->i >= MAX_ROW || next_loc->j < 0 ||
      next_loc->j >= MAX_COL) {
    printf("Out of bounds move, piece will not be moved");
    return;
  }

  Piece *curr_piece = board->board[curr_loc->i][curr_loc->j];
  Piece *next_piece = board->board[next_loc->i][next_loc->j];

  if (curr_piece == NULL) {
    printf("Cannot move empty piece\n");
    return; 
  }

  if (curr_piece->player != board->player_order[board->current_player]) {
    printf("player %d cannot make move because player %d should make the move\n", curr_piece->player, board->player_order[board->current_player]);
    return;
  }

  if (next_piece != NULL && curr_piece->player == next_piece->player) {
    printf("Cannot attack your own piece\n");
    return;
  }

  Movements *piece_movement = curr_piece->allowed_movements;

  if (piece_movement == NULL) {
    printf("No rule assigned for the piece %s\n", curr_piece->piece_symbol);
    return;
  }

  Movements *legal_move = movement_allowed(board, piece_movement, curr_loc, next_loc,
                                        curr_piece->set_up_movement);


  if (legal_move == NULL) {
    printf("Movement is not allowed\n");
    return;
  }

  printf("%d", legal_move->total_movement_condition);
  bool legal_move_meets_req = legal_move->total_movement_condition == 0;

  // surely there will be no or condition right?
  for (int i = 0; i < legal_move->total_movement_condition; i++) {
    legal_move_meets_req |= MOVEMENT_CONDITION[legal_move->movement_condition[i]](board, *next_loc, *curr_loc);
  }
   
  if (!legal_move_meets_req) {
    printf("Movement does not obey the requirement\n");
    return;
  }

  // making sure not memory leakagedge
  if (next_piece != NULL) {
    free(next_piece);
  }

  __update_piece_movement_state(curr_piece, *next_loc);

  board->board[next_loc->i][next_loc->j] = curr_piece;
  // either way, the piece is going to be removed right 
  board->board[curr_loc->i][curr_loc->j] = NULL;

  board->current_player = (board->current_player + 1) % MAX_PLAYER;
}

void render_board(Board *board) {
  printf("*");
  for (int i = 0; i < MAX_ROW; i++) {
    printf("%d", i);
  }
  printf("\n");

  for (int i = 0; i < MAX_COL; i++) {
    printf("%d", i);
    for (int j = 0; j < MAX_ROW; j++) {
      if (board->board[i][j] == NULL) {
      printf("-");
      } else {
        printf("%s", board->board[i][j]->piece_symbol);
      }
    }
    printf("\n");
  }
}
