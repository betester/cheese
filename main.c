
#include "chess.h"
#include <stdio.h>

#define WHITE_PAWN "♙"
#define WHITE_KNIGHT "♘"
#define WHITE_BISHOP "♗"
#define WHITE_ROOK "♖"
#define WHITE_QUEEN "♕"
#define WHITE_KING "♔"

#define BLACK_PAWN "♟︎"
#define BLACK_KNIGHT "♞"
#define BLACK_BISHOP "♝"
#define BLACK_ROOK "♜"
#define BLACK_QUEEN "♛"
#define BLACK_KING "♚"

int main() {

  char board[8][8][8] = {
      {
          BLACK_ROOK,
          BLACK_KNIGHT,
          BLACK_BISHOP,
          BLACK_QUEEN,
          BLACK_KING,
          BLACK_BISHOP,
          BLACK_KNIGHT,
          BLACK_ROOK,
      },
      {
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
          BLACK_PAWN,
      },
      {
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
      },
      {
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
      },
      {
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
      },
      {
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
          "-",
      },
      {
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
          WHITE_PAWN,
      },
      {
          WHITE_ROOK,
          WHITE_KNIGHT,
          WHITE_BISHOP,
          WHITE_QUEEN,
          WHITE_KING,
          WHITE_BISHOP,
          WHITE_KNIGHT,
          WHITE_ROOK,
      },
  };

  struct PieceMovement black_king_movement = {
      BLACK_KING,
      {
          {1, DOWN, NOT_ATTACKED},
          {1, UP, NOT_ATTACKED},
          {1, LEFT, NOT_ATTACKED},
          {1, RIGHT, NOT_ATTACKED},
          {1, DIAGONAL_UP_RIGHT, NOT_ATTACKED},
          {1, DIAGONAL_UP_LEFT, NOT_ATTACKED},
          {1, DIAGONAL_DOWN_LEFT, NOT_ATTACKED},
          {1, DIAGIONAL_DOWN_RIGHT, NOT_ATTACKED},
      },
  };

  struct PieceMovement white_king_movement = {
      WHITE_KING,
      {
          {1, DOWN, NOT_ATTACKED},
          {1, UP, NOT_ATTACKED},
          {1, LEFT, NOT_ATTACKED},
          {1, RIGHT, NOT_ATTACKED},
          {1, DIAGONAL_UP_RIGHT, NOT_ATTACKED},
          {1, DIAGONAL_UP_LEFT, NOT_ATTACKED},
          {1, DIAGONAL_DOWN_LEFT, NOT_ATTACKED},
          {1, DIAGIONAL_DOWN_RIGHT, NOT_ATTACKED},
      },
  };

  struct PieceMovement white_queen_movement = {
      WHITE_QUEEN,
      {
          {7, DOWN},
          {7, UP},
          {7, LEFT},
          {7, RIGHT},
          {7, DIAGONAL_UP_RIGHT},
          {7, DIAGONAL_UP_LEFT},
          {7, DIAGONAL_DOWN_LEFT},
          {7, DIAGIONAL_DOWN_RIGHT},
      },
  };

  struct PieceMovement black_queen_movement = {
      BLACK_QUEEN,
      {
          {7, DOWN},
          {7, UP},
          {7, LEFT},
          {7, RIGHT},
          {7, DIAGONAL_UP_RIGHT},
          {7, DIAGONAL_UP_LEFT},
          {7, DIAGONAL_DOWN_LEFT},
          {7, DIAGIONAL_DOWN_RIGHT},
      },
  };

  struct PieceMovement black_knight_movement = {
      BLACK_KNIGHT,
      {{1, L_MOVEMENT_TOP_LEFT},
       {1, L_MOVEMENT_TOP_RIGHT},
       {1, L_MOVEMENT_BOTTOM_LEFT},
       {1, L_MOVEMENT_BOTTOM_RIGHT}},
  };

  struct PieceMovement white_knight_movement = {
      WHITE_KNIGHT,
      {{1, L_MOVEMENT_TOP_LEFT},
       {1, L_MOVEMENT_TOP_RIGHT},
       {1, L_MOVEMENT_BOTTOM_LEFT},
       {1, L_MOVEMENT_BOTTOM_RIGHT}},
  };

  // think about en passant and  first 2 move later on
  struct PieceMovement black_pawn_movement = {
      BLACK_PAWN, {{1, DOWN}, {2, DOWN, ONLY_ONCE}}};
  struct PieceMovement white_pawn_movement = {WHITE_PAWN, {{1, DOWN}}};

  struct PieceMovement black_bishop_movement = {
      BLACK_BISHOP,
      {{7, DIAGONAL_UP_LEFT},
       {7, DIAGONAL_UP_RIGHT},
       {7, DIAGONAL_DOWN_LEFT},
       {7, DIAGIONAL_DOWN_RIGHT}},
  };

  struct PieceMovement white_bishop_movement = {
      WHITE_BISHOP,
      {{7, DIAGONAL_UP_LEFT},
       {7, DIAGONAL_UP_RIGHT},
       {7, DIAGONAL_DOWN_LEFT},
       {7, DIAGIONAL_DOWN_RIGHT}},
  };

  struct PieceMovement black_rook_movement = {
      BLACK_ROOK,
      {{7, UP}, {7, DOWN}, {7, LEFT}, {7, RIGHT}},
  };

  struct PieceMovement white_rook_movement = {
      WHITE_ROOK,
      {{7, UP}, {7, DOWN}, {7, LEFT}, {7, RIGHT}},
  };

  set_move_rule(black_king_movement);
  set_move_rule(white_king_movement);
  set_move_rule(black_queen_movement);
  set_move_rule(white_queen_movement);
  set_move_rule(black_knight_movement);
  set_move_rule(white_knight_movement);
  set_move_rule(black_pawn_movement);
  set_move_rule(white_pawn_movement);
  set_move_rule(black_bishop_movement);
  set_move_rule(white_bishop_movement);
  set_move_rule(black_rook_movement);
  set_move_rule(white_rook_movement);

  struct Location current_loc;
  struct Location next_loc;

  while (1) {
    render_board(board);
    scanf("%u %u %u %u", &current_loc.i, &current_loc.j, &next_loc.i,
          &next_loc.j);
    move_piece(board, &current_loc, &next_loc);
  }
  return 0;
}
