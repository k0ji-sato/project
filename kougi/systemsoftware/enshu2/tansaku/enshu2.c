#include<stdio.h>
#include"queueI.h"
#include"queueS.h"

typedef struct{
    int puzzle[9];
    int lastmove;
}Puzzle;

void printpuzzle(int puzzle[])
{
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle[0],puzzle[1],puzzle[2]);
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle[3],puzzle[4],puzzle[5]);
    puts("-------");
    printf("|%d|%d|%d|\n",puzzle[6],puzzle[7],puzzle[8]);
    puts("-------");
}


void initpuzzle(int *puzzle, int* zero)
{
    puzzle[0]=8;
	puzzle[1]=1;
    puzzle[2]=7;
    puzzle[3]=6;
    puzzle[4]=3;
    puzzle[5]=4;
    puzzle[6]=2;
    puzzle[7]=0;
    puzzle[8]=5;
    printpuzzle(puzzle);

	*zero = 7;
}

void Move(int puzzle[], int locate, int* zero)
{
	int tmp;
	int i;

	tmp = puzzle[locate];
	puzzle[locate] = puzzle[*zero];
	puzzle[*zero] = tmp;

	*zero = locate;
}

int FinishCheck(int puzzle[])
{
	int i;
	
	for (i=0;i<8;i++)
	{
		if (puzzle[i] != i+1)
		{
			return 0;
		}
	}
	
	return 1; 
}

int locatesearch(int puzzle[],int n)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (puzzle[i] == n)
		{
			return i;
		} 	
	} 
return 9;
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

void copypuzzle(int originalpuzzle[],int copiedpuzzle[])
{
    int i;
    for (i=0;i<9;i++)
    {
        copiedpuzzle[i] = originalpuzzle[i];
    }
}

void SPS(int puzzle[], int zero)
{
    QueueS queueS;

    int tmp_puzzle[9];
    int locate;

    while(1)
    {
        getQS(&queueS, puzzle);
        copypuzzle(puzzle,tmp_puzzle);

        int i;
        for(i=0;i<9;i++)
        {
            locate = locatesearch(puzzle,i);
            if (possibletomove(locate,zero))
            {
                Move(tmp_puzzle,locate,&zero);
                if(FinishCheck(puzzle))
                {
                    copypuzzle(tmp_puzzle,puzzle);
                    return ;
                }
                putQS(&queueS,tmp_puzzle);
                copypuzzle(puzzle,tmp_puzzle);
            }
        }



    }


}


int main()
{
	int puzzle[9];
	int tmp_puzzle[9];
    int tmp;
	int count = 0;
	int locate = 0;
	int zero;
    QueueS queueS;

	initpuzzle(puzzle,&zero);

    SPS(puzzle,zero);

    printpuzzle(puzzle);

	printf("クリアまでにかかった手数は%d手です。\n", count);
    return 0;

}
