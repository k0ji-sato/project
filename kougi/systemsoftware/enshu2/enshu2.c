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


void initpuzzle(int puzzle[])
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
        printf("%dを配置する場所の番号を入力してください。\n", k);
        tmp = 0;

        scanf("%d",&tmp);

        if(tmp < 1 || tmp > 9)
        {
            puts("1から9までの整数を入力してください。");
        }

        else if (puzzle[tmp] == 0)
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

}


int main()
{
	int puzzle[9];

	initpuzzle(puzzle);
	
    return 0;
}
