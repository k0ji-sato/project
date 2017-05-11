#include<stdio.h>
#include"queueI.h"


void printqueue(QueueI* queueI)
{
    int i;
    printf("flag  ");
    for(i=0;i<MAXQI;i++)
    {
        printf("%d  ",queueI->flag[i]);

    }
    printf("\n");

    printf("value ");
    int j;
    for(j=0;j<MAXQI;j++)
    {
        printf("%d  ",queueI->queue[j]);
    }
    printf("\n");
}


int main() {
    int n=0;
    int tmp;
    QueueI queueI;
    InitQI(&queueI);
    while (n != 9)
    {
        printf("putなら1を、getなら2入力してください。\n");
        scanf("%d", &n);

        if(n==1)
        {
         putQI(&queueI,1);
        }
        else if (n==2)
        {
            getQI(&queueI,&tmp);
        }

        else printf("無効なコマンドです\n");

        printqueue(&queueI);

    }

    return 0;
}
