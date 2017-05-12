#define MAXQP 180000
#define Psize 9

typedef struct
{
	int puzzle[Psize];
	int lastmove;
	int depth;
}Puzzle;


//配列の中身の有無はflagの0or1で表す
typedef struct
{
	Puzzle queue[MAXQP];
	int flag[MAXQP];
	int headQ;
	int tailQ;
}QueueP;

int emptyQP(QueueP* queueP);
int fullQP(QueueP* queueP);

void InitQP(QueueP* queueP)
{
	int i;
	for (i=0;i<MAXQP;i++)
	{	
		queueP->flag[i] = 0;
	}
	
	queueP->headQ = 0;
	queueP->tailQ = 0;
}

void putQP(QueueP* queueP, Puzzle* puzzle)
{
    if(!fullQP(queueP))
    {
	        queueP->queue[queueP->tailQ] = *puzzle;

	    queueP->flag[queueP->tailQ] = 1;
        if (queueP->tailQ!=MAXQP-1)
        {
            queueP->tailQ++;
        }
        else
        {
            queueP->tailQ = 0;
        }
    }
    else puts("これ以上キューに入れられません。");
}

void getQP(QueueP* queueP, Puzzle* puzzle)
{
    if(!emptyQP(queueP))
    {
		*puzzle = queueP->queue[queueP->headQ];
	    queueP->flag[queueP->headQ] = 0;
        if (queueP->headQ != MAXQP-1) {
            queueP->headQ++;
        }
        else
        {
            queueP->headQ = 0;
        }
    }
    else puts("キューの中身が存在しません。");
}

int emptyQP(QueueP* queueP)
{
	if(queueP->flag[queueP->headQ] ==  0)
	{
		printf("empty");
		return 1;

	}
	return 0;
}

int fullQP(QueueP* queueP)
{
	if(queueP->headQ == queueP->tailQ && queueP->flag[queueP->headQ] == 1)
	{
		printf("full");
		return 1;
	}
	return 0;
}
