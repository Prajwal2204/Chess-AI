#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "hellomake.h"


int evaluate_board_test(board* chess){
    int score;
    for(int i = 2;i < 10;i++){
        for(int j =1;j < 9;j++){
            int pos = chess->layout[i][j];
                score = score + pos;
        }
    }
    return score;
}

int evaluate_board(board* chess){

	const int PawnTable[64] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
10	,	10	,	0	,	-10	,	-10	,	0	,	10	,	10	,
5	,	0	,	0	,	5	,	5	,	0	,	0	,	5	,
0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
5	,	5	,	5	,	10	,	10	,	5	,	5	,	5	,
10	,	10	,	10	,	20	,	20	,	10	,	10	,	10	,
20	,	20	,	20	,	30	,	30	,	20	,	20	,	20	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int KnightTable[64] = {
0	,	-10	,	0	,	0	,	0	,	0	,	-10	,	0	,
0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,
0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,
0	,	0	,	10	,	20	,	20	,	10	,	5	,	0	,
5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,
5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0		
};

const int BishopTable[64] = {
0	,	0	,	-10	,	0	,	0	,	-10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int RookTable[64] = {
-5	,	15	,	5	,	10	,	10	,	5	,	15	,	-5	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,
0	,	-10	,	5	,	10	,	10	,	5	,	-10	,	0		
};

const int MirrorTable[64] = {
56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
};

    int cp = 1;
    int kill_fact = 4;
    int score = 0;
    for(int i = 2;i < 10;i++){
        for(int j =1;j < 9;j++){
            int pos = chess->layout[i][j];
            int endpos = chess->layout[chess->endX][chess->endY];
            if(pos != -1 && pos != 0 && endpos != -1){
                switch(pos){
                    case -10:
                        score += (PawnTable[((i - 2)*8) + (j-1)]*cp);
                        score += abs(endpos) * kill_fact;
                        break;
                    case 10:
                        score += (PawnTable[MirrorTable[((i - 2)*8) + (j-1)]]*cp);
                        score += abs(endpos) *kill_fact;
                        break;
                    case -30:
                        score += (KnightTable[((i - 2)*8) + (j-1)]*cp);
                        score += abs(endpos)*kill_fact;
                        break;
                    case 30:
                        score += (KnightTable[MirrorTable[((i - 2)*8) + (j-1)]]*cp);
                        score += abs(endpos)* kill_fact;
                        break;
                    case -40:
                        score += (BishopTable[((i - 2)*8) + (j-1)]*cp);
                        score += abs(endpos)*kill_fact;
                        break;
                    case 40:
                        score += (BishopTable[MirrorTable[((i - 2)*8) + (j-1)]]*cp);
                        score += abs(endpos)* kill_fact;
                        break;
                    case -50:
                        score += (RookTable[((i - 2)*8) + (j-1)]*cp);
                        score += abs(endpos)* kill_fact;
                        break;
                    case 50:
                        score += (RookTable[MirrorTable[((i - 2)*8) + (j-1)]]*cp);
                        score += abs(endpos)* kill_fact;
                        break;
                    case 90:
                        score += abs(endpos) * kill_fact;
                        break;
                    case -90:
                        score += abs(endpos) * kill_fact;
                        break;
                    case 900:
                        break;
                    case -900:
                        break;
                    default:
                        break;
                    
                }
            }

        }
    }
    return score;
}


