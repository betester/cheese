
#include "chess.h"
#include <stdio.h>

void move_piece(struct Piece (*board)[8], struct Piece currentLoc,
                struct Piece nextLocation) {}

void render_board(struct Piece (*board)[8]) {

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < sizeof(board[i]) / sizeof(struct Piece); j++) {
      printf("%s", board[i][j].pieceUnicode);
    }
    printf("\n");
  }
}
