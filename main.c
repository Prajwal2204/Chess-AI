#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "hellomake.h"

int AI_moveX;
int AI_moveY;

/*
BASIC LAYOUT OF THE CHESS BOARD===>

-Minus represents the opponent(black).
-Plus represents the player(white).
-The rest of the positions are filled with 0
-a buffer is left for -1 around all elements because 
    this is helpful while finding all possible moves.
-0 is player turn and 1 is computer turn.

     a    b    c    d    e    f    g    h
1    -50  -30  -30  -90  -900 -30  -30  -50
2    -10  -10  -10  -10  -10  -10  -10  -10
3
4
5
6     
7    10   10   10   10   10   10   10   10
8    50   30   30   90   900  30   30   50


-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
-1,-50, -30, -40,-90, -900, -40, -30, -50,-1,
-1,-10, -10, -10,-10,  -10, -10, -10, -10,-1,
-1, 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
-1, 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
-1, 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
-1, 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
-1, 10,  10,  10,  10,  10,  10,  10,  10,-1,
-1, 50,  30,  40,  90, 900,  40,  30,  50,-1,
-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1, 

king = 900
queen = 90
rook = 50
bishop = 40
knight = 30
pawn = 10

}
*/
//A FEW GLOBAL VARIABLES.
int leafNode;
int AI_move_startX;
int AI_move_startY;
int check_flag;


int main(void){
    board* chess = array_init(chess);
    int count = 0;
    check_flag = 0;
    render_board(chess);

    while(!king_checkmate(chess)){
        printf("------------------------------------------------------\n");
        chess->side = count%2;
        if(!chess->side){
            int endX,endY;
            printf("Number representation of chess characters\n");
			printf("10->Pawn \n30->Knight \n40->Bishop \n50->Rook \n90->Queen \n900->King");
            printf("\nIts Your Turn!");
            printf("\nEnter Your Move(from):");
            scanf("%d %d",&chess->startX,&chess->startY);
            printf("\nmove %d to?:",chess->layout[chess->startX][chess->startY]);
            scanf("%d %d",&endX,&endY);
            chess->endX = endX;
            chess->endY = endY;


            if(validate_input(chess)){
                if(validate_move(chess)){
                    update_move(chess,endX,endY);
                    count++;
                    chess->move_num++;
                }
                else
                {
                	printf("INVALID MOVE:Move Validation is Wrong!\n\n");
                }	
                	    
            }
            else{
                printf("INVALID MOVE:Input Validation is Wrong!\n\n");
            }
                
        }
        else{
            leafNode = 0;
            AI_moveX = 1;
            AI_moveY = 1;
            AI_move_startX = 0;
            AI_move_startY = 0;
            
            printf("\nIts the computers turn!!\n");
            piece_move* moves;
            
            int AI_move;

            /*
            int a = 0;
            board* chess_copy;
            chess_copy = make_copy(chess,1,chess->startX,chess->startY,chess->endX,chess->endY,chess->move_num);
            moves = move_generation(chess_copy,1);
            test_moves(moves);
            printf("------------------------------------------\n");
            count++;
            chess->move_num++;
            //*/

           ///*
            if(chess->move_num == 2){
                int begin_moveX,begin_moveY,end_moveX,end_moveY;
                piece_move* moves_for_begin;
                moves_for_begin = move_generation(chess,1);

                srand(time(0));
                int num = (rand() % moves_for_begin->max-1) + 1;
                printf("The first move is a random move in this AI\n");
                printf("The Random number is %d out of %d moves\n",num,moves_for_begin->max);
                chess->startX = moves_for_begin->moves[num]->startX;
                chess->startY = moves_for_begin->moves[num]->startY;
                end_moveX = moves_for_begin->moves[num]->endX;
                end_moveY = moves_for_begin->moves[num]->endY;
                update_move(chess,end_moveX,end_moveY);
                free(moves_for_begin);
            }
            else{
                int depth = 3;
                board* chess_copy;
                chess_copy = make_copy(chess,1,chess->startX,chess->startY,chess->endX,chess->endY,chess->move_num);
                printf("The Number of possibilities at a depth of %d is ",depth);
                //perft_testing(3,chess_copy,1);
                printf("%d nodes\n",leafNode);

                
                ///*
                leafNode = 0;
                
                do{
                    //AI_move = max(depth,chess_copy);
                    AI_move = max_test(depth,-99999,99999,chess_copy);
                    chess->startX = AI_move_startX;
                    chess->startY = AI_move_startY;
                    depth--;
                    if(depth == 0)
                        break;
                }
                while(!update_move(chess,AI_moveX,AI_moveY));
                
                
                printf(" The number of leafnodes in alpha beta pruning is:%d\n",leafNode);
                //*/
                printf("The starting X and Y of the AI is %d %d\n",AI_move_startX,AI_move_startY);
                free(chess_copy);
            }
            printf("max score on this run is %d\n",AI_move);

            count++;
            chess->move_num++;

            //*/
        }

    

        render_board(chess);
    }

    printf("The Game is Over!!!!!\n");

}
