#include<stdio.h>

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
void Move(int puzzle[], int n, int *zero)
{
    int tmp;

    tmp = puzzle[n];
    puzzle[n] = puzzle[*zero];
    puzzle[*zero] = tmp;

    *zero = n;
}

void Switch(int puzzle[],int n,int m)
{
    int tmp;

    tmp = puzzle[n];
    puzzle[n] = puzzle[m];
    puzzle[m] = tmp;
}

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

int checkpuzzle(int oripuzzle[])
{
    int count = 0;
    int zero;
    int tmp;
    int puzzle[9];
    int j;

    for(j=0;j<9;j++)
    {
        puzzle[j]=oripuzzle[j];
    }

    zero = locatesearch(puzzle,0);
    zero = zero%2;
    int i;

    for (i=0;i<8;i++)
    {
        if (puzzle[i]!=i+1)
        {
            tmp = locatesearch(puzzle,i+1);
            Switch(puzzle,i,tmp);
            count++;
        }
    }

    count = count%2;

    if (count==zero){
        return 1;
    }
    else
        return 0;
}

void initpuzzle(int puzzle[], int* zero)
{

    int i,j;
    for(i = 0;i < 9; i++)
    {
        puzzle[i]=0;
    }
    int k;
    int tmp = 0;

    while(1) {
        puts("-------");
        puts("|1|2|3|");
        puts("-------");
        puts("|4|5|6|");
        puts("-------");
        puts("|7|8|9|");
        puts("-------");

        for (k = 1; k < 9;) {
            tmp = 0;
            printf("%dを配置する場所の番号を入力してください。\n", k);
            scanf("%d", &tmp);

            if (tmp < 1 || tmp > 9) {
                puts("1から9までの整数を入力してください。");
            } else if (puzzle[tmp - 1] == 0) {
                puzzle[tmp - 1] = k;
                printf("%dを%d番に配置しました。\n", k, tmp);
                k++;

            } else {
                puts("その場所には配置できません。");
            }
        }
        if (checkpuzzle(puzzle)) break;
        else {
            printf("その配置はクリア不可能です。\n");
            for(j = 0;j < 9; j++)
            {
                puzzle[j]=0;
            }
        }
    }

        puts("配置が完了しました。");
        printpuzzle(puzzle);

        *zero = locatesearch(puzzle, 0);

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


int main()
{
	int puzzle[9];
	int tmp;
	int count = 0;
	int locate = 0;
	int zero;
	int cmd = 0;
while(1)
{	
    initpuzzle(puzzle,&zero);
    count = 0;
	puts("ゲームスタートです。");
	while(!FinishCheck(puzzle))	
	{
		tmp = 0;
		puts("動かしたい数字を入力してください。");
		scanf("%d" , &tmp);

		 if (0<tmp && tmp <9)
		{		
			locate = locatesearch(puzzle,tmp);
			
			if (locate < 0 || locate > 8)	break; //バグ対策

			if(possibletomove(locate,zero))
			{ 
				Move(puzzle, locate, &zero);
				printpuzzle(puzzle);
				count++;
			}
			
			else
			{
				puts("無効な入力です。");
			}
		}
		
		else 
		{
			puts("無効な入力です。");
		}
	}
		
	puts("おめでとうございます。ゲームクリアです。");
	printf("クリアまでにかかった手数は%d手です。\n", count);		
 	puts("もう一度ゲームを始める場合は1を、ゲームをやめる場合は1以外の数字を入力してください。");
	scanf("%d",&cmd);

	if (cmd != 1) break; 
}
	puts("お疲れ様でした。");
   return 0;

}
