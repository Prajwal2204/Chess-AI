
typedef struct board{
    int** layout;
    int side;
    int startX,startY,endX,endY;
    int move_num;
}board;

typedef struct piece_move{
    board** moves;
	int max;
}piece_move;



////A FEW GLOBAL VARIABLES TO TAKE NOTE OF.
extern int leafNode;
extern int AI_moveX;
extern int AI_moveY;
extern int AI_move_startX;
extern int AI_move_startY;
extern int check_flag;

