#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 
void perft_testing(int depth , board* chess,int side);
int max(int depth , board* chess);
int min(int depth , board* chess);
void test_moves(piece_move* moves);
board* make_copy(board* chess,int move,int i,int j,int endX,int endY,int move_num);
piece_move* move_generation(board* chess,int move);
piece_move* move_generation_testing(board* chess,int move);
int validate_for_pawn(board* chess);
int validate_for_knight(board* chess);
int validate_for_queen(board* chess);
int validate_for_king(board* chess);
int validate_for_rook(board* chess);
int validate_for_bishop(board* chess);
int validate_input(board* chess);
int validate_move(board* chess);
int evaluate_board(board* chess);
int update_move(board* chess, int endX, int endY);
void render_board(board* chess);
board* array_init();
int gameOver(board* chess);
int king_checkmate(board* chess);
int minimax(board* chess,int depth,int side);
int max_test(int depth , int alpha,int beta, board* chess);
int min_test(int depth , int alpha,int beta, board* chess);
