
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
  struct Piece board[8][8] = {
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
      {
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
          {0, 0, BLACK_KING},
      },
  };
  char someVal;

  while (1) {
    render_board(board);
    scanf("%s", &someVal);
  }
  return 0;
}
