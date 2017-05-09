#include<stdio.h>

void printpuzzle(char** puzzle[3][3][1])
{
    puts("-------");
    printf("|%s|%s|%s|",puzzle[1][1],puzzle[1][2],puzzle[1][3]);
    puts("-------");
    printf("|%s|%s|%s|",puzzle[2][1],puzzle[2][2],puzzle[2][3])
    puts("-------");
    printf("|%s|%s|%s|",puzzle[3][1],puzzle[3][2],puzzle[3][3])
    puts("-------");
}



void initpuzzle(char** puzzle[3][3][1])
{

    int i,j;
    for(i = 0;i < 3; i++)
    {
        for(j = 0; j < 3;j++)
        {
            puzzle[i][j] = NULL;
        }
    }

    puts("---------");
    puts("|①|②|③|");
    puts("---------");
    puts("|④|⑤|⑥|");
    puts("---------");
    puts("|⑦|⑧|⑨|");
    puts("---------");

    int k;
    char tmp[];
    for(k=1;k<9;)
    {
        printf("%dを配置する場所の番号を入力してください。¥n", k);
        scanf("%s¥n",tmp);

        if(atoi(tmp) < 1 || atoi(tmp) > 9)
        {
            puts("1から9までの整数を入力してください。");
        }

        else if (!strcmp(puzzle[tmp/3][tmp%3] , NULL))
        {
            *puzzle[tmp/3][tmp%3] =  &tmp;
            printf("%dを%s番に配置しました。¥n",k,&tmp);
            k++;
        }

        else
        {
            puts("すでに数字が存在します。");
        }
    }

    printpuzzle(puzzle);


}


int main()
{
	int* puzzle[3][3][1];

	initpuzzle(puzzle);
	
    return 0;
}
