#include<stdio.h>

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


void initpuzzle(int puzzle[], int* zero)
{

    int i,j;
    for(i = 0;i < 9; i++)
    {
        puzzle[i]=0;
    }

    puts("-------");
    puts("|1|2|3|");
    puts("-------");
    puts("|4|5|6|");
    puts("-------");
    puts("|7|8|9|");
    puts("-------");

    int k;
    int tmp = 0;
    for(k=1;k<9;)
    {
	tmp = 0;
        printf("%dを配置する場所の番号を入力してください。\n", k);
        scanf("%d",&tmp);

        if(tmp < 1 || tmp > 9)
        {
            puts("1から9までの整数を入力してください。");
        }

        else if (puzzle[tmp-1] == 0)
        {
            puzzle[tmp-1] =  k;
            printf("%dを%d番に配置しました。\n",k,tmp);
            k++;

        }

        else
        {
            puts("その場所には配置できません。");
        }
    }
    puts("配置が完了しました。");
    printpuzzle(puzzle);

	for (j=0 ;j<9;j++)
	{
		if(puzzle[j]==0)
		{
			*zero = j;
			break;
		}
	}	 
}

void Move(int puzzle[], int n, int* zero)
{
	int tmp;
	int i;

	tmp = puzzle[n];
	puzzle[n] = puzzle[*zero];
	puzzle[*zero] = tmp;

	*zero = n;
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
	if(locate == zero+1 || locate == zero-1 || locate == zero + 3 || locate == zero - 3)
	{
		return 1; 
	}	
	
	return 0;
}

int main()
{
	int puzzle[9];
	int tmp;
	int count = 0;
	int locate = 0;
	int zero;

	initpuzzle(puzzle,&zero);
	
	puts("ゲームスタートです。");
	while(!FinishCheck(puzzle))	
	{
		tmp = 0;
		printf("動かしたい数字を入力してください。\n");
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
    return 0;

}
