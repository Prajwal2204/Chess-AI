#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "hellomake.h"



void perft_testing(int depth , board* chess,int side){

    if(depth == 0){
        leafNode++;
        return;
    }
    else{
        piece_move* moves = move_generation(chess,side);
		printf("%d\n",moves->max);
        int i = 0;
        while(i < moves->max){
            perft_testing(depth - 1,moves->moves[i],side);
			i++;
        }
		free(moves);
    }
}

int max_test(int depth , int alpha,int beta, board* chess){
    int bestSoFar = -999999;
	piece_move* moves;
    if(depth == 0 || check_flag){
		leafNode++;
		int ev = evaluate_board(chess);
        return ev;
    }
    else{
        moves = move_generation(chess,chess->side);
        int i = 0;
        for(i = 0;i < moves->max;i++){
				moves->moves[i]->side = !chess->side;
                int moveScore = min_test(depth - 1,alpha,beta,moves->moves[i]);
				
                if(moveScore > bestSoFar){
					AI_move_startX = moves->moves[i]->startX;
					AI_move_startY = moves->moves[i]->startY;
					AI_moveX = moves->moves[i]->endX;
					AI_moveY = moves->moves[i]->endY;  
                    bestSoFar = moveScore;
				}
				if(alpha < moveScore)
					alpha = moveScore;
				if(beta <= alpha){
					//free(moves);
					break;
				}
        }
	}
    return bestSoFar;
}


int min_test(int depth ,int alpha,int beta, board* chess){
    int bestSoFar = 999999;
	piece_move* moves;
    if(depth == 0 || check_flag){
		leafNode++;
        int ev = evaluate_board(chess);
        return ev;
    }
    else{
        moves = move_generation(chess,chess->side);
        int i = 0;
        for(i = 0;i<moves->max;i++){
				moves->moves[i]->side = !chess->side;
                int moveScore = max_test(depth - 1,alpha,beta,moves->moves[i]);
                if(moveScore < bestSoFar){
					AI_move_startX = moves->moves[i]->startX;
					AI_move_startY = moves->moves[i]->startY;
					AI_moveX = moves->moves[i]->endX;
					AI_moveY = moves->moves[i]->endY;
				    bestSoFar = moveScore;
				}
				if(beta > moveScore)
					beta = moveScore;
				if(beta <= alpha){
					//free(moves);
					break;
				}
        }
    }
    return bestSoFar;
        
}



int max(int depth , board* chess){
    int bestSoFar = -999999;
	piece_move* moves;
    if(depth == 0 || check_flag){
		int ev = evaluate_board(chess);
        return ev;
    }
    else{
        moves = move_generation(chess,chess->side);
        int i = 0;
        for(i = 0;i < moves->max;i++){
				moves->moves[i]->side = !chess->side;
                int moveScore = min(depth - 1,moves->moves[i]);
                if(moveScore > bestSoFar){
					AI_move_startX = moves->moves[i]->startX;
					AI_move_startY = moves->moves[i]->startY;
					AI_moveX = moves->moves[i]->endX;
					AI_moveY = moves->moves[i]->endY;  
                    bestSoFar = moveScore;
				}
        }
	}
    return bestSoFar;
}


int min(int depth , board* chess){
    int bestSoFar = 999999;
	piece_move* moves;
    if(depth == 0 || check_flag){
        int ev = evaluate_board(chess);
        return ev;
    }
    else{
        moves = move_generation(chess,chess->side);
        int i = 0;
        for(i = 0;i<moves->max;i++){
				moves->moves[i]->side = !chess->side;
                int moveScore = max(depth - 1,moves->moves[i]);
                if(moveScore < bestSoFar){
					AI_move_startX = moves->moves[i]->startX;
					AI_move_startY = moves->moves[i]->startY;
					AI_moveX = moves->moves[i]->endX;
					AI_moveY = moves->moves[i]->endY;
				    bestSoFar = moveScore;
				}
        }
    }
    return bestSoFar;
        
}



void test_moves(piece_move* moves){
	int max = moves->max;
	int i = 0;
	printf("total number of moves:%d\n",max);
	for(i = 0;i<max;i++){
		int x = moves->moves[i]->startX;
		int y = moves->moves[i]->startY;
		printf("move %d from x %d y %d\n",moves->moves[i]->layout[x][y],moves->moves[i]->startX,moves->moves[i]->startY);
		printf("\t to x %d y %d \n",moves->moves[i]->endX,moves->moves[i]->endY);
		render_board(moves->moves[i]);
	}
}


board* make_copy(board* chess,int move,int startX,int startY,int endX,int endY, int move_num){

    board* c = array_init();
	int i,j;
	for(i = 0;i<12;i++){
		for(j = 0;j<10;j++){
			c->layout[i][j] = chess->layout[i][j];
		}
	}
	c->side = move;
	c->startX = startX;
	c->startY = startY;
	c->endX = endX;
	c->endY = endY;
	c->move_num = move_num;

    return c;
}


piece_move* move_generation_testing(board* chess,int move){              // ////---------TESTING ONLYYYYYY!!!!------
    int max_moves = 256;
	piece_move* p_moves = malloc(sizeof(piece_move));
	p_moves->moves = (board**)malloc(sizeof(board));
	int top = 0;
    int tempX,tempY,i,j,num = 0;
	int move_num = chess->move_num;
	if(num < 256){               //checks for overflow
		for(i = 2; i<10;i++){
			for(j = 1; j<9;j++){
				int pos = chess->layout[i][j];
				if(abs(pos) == 10){ 
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);               // pawn
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);	
									render_board(c);
									num++;
									top++;
								}
						}
					}
				}
				else if(abs(pos) == 50){           // rook
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);
									render_board(c);
									top++;
									num++;
								}
						}
					}
				}
				else if(abs(pos) == 40){             //bishop
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);
									render_board(c);
									top++;
									num++;
								}
						}
					}
				}
				else if(abs(pos) == 30){             //knight
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);
									render_board(c);
									top++;
									num++;
								}
						}
					}
				}
				else if(abs(pos) == 90){              //queen
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);
									render_board(c);
									top++;
									num++;
								}
						}
					}
				}
				else if(abs(pos) == 900){                //king
					printf("for pos:%d startX %d and startY %d\n",pos,i,j);
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									//printf("\tpositions available x %d y %d\n",tempX,tempY);
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(c,tempX,tempY);
									render_board(c);
									top++;
									num++;
								}
						}
					}
				}
			}
    	}
	}
	else{
		printf("Max number of moves reached!");
	}	
	p_moves->max = top;
	printf("\nTotal number of available moves are:%d\n",num);
    return p_moves;
}

int king_checkmate(board* chess){
	int endpos = chess->layout[chess->endX][chess->endY];
	if(endpos == 900 && chess->side == 1){
		return 1;
	}
	else if(endpos == -900 && chess->side == 0){
		return 1;
	}
	return 0;
}

piece_move* move_generation(board* chess,int move){             
    int max_moves = 50;
	piece_move* p_moves = malloc(sizeof(piece_move));
	p_moves->moves = (board**)malloc(sizeof(board*) * max_moves);
	int top = 0;
    int tempX,tempY,i,j,num = 0;
	int move_num = chess->move_num;
	if(num < max_moves){               //checks for overflow
		for(i = 2; i<10;i++){
			for(j = 1; j<9;j++){
				int pos = chess->layout[i][j];
				if(abs(pos) == 10){                // pawn
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(c,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									num++;
									top++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
				else if(abs(pos) == 50){           // rook
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(c,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									top++;
									num++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
				else if(abs(pos) == 40){             //bishop
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(c,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									top++;
									num++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
				else if(abs(pos) == 30){             //knight
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(c,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									top++;
									num++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
				else if(abs(pos) == 90){              //queen
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(c,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									top++;
									num++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
				else if(abs(pos) == 900){                //king
					for(tempX = 2; tempX<10;tempX++){
						for(tempY = 1; tempY<9;tempY++){
							board* c = make_copy(chess,move,i,j,tempX,tempY,move_num);
							if(validate_input(c))
								if(validate_move(c)){
									p_moves->moves[top] = make_copy(chess,move,i,j,tempX,tempY,move_num);
									update_move(p_moves->moves[top],tempX,tempY);
									top++;
									num++;
									check_flag = king_checkmate(c);
									free(c);
								}
						}
					}
				}
			}
    	}
	}
	else{
		printf("----------------Max number of moves reached!-----------------\n");
		p_moves->max = top;
		return p_moves;
	}	
	p_moves->max = top;
    return p_moves;
}


int validate_for_pawn(board* chess){
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    
    if(pos == -10){            //computers turn
        if(chess->startX == 3)
        {
        	if(endpos==-1)
        		return 0;
            if(chess->endY==chess->startY && chess->endX==(chess->startX + 2) && endpos == 0)
                if(chess->layout[chess->startX + 1][chess->startY] == 0)
                    return 1;
        	if(chess->endY==chess->startY && chess->endX==(chess->startX + 1) && endpos == 0)
				return 1;
            if((chess->endX == chess->startX + 1) && (chess->endY == chess->startY + 1 || chess->endY == chess->startY - 1) && 
                endpos > 0 && endpos != -1)
                return 1;
			return 0;
		}
        	
		else
		{
			if(endpos==-1)
        		return 0;
			if(chess->endY==chess->startY && chess->endX==(chess->startX + 1) && endpos == 0)
				return 1;
            if((chess->endX == chess->startX + 1) && (chess->endY == chess->startY + 1 || chess->endY == chess->startY - 1) && 
                endpos > 0 && endpos != -1)
                return 1;
			return 0;	
		}
    }
    if(pos == 10){          // users turn
        if(chess->startX == 8)
        {
        	if(endpos==-1)
        		return 0;
            if(chess->endY==chess->startY && chess->endX==(chess->startX - 2) && endpos == 0)
                if(chess->layout[chess->startX - 1][chess->startY] == 0)
                    return 1;
        	if(chess->endY==chess->startY && chess->endX==(chess->startX - 1) && endpos == 0)		
				return 1;
            if((chess->endX == chess->startX - 1) && ((chess->endY == chess->startY - 1) || (chess->endY == chess->startY + 1)) && 
                endpos < 0 && endpos != -1)
                return 1;
			return 0;
		}
        	
		else
		{
			if(endpos==-1)
        		return 0;
			if(chess->endY==chess->startY && chess->endX==(chess->startX - 1) && endpos == 0)
				return 1;
            if((chess->endX == chess->startX - 1) && (chess->endY == chess->startY + 1 || chess->endY == chess->startY - 1) && 
                endpos < 0 && endpos != -1)
                return 1;
			return 0;	
		}
    }
    return 0;
}

int validate_for_knight(board* chess){               //knight or horse.
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];

    if(pos == 30){
    		if(endpos==-1)
        		return 0 ;
        	if(((chess->endY==(chess->startY-1) || chess->endY==(chess->startY+1)) && (chess->endX==(chess->startX-2) || chess->endX==(chess->startX+2))) 
        					|| ((chess->endX==(chess->startX-1) || chess->endX==(chess->startX+1)) && (chess->endY==(chess->startY-2) || chess->endY==(chess->startY+2))))
        		return 1;
			return 0;		
		
    }
    if(pos == -30){
            if(endpos==-1)
        		return 0 ;
        	if(((chess->endY==(chess->startY-1) || chess->endY==(chess->startY+1)) && (chess->endX==(chess->startX-2) || chess->endX==(chess->startX+2))) 
        					|| ((chess->endX==(chess->startX-1) || chess->endX==(chess->startX+1)) && (chess->endY==(chess->startY-2) || chess->endY==(chess->startY+2))))
        		return 1;
			return 0;
    }
    return 0;
}

int validate_for_queen(board* chess){               //queen stuff coz she a bish.
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    int flag = 0;
    if(abs(pos) == 90){
        flag=1;
		if(chess->move_num==1)
			return 0;
		else
		{	int k,j;
			if(endpos==-1)
				return 0;
			int i = 0;
			for(i=0; i<=8; i++)
			{
				if(chess->endX==chess->startX && chess->endY==(chess->startY-i)){       //left path
					for(k=chess->startY-1; k>(chess->endY); k--)
						if(chess->layout[chess->startX][k] != 0)
							return 0;	 
					return 1;
				}
				else if(chess->endX==chess->startX && chess->endY==(chess->startY+i))   //right path
				{
					for(k=chess->startY+1; k<(chess->endY); k++)
						if(chess->layout[chess->startX][k] != 0)
							return 0;		 
					return 1;
				}
				else if(chess->endY==chess->startY && chess->endX==(chess->startX-i)) //top path
				{
					for(k=chess->startX-1; k>(chess->endX); k--)
						if(chess->layout[k][chess->startY] != 0)
							 return 0; 
					return 1;
				}
				else if(chess->endY==chess->startY && chess->endX==(chess->startX+i)) //bottom path
				{
					for(k=chess->startX+1; k<(chess->endX); k++)
						if(chess->layout[k][chess->startY] != 0)
							return 0;	 
					return 1;
				}
				if(chess->endX==(chess->startX-i) && chess->endY==(chess->startY+i))   //top right
				{
					for(k=chess->startX-1, j=chess->startY+1; k>chess->endX, j<chess->endY; k--, j++)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX-i) && chess->endY==(chess->startY-i))   //top left
				{
					for(k=chess->startX-1, j=chess->startY-1; k>chess->endX, j>chess->endY; k--, j--)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX+i) && chess->endY==(chess->startY-i))   //bottom left
				{
					for(k=chess->startX+1, j=chess->startY-1; k<chess->endX, j>chess->endY; k++, j--)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX+i) && chess->endY==(chess->startY+i))   //bottom right
				{
					for(k=chess->startX+1, j=chess->startY+1; k<chess->endX, j<chess->endY; k++, j++)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}			
				else
					flag=0;
			}
			if(flag==0)
				return 0;
		}
    }
}

int validate_for_king(board* chess){               //king.
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    int flag;
    if(abs(pos) == 900){
        flag=1;
		if(chess->move_num==1)
			return 0;
		else
		{
			if(endpos==-1)
				return 0;
			for(int i=0; i<=8; i++)
			{
				if((chess->endX==chess->startX && (chess->endY==(chess->startY-1) || chess->endY==(chess->startY+1))) 
							|| (chess->endY==chess->startY && (chess->endX==(chess->startX-1) || chess->endX==(chess->startX+1))))
				{	return 1;	}
				if(((chess->endX==(chess->startX-1) || chess->endX==(chess->startX+1)) && (chess->endY==(chess->startY-1) || chess->endY==(chess->startY+1)))
							|| ((chess->endY==(chess->startY-1) || chess->endY==(chess->startY+1)) && (chess->endX==(chess->startX-1) || chess->endX==(chess->startX+1))))
				{	return 1;	}				
				else
					flag=0;
			}
			if(flag==0)
				return 0;
		}
    }
    return 0;
}


int validate_for_rook(board* chess){               //rookkkkk
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    int flag;

    if(abs(pos) == 50){
        if(chess->move_num==1)
			return 0;
		else
		{
			int k;
			if(endpos==-1)
				return 0;
			for(int i=1; i<=8; i++)
			{
				flag=1;
				if(chess->endX==chess->startX && chess->endY==(chess->startY-i))   //left path
				{
					for(k=chess->startY-1; k>(chess->endY); k--)
					{
						if(chess->layout[chess->startX][k] != 0)
						{	return 0;
						}
					}	
					if(flag==0)
						break;		 
					return 1;
				}
				else if(chess->endX==chess->startX && chess->endY==(chess->startY+i)) //right path
				{
					for(k=chess->startY+1; k<(chess->endY); k++)
					{
						if(chess->layout[chess->startX][k] != 0)
						{	flag=0;
							break;
						}
					}	
					if(flag==0)
						break;		 
					return 1;
				}
				else if(chess->endY==chess->startY && chess->endX==(chess->startX-i)) //top path
				{
					for(k=chess->startX-1; k>(chess->endX); k--)
					{
						if(chess->layout[k][chess->startY] != 0)
						{
							 return 0;
						}
					}	
					if(flag==0)
						break;	 
					return 1;
				}
				else if(chess->endY==chess->startY && chess->endX==(chess->startX+i)) //bottom path
				{
					for(k=chess->startX+1; k<(chess->endX); k++)
					{
						if(chess->layout[k][chess->startY] != 0)
						{	flag=0;
							break;
						}
					}	
					if(flag==0)
						break;		 
					return 1;
				}
								
				else
					flag=0;
			}
			if(flag==0)
				return 0;
		}
    }
    return 0;
}


int validate_for_bishop(board* chess){               //bishop
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    int flag;

    if(abs(pos) == 40){
        flag=1;
		if(chess->move_num==1)
			return 0;
		else
		{	int k, j;
			if(endpos==-1)
				return 0;
			for(int i=0; i<=8; i++)
			{
				if(chess->endX==(chess->startX-i) && chess->endY==(chess->startY+i))   //top right
				{
					for(k=chess->startX-1, j=chess->startY+1; k>chess->endX, j<chess->endY; k--, j++)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX-i) && chess->endY==(chess->startY-i))   //top left
				{
					for(k=chess->startX-1, j=chess->startY-1; k>chess->endX, j>chess->endY; k--, j--)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX+i) && chess->endY==(chess->startY-i))   //bottom left
				{
					for(k=chess->startX+1, j=chess->startY-1; k<chess->endX, j>chess->endY; k++, j--)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}
				else if(chess->endX==(chess->startX+i) && chess->endY==(chess->startY+i))   //bottom right
				{
					for(k=chess->startX+1, j=chess->startY+1; k<chess->endX, j<chess->endY; k++, j++)
						if(chess->layout[k][j] != 0)
							return 0;
					return 1;
				}			
				else
					flag=0;
			}
			if(flag==0)
				return 0;
		}
    }
    return 0;
}


int validate_input(board* chess){
    int pos = chess->layout[chess->startX][chess->startY];
	int endpos = chess->layout[chess->endX][chess->endY];
    if(chess->side == 0 && pos != 0 && endpos != -1){             // when users turn
        if(pos > 0 && endpos <= 0)
            return 1;
		else
        	return 0;
    }
    else if(chess->side == 1 && pos != 0 && pos != -1){           /// computers turn
        if(pos < 0 && endpos >= 0)
            return 1;
		else
        	return 0;
    }
    else{
        return 0;
    }
}


int validate_move(board* chess)
{
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[chess->endX][chess->endY];
    if(pos==-1)
    	return 0;
    if(abs(pos) == 10)
    {
        return validate_for_pawn(chess);
    }
    else if(abs(pos)==30)
    {
    	return validate_for_knight(chess);
	}	

    else if(abs(pos) == 40){
        return validate_for_bishop(chess);
    }
    else if(abs(pos) == 50){
        return validate_for_rook(chess);
    }
    else if(abs(pos) == 90){
        return validate_for_queen(chess);
    }
    else if(abs(pos) == 900){
        return validate_for_king(chess);
    }
    else{
        return 0;
    }
}



int update_move(board* chess, int endX, int endY){
    int pos = chess->layout[chess->startX][chess->startY];
    int endpos = chess->layout[endX][endY];
    int flag = 0;
    if(chess->side == 0){
        if(pos > 0 && endpos <= 0 && endpos != -1){
            flag = 1;
		}
    }
    else{
        if(pos < 0 && pos != -1 && endpos >= 0){
            flag = 1;
		}
    }
	if(flag == 1){
		chess->layout[endX][endY] = chess->layout[chess->startX][chess->startY];
    	chess->layout[chess->startX][chess->startY] = 0;
		return 1;
	}
	return 0;
    
}


void render_board(board* chess){
    for(int i=-1;i<12;i++){
        if(i == -1){
            printf("\t\t");
            for(int a = 0;a<10;a++){
                printf("%d\t",a);
            }
            printf("\n");
        }
        else{
            printf("\t%d\t\t",i);
            for(int j = 1;j<10;j++){
                    if(chess->layout[i][j] != -1)
                        printf("%d\t",chess->layout[i][j]);
                    //printf("%d\t",piece_name(chess[i][j]));
            }
            printf("\n\n");
        }
    }
}

board* array_init(){

    int elements[]={-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
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
                    -1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1                       
    };

	int elements_test[]={-1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
                    -1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
                    -1,-50, -30, -40,-90, -900, -40, -30, -50,-1,
                    -1,-10, -10, 0,0,  -10, -10, -10, -10,-1,
                    -1, 0 ,  0 ,  -10 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
                    -1, 0 ,  0 ,  -10 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
                    -1, 0 ,  0 ,  0 ,  10 ,  0 ,  0 ,  0 ,  0 ,-1,
                    -1, 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,-1,
                    -1, 10,  10,  10,  0,  10,  10,  10,  10,-1,
                    -1, 50,  30,  40,  90, 900,  40,  30,  50,-1,
                    -1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1,
                    -1, -1,  -1,  -1, -1,  -1 , -1 , -1 , -1 ,-1                       
    };

    board* chess = malloc(sizeof(board));
    chess->startX = chess->startY = chess->endX = chess->endY = 0;
    chess->side = 0;            // 0 is player side and 1 is computer side.
    chess->move_num = 1;       
    chess->layout = (int**)malloc(12*sizeof(int*));
    for(int i = 0;i<12;i++){
        chess->layout[i] = (int*)malloc(10*sizeof(int));
    }
    int k = 0;
    for(int i = 0;i<12;i++){
        for(int j = 0;j<10;j++){
            chess->layout[i][j] = elements[k];
            k++;
        }
    }
    return chess;
}

