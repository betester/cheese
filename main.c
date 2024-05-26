
#include "chess.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

void pawn_reach_end_of_board_event(Board *board, const Player *player, const Location *last_loc) {
    Piece *piece = board->board[last_loc->i][last_loc->j];
    
    if (piece->piece_type != PAWN) {
        return;
    }

    // handle white pawn
    if (*player == WHITE && last_loc->i == 0) {
        //TODO: emit piece selection
        printf("You should be selecting something brother\n");
        return;
    }

    if (*player == BLACK && last_loc->i == 7) {
        //TODO: emit piece selection
        printf("You should be selecting something brother\n");
        return;
    }
}

void king_in_check_event(Board *board, const Player *player, const Location *last_loc) {
    // only the opposing king can be in check
    
    // this is really expensive but since it's 8 x 8 at most probably around 64 maybe... 
    // in one game chess probably around 60 to 100 movments at most so 6400 computation ¯\_(ツ)_/¯
    
    Location king_loc;
    bool found_the_king = false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *curr_piece = board->board[i][j];
            if (curr_piece->piece_type == KING && curr_piece->player != *player) {
                king_loc.i = i;
                king_loc.j = j;
                found_the_king = true;
                break;
            }
        }

        if (found_the_king) {
            break;
        }
    }

    // i should refactor this into a single function which is called is my piece under attack but im too lazy

    bool king_under_attack_bro = false;
    // checks whether the king is under attack
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *piece = board->board[i][j];
            Location loc = {i, j};
            if (piece != NULL && piece->player != *player) {
                Movements *movements = piece->allowed_movements;
                if (movement_allowed(board, movements, &loc, &king_loc, piece->set_up_movement) != NULL) {
                    king_under_attack_bro = true;
                    break;
                }
            }
        }
        if (king_under_attack_bro) {
            break;
        }
    }

    // so if it happens the player move the king, then it will be updated as well
    board->king_under_check = king_under_attack_bro;
}

void king_is_checkmated_event(Board *board, const Player *player, const Location *last_loc) {

    // this one should be refactored as well? find piece for example?
    
    Location king_loc;
    bool found_the_king;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *curr_piece = board->board[i][j];
            if (curr_piece->piece_type == KING && curr_piece->player != *player) {
                king_loc.i = i;
                king_loc.j = j;
                found_the_king = true;
                break;
            }
        }
        if (found_the_king) {
            break;
        }
    }

    Piece *king_piece = board->board[king_loc.i][king_loc.j];
    
    // there could also be a stalemate case 
    
    bool attacked_from_all_direction = true;

    for (int i = 0; i < king_piece->set_up_movement; i++) {

        Direction direction = king_piece->allowed_movements[i].direction;
        Location direction_offset = get_direction(direction);

        Location loc_to_be_checked; 

        loc_to_be_checked.i = direction_offset.i + king_loc.i;
        loc_to_be_checked.j = direction_offset.j + king_loc.j;

        bool this_direction_is_attacked = false;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Piece *piece = board->board[i][j];
                Location loc = {i, j};
                if (piece != NULL && piece->player != *player) {
                    Movements *movements = piece->allowed_movements;
                    this_direction_is_attacked = this_direction_is_attacked || (movement_allowed(board, movements, &loc, &loc_to_be_checked, piece->set_up_movement) != NULL);
                }
            }
        }

        attacked_from_all_direction = attacked_from_all_direction && this_direction_is_attacked;
    }

    // the problem with stalemate is that it only happens when other pieces could not move
    // TODO: handle stalemate case
    if (attacked_from_all_direction && board->king_under_check) {
        board->shahmat = true;
    }
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
        {7, DOWN, 0},
        {7, UP, 0},
        {7, LEFT, 0},
        {7, RIGHT, 0},
        {7, DIAGONAL_UP_RIGHT, 0},
        {7, DIAGONAL_UP_LEFT, 0},
        {7, DIAGONAL_DOWN_LEFT, 0},
        {7, DIAGIONAL_DOWN_RIGHT, 0},
    };

    Movements knight_movement[8] =  {
        {1, L_STAND_TOP_LEFT, 0},
        {1, L_SLEEP_TOP_LEFT, 0},
        {1, L_STAND_TOP_RIGHT, 0},
        {1, L_SLEEP_TOP_RIGHT, 0},
        {1, L_STAND_BOTTOM_LEFT, 0},
        {1, L_SLEEP_BOTTOM_LEFT, 0},
        {1, L_STAND_BOTTOM_RIGHT, 0},
        {1, L_SLEEP_BOTTOM_RIGHT, 0},
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
        {7, DIAGONAL_UP_LEFT, 0},
        {7, DIAGONAL_UP_RIGHT, 0},
        {7, DIAGONAL_DOWN_LEFT, 0},
        {7, DIAGIONAL_DOWN_RIGHT, 0}
    };

    Movements rook_movements[8] = {
        {7, UP, 0},
        {7, DOWN, 0},
        {7, LEFT, 0},
        {7, RIGHT, 0}
    };

    Piece *black_king = create_piece(KING, BLACK_KING, king_movements, 8, BLACK);
    Piece *black_queen = create_piece(QUEEN, BLACK_QUEEN, queen_movements, 8, BLACK);
    Piece *first_black_knight = create_piece(KNIGHT, BLACK_KNIGHT, knight_movement, 8, BLACK);
    Piece *second_black_knight = create_piece(KNIGHT, BLACK_KNIGHT, knight_movement, 8, BLACK);
    Piece *first_black_bishop = create_piece(BISHOP, BLACK_BISHOP, bishop_movements, 8, BLACK);
    Piece *second_black_bishop = create_piece(BISHOP, BLACK_BISHOP, bishop_movements, 8, BLACK);
    Piece *first_black_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);
    Piece *second_black_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);

    Piece *white_queen = create_piece(QUEEN, WHITE_QUEEN, queen_movements, 8, WHITE);
    Piece *white_king = create_piece(KING, WHITE_KING, king_movements, 8, WHITE);
    Piece *first_white_knight = create_piece(KNIGHT, WHITE_KNIGHT, knight_movement, 8, WHITE);
    Piece *second_white_knight = create_piece(KNIGHT, WHITE_KNIGHT, knight_movement, 8, WHITE);
    Piece *first_white_bishop = create_piece(BISHOP, WHITE_BISHOP, bishop_movements, 8, WHITE);
    Piece *second_white_bishop = create_piece(BISHOP, WHITE_BISHOP, bishop_movements, 8, WHITE);
    Piece *first_white_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);
    Piece *second_white_rook = create_piece(ROOK, WHITE_ROOK, rook_movements, 4, WHITE);

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

    add_move_event_handler(pawn_reach_end_of_board_event);
    add_move_event_handler(king_in_check_event);
    add_move_event_handler(king_is_checkmated_event);

    Piece *chess_board[8][8] = {
        {first_black_rook,  first_black_bishop, first_black_knight,  black_queen, black_king, second_black_knight, second_black_bishop, second_black_rook},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {first_white_rook, first_white_bishop, first_white_knight, white_queen, white_king, second_white_knight, second_white_bishop, second_white_rook}
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
