#define MAXQS 100;
#define Psize 9;

//配列の中身の有無はflagの0or1で表す
typedef struct
{
	int queue[Psize][MAXQS];
	int flag[MAXQS];
	int headQ;
	int tailQ;
}QueueS

void InitQS(QueueS* queueS)
{
	int i;
	for (i=0;i<MAXQS;i++)
	{	
		queueS->flag[i] = 0;		
	}
	
	queueI->headQ = 0;
	queueI->tailQ = 0;
}

void putQS(QueueS* queueS, int puzzle[])
{
	int i;
	for (i=0;i<Psize;i++)
	{
	queueI->queue[i][queueI->tailQ] = puzzle[i];
	}
	flag[queue->tailQ] = 1;
	tailQ++;
} 

void getQS(QueueS* queueS, int puzzle[])
{	
	int i;
	for (i=0;i<Psize;i++)
	{
		puzzle[i] = queueS->queue[i][queueS->headQ];
	}
	queueS->flag[queueS->headQ] = 0;
	headQ++;
}

int emptyQS(QueueS* queueS)
{
	if(queueS->frag[queueI->headQ] ==  0)
	{
		return 1;	
	}
	return 0;
}

int maxQS(QueueS* queueS)
{
	if(queueS->headQ == queueS->tailQ && queueS->flag[queueI->headQ] == 1)
	{
		return 1;
	}
	return 0;
}
