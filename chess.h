
#include <stdint.h>

struct Piece {
  int i;
  int j;
  char pieceUnicode[4];
};

void move_piece(struct Piece board[8][8], struct Piece currentLoc,
                struct Piece nextLocation);

void render_board(struct Piece board[8][8]);
