
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
          {0, 0, BLACK_ROOK},
          {0, 1, BLACK_KNIGHT},
          {0, 2, BLACK_BISHOP},
          {0, 3, BLACK_QUEEN},
          {0, 4, BLACK_KING},
          {0, 5, BLACK_BISHOP},
          {0, 6, BLACK_KNIGHT},
          {0, 7, BLACK_ROOK},
      },
      {
          {0, 0, BLACK_PAWN},
          {0, 0, BLACK_PAWN},
          {0, 1, BLACK_PAWN},
          {0, 2, BLACK_PAWN},
          {0, 3, BLACK_PAWN},
          {0, 4, BLACK_PAWN},
          {0, 5, BLACK_PAWN},
          {0, 6, BLACK_PAWN},
      },
      {
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
      },
      {
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
      },
      {
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
      },
      {
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
          {0, 0, "-"},
      },
      {
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
          {0, 0, WHITE_PAWN},
      },
      {
          {0, 0, WHITE_ROOK},
          {0, 0, WHITE_KNIGHT},
          {0, 0, WHITE_BISHOP},
          {0, 0, WHITE_QUEEN},
          {0, 0, WHITE_KING},
          {0, 0, WHITE_BISHOP},
          {0, 0, WHITE_KNIGHT},
          {0, 0, WHITE_ROOK},
      },
  };
  char someVal;

  while (1) {
    render_board(board);
    scanf("%s", &someVal);
  }
  return 0;
}
