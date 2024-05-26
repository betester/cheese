
#include "chess.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

bool occupied_by_opps_rule(Board *board, Location opp_location, Location our_location) {
    Piece *opps_piece = board->board[opp_location.i][opp_location.j];
    Piece *our_piece = board->board[our_location.i][our_location.j];

    return opps_piece != NULL && our_piece->player != opps_piece->player;
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
                if (movement_allowed(board, movements, &opps_location, &our_location, piece->set_up_movement) != NULL) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool en_passant_rule(Board *board, const Location next_loc, const Location curr_loc) {

    // next loc has to be empty
    if (board->board[next_loc.i][next_loc.j] != NULL) {
        return false;
    }

    Piece* curr_piece = board->board[curr_loc.i][curr_loc.j];
    Piece* next_piece;

    if (curr_piece->player == WHITE) {
        next_piece = board->board[next_loc.i + 1][next_loc.j];
    } else {
        next_piece = board->board[next_loc.i - 1][next_loc.j];
    }

    if (next_piece->piece_type != PAWN || next_piece->player == curr_piece->player) {
        return false;
    }

    if (next_piece->total_taken_movements > 1) {
        return false;
    }

    Location last_loc_next_piece = next_piece->taken_move_state[0];
    
    // has to take the two step movements

    int step_diff = last_loc_next_piece.i - next_loc.i;

    if (step_diff >= -1 || step_diff <= 1) {
        return false;
    }

    return true;
}

int main() {

    Movements king_movements[8] = {
        {1, DOWN, 1, {NOT_ATTACKED}},
        {1, UP, 1, {NOT_ATTACKED}},
        {1, LEFT, 1, {NOT_ATTACKED}},
        {1, RIGHT, 1, {NOT_ATTACKED}},
        {1, DIAGONAL_UP_RIGHT, 1, {NOT_ATTACKED}},
        {1, DIAGONAL_UP_LEFT, 1, {NOT_ATTACKED}},
        {1, DIAGONAL_DOWN_LEFT, 1, {NOT_ATTACKED}},
        {1, DIAGIONAL_DOWN_RIGHT, 1, {NOT_ATTACKED}},
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
        {1, DOWN, 0},
        {2, DOWN, 1, {ONLY_ONCE}},
        {1, DIAGONAL_DOWN_LEFT, 2, {OCCUPIED_BY_OPPS, EN_PASSANT}},
        {1, DIAGIONAL_DOWN_RIGHT, 2, {OCCUPIED_BY_OPPS, EN_PASSANT}}
    };

    Movements white_pawn_movement[8] = {
        {1, UP, 0},
        {2, UP, 1, {ONLY_ONCE}},
        {1, DIAGONAL_UP_LEFT, 2, {OCCUPIED_BY_OPPS, EN_PASSANT}},
        {1, DIAGONAL_UP_RIGHT, 2, {OCCUPIED_BY_OPPS, EN_PASSANT}}
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

    Piece *black_king = create_piece(KING, BLACK_KING, king_movements, 8, BLACK);
    Piece *black_queen = create_piece(QUEEN, BLACK_QUEEN, queen_movements, 8, BLACK);
    Piece *black_knight = create_piece(KNIGHT, BLACK_KNIGHT, knight_movement, 8, BLACK);
    Piece *black_bishop = create_piece(BISHOP, BLACK_BISHOP, bishop_movements, 8, BLACK);
    Piece *black_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);

    Piece *white_queen = create_piece(QUEEN, WHITE_QUEEN, queen_movements, 8, WHITE);
    Piece *white_king = create_piece(KING, WHITE_KING, king_movements, 8, WHITE);
    Piece *white_knight = create_piece(KNIGHT, WHITE_KNIGHT, knight_movement, 8, WHITE);
    Piece *white_bishop = create_piece(BISHOP, WHITE_BISHOP, bishop_movements, 8, WHITE);
    Piece *white_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);

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
    set_movement_condition_rule(EN_PASSANT, en_passant_rule);

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
        chess_board[1][i] = create_piece(PAWN, BLACK_PAWN, black_pawn_movement, 8, BLACK);
    }

    // fills up the second lower row with white pawn
    for (int i = 0; i < 8; i++) {
        chess_board[6][i] = create_piece(PAWN, WHITE_PAWN, white_pawn_movement, 8, WHITE);
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
