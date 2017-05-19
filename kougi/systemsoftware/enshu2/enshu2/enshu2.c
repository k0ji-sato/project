#include<stdio.h>
#include"queueP.h"


void printpuzzle(Puzzle* puzzle)
{
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle->puzzle[0],puzzle->puzzle[1],puzzle->puzzle[2]);
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle->puzzle[3],puzzle->puzzle[4],puzzle->puzzle[5]);
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle->puzzle[6],puzzle->puzzle[7],puzzle->puzzle[8]);
    puts("-------");
}

int locatesearch(Puzzle puzzle,int n)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (puzzle.puzzle[i] == n)
        {
            return i;
        }
    }
    return 9;
}

int checkpuzzle(Puzzle puzzle)
{
    int zero;
    zero = locatesearch(puzzle,0);

    int count = 0;

    int i;
    for (i=0;i<9;i++)
    {
        if 

    }


}

void initpuzzle(Puzzle* puzzle, int* zero)
{
    puzzle->puzzle[0]=8;
    puzzle->puzzle[1]=1;
    puzzle->puzzle[2]=7;
    puzzle->puzzle[3]=6;
    puzzle->puzzle[4]=3;
    puzzle->puzzle[5]=4;
    puzzle->puzzle[6]=2;
    puzzle->puzzle[7]=0;
    puzzle->puzzle[8]=5;

    puzzle->lastmove = 0;
    puzzle->depth = 0;
    printpuzzle(puzzle);

}

void Move(Puzzle* puzzle, int locate, int* zero)
{
	int tmp;

	tmp = puzzle->puzzle[locate];
    puzzle->puzzle[locate] = puzzle->puzzle[*zero];
    puzzle->puzzle[*zero] = tmp;

    puzzle->depth++;
}

int FinishCheck(Puzzle puzzle)
{
	int i;
	for (i=0;i<8;i++)
	{
		if (puzzle.puzzle[i] != i+1)
		{
			return 0;
		}
	}
	
	return 1; 
}





int possibletomove(int locate, int zero)
{
    if (locate == zero + 1 && zero%3 != 2)
        return 1;
    if (locate == zero - 1 && zero%3 != 0)
        return 1;
    if (locate == zero + 3 && zero/3 != 2)
        return 1;
    if (locate == zero - 3 && zero/3 != 0)
        return 1;

    return 0;
}


int SPS(Puzzle puzzle)
{
    QueueP queueP;
    Puzzle tmp_puzzle;
    int zero;
    int locate;
    int countg=0;
    int countp=0;
    InitQP(&queueP);
    putQP(&queueP,&puzzle);

    while(!emptyQP(&queueP) && !fullQP(&queueP))
    {
        getQP(&queueP, &puzzle);
        countg++;
        zero = locatesearch(puzzle, 0);
        tmp_puzzle = puzzle;
        int i;
        for(i=1;i<9;i++)
        {
            locate = locatesearch(tmp_puzzle,i);
            if (possibletomove(locate,zero) && i != tmp_puzzle.lastmove)
            {
                Move(&tmp_puzzle,locate,&zero);
                tmp_puzzle.lastmove=i;
                //printf("depth=%d\n",tmp_puzzle.depth);
                if(FinishCheck(tmp_puzzle))
                {
                    printpuzzle(&tmp_puzzle);
                    //printf("put%d回\n",countp);
                    //printf("get%d回\n",countg);
                    printf("headQ %d\n",queueP.headQ);
                    printf("tailQ %d\n",queueP.tailQ);
                    return tmp_puzzle.depth;
                }
                putQP(&queueP,&tmp_puzzle);
                countp++;
                tmp_puzzle = puzzle;
            }
        }



    }
    printf("探索できませんでした");
    return 0;

}


int main()
{
	Puzzle puzzle;
	int zero;
    int depth;

	initpuzzle(&puzzle,&zero);

    depth = SPS(puzzle);


	printf("クリアまでにかかった手数は%d手です。\n", depth);

    return 0;

}
