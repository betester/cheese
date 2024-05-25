
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

bool occupied_by_opps_rule(Board *board, Location opp_location, Location our_location) {
    Piece *opps_piece = board->board[opp_location.i][opp_location.j];
    Piece *our_piece = board->board[our_location.i][our_location.j];

    return our_piece->player != opps_piece->player;
}

bool only_once_rule(Board *board, Location opp_location, Location our_location) {
    Piece *our_piece = board->board[our_location.i][our_location.j];
    return our_piece->taken_move_state == 0;
}

bool not_attacked_rule(Board *board, const Location opps_location, const Location our_location) {

    bool target_position_attacked = false;
    Piece *our_piece = board->board[our_location.i][our_location.j];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *piece = board->board[i][j];
            if (piece != NULL && piece->player != our_piece->player) {
                Movements *movements = piece->allowed_movements;
                if (movement_allowed(movements, &opps_location, &our_location, piece->set_up_movement) != NULL) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool en_passant_rule(Board *board, const Location opps_location, const Location our_location) {
    return true;
}

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

    set_movement_condition_rule(OCCUPIED_BY_OPPS, occupied_by_opps_rule);
    set_movement_condition_rule(ONLY_ONCE, only_once_rule);
    set_movement_condition_rule(NOT_ATTACKED, not_attacked_rule);

    Piece *chess_board[8][8] = {
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
        chess_board[1][i] = create_piece(BLACK_PAWN, black_pawn_movement, 8, BLACK);
    }

    // fills up the second lower row with white pawn
    for (int i = 0; i < 8; i++) {
        chess_board[6][i] = create_piece(WHITE_PAWN, white_pawn_movement, 8, WHITE);
    }

    // filling up those null values
    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            chess_board[i][j] = create_piece(EMPTY_PEICE, empty_piece_movement, 0, NEUTRAL);
        }
    }

    Player player_order[2] = {WHITE, BLACK}; 
    Board board = initialize_board(chess_board, player_order);

    Location current_loc;
    Location next_loc;

    while (true) {
        render_board(&board);
        scanf("%u %u %u %u", &current_loc.i, &current_loc.j, &next_loc.i, &next_loc.j);
        move_piece(&board, &current_loc, &next_loc);
    }
    return 0;
}
