
#include "chess.h"
#include <stdbool.h>
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
#define EMPTY_PEICE "-"

int main() {

    Movements king_movements[8] = {
        {1, DOWN, NOT_ATTACKED},
        {1, UP, NOT_ATTACKED},
        {1, LEFT, NOT_ATTACKED},
        {1, RIGHT, NOT_ATTACKED},
        {1, DIAGONAL_UP_RIGHT, NOT_ATTACKED},
        {1, DIAGONAL_UP_LEFT, NOT_ATTACKED},
        {1, DIAGONAL_DOWN_LEFT, NOT_ATTACKED},
        {1, DIAGIONAL_DOWN_RIGHT, NOT_ATTACKED},
    };

    Movements queen_movements[8] = {
        {7, DOWN},
        {7, UP},
        {7, LEFT},
        {7, RIGHT},
        {7, DIAGONAL_UP_RIGHT},
        {7, DIAGONAL_UP_LEFT},
        {7, DIAGONAL_DOWN_LEFT},
        {7, DIAGIONAL_DOWN_RIGHT},
    };

    Movements knight_movement[8] =  {
        {1, L_STAND_TOP_LEFT},
        {1, L_SLEEP_TOP_LEFT},
        {1, L_STAND_TOP_RIGHT},
        {1, L_SLEEP_TOP_RIGHT},
        {1, L_STAND_BOTTOM_LEFT},
        {1, L_SLEEP_BOTTOM_LEFT},
        {1, L_STAND_BOTTOM_RIGHT},
        {1, L_SLEEP_BOTTOM_RIGHT},
    };

    Movements black_pawn_movement[8] = {
        {1, DOWN},
        {2, DOWN, ONLY_ONCE},
        {1, DIAGONAL_DOWN_LEFT, OCCUPIED_BY_OPPS},
        {1, DIAGIONAL_DOWN_RIGHT, OCCUPIED_BY_OPPS}
    };

    Movements white_pawn_movement[8] = {
        {1, UP},
        {2, UP, ONLY_ONCE},
        {1, DIAGONAL_UP_LEFT, OCCUPIED_BY_OPPS},
        {1, DIAGONAL_UP_RIGHT, OCCUPIED_BY_OPPS}
    };

    Movements bishop_movements[8] = {
        {7, DIAGONAL_UP_LEFT},
        {7, DIAGONAL_UP_RIGHT},
        {7, DIAGONAL_DOWN_LEFT},
        {7, DIAGIONAL_DOWN_RIGHT}
    };

    Movements rook_movements[8] = {
        {7, UP},
        {7, DOWN},
        {7, LEFT},
        {7, RIGHT}
    };

    Movements empty_piece_movement[8] = {};

    Piece *black_king = create_piece(BLACK_KING, king_movements, 8, BLACK);
    Piece *black_queen = create_piece(BLACK_QUEEN, queen_movements, 8, BLACK);
    Piece *black_knight = create_piece(BLACK_KNIGHT, knight_movement, 8, BLACK);
    Piece *black_bishop = create_piece(BLACK_BISHOP, bishop_movements, 8, BLACK);
    Piece *black_rook = create_piece(WHITE_ROOK, rook_movements, 4, WHITE);

    Piece *white_queen = create_piece(WHITE_QUEEN, queen_movements, 8, WHITE);
    Piece *white_king = create_piece(WHITE_KING, king_movements, 8, WHITE);
    Piece *white_knight = create_piece(WHITE_KNIGHT, knight_movement, 8, WHITE);
    Piece *white_bishop = create_piece(WHITE_BISHOP, bishop_movements, 8, WHITE);
    Piece *white_rook = create_piece(WHITE_ROOK, rook_movements, 4, WHITE);

    set_direction_rule(UP, -1, 0);
    set_direction_rule(LEFT, 0, -1);
    set_direction_rule(RIGHT, 0, 1);
    set_direction_rule(DOWN, 1, 0);
    set_direction_rule(DIAGONAL_UP_LEFT, -1, -1);
    set_direction_rule(DIAGONAL_UP_RIGHT, -1, 1);
    set_direction_rule(DIAGONAL_DOWN_LEFT, 1, -1);
    set_direction_rule(DIAGIONAL_DOWN_RIGHT, 1, 1);
    set_direction_rule(L_STAND_TOP_LEFT, -2, -1);
    set_direction_rule(L_SLEEP_TOP_LEFT, -1, -2);
    set_direction_rule(L_STAND_TOP_RIGHT, -2, 1);
    set_direction_rule(L_SLEEP_TOP_RIGHT, -1, 2);
    set_direction_rule(L_STAND_BOTTOM_LEFT, 2, -1);
    set_direction_rule(L_SLEEP_BOTTOM_LEFT, -1, 2);
    set_direction_rule(L_STAND_BOTTOM_RIGHT, 2, 1);
    set_direction_rule(L_SLEEP_BOTTOM_RIGHT, 1, 2);

    Piece *board[8][8] = {
        {black_rook, black_knight, black_bishop, black_king, black_queen, black_bishop, black_knight, black_rook},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {white_rook, white_knight, white_bishop, white_king, white_queen, white_bishop, white_knight, white_rook}
    };

    // fills up the second upper row with black pawn
    for (int i = 0; i < 8; i++) {
        board[1][i] = create_piece(BLACK_PAWN, black_pawn_movement, 8, BLACK);
    }

    // fills up the second lower row with white pawn
    for (int i = 0; i < 8; i++) {
        board[6][i] = create_piece(WHITE_PAWN, white_pawn_movement, 8, WHITE);
    }

    // filling up those null values
    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = create_piece(EMPTY_PEICE, empty_piece_movement, 0, NEUTRAL);
        }
    }

    Location current_loc;
    Location next_loc;

    while (true) {
        render_board(board);
        scanf("%u %u %u %u", &current_loc.i, &current_loc.j, &next_loc.i, &next_loc.j);
        move_piece(board, &current_loc, &next_loc);
    }
    return 0;
}
