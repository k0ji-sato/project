#define MAXQS 1024
#define Psize 9

//配列の中身の有無はflagの0or1で表す
typedef struct
{
	int queue[Psize][MAXQS];
	int flag[MAXQS];
	int headQ;
	int tailQ;
}QueueS;

int emptyQS(QueueS* queueS);
int fullQS(QueueS* queueS);

void InitQS(QueueS* queueS)
{
	int i;
	for (i=0;i<MAXQS;i++)
	{	
		queueS->flag[i] = 0;		
	}
	
	queueS->headQ = 0;
	queueS->tailQ = 0;
}

void putQS(QueueS* queueS, int puzzle[])
{
	int i;
    if(!fullQS(queueS))
    {
	    for (i=0;i<Psize;i++)
	    {
	        queueS->queue[i][queueS->tailQ] = puzzle[i];
	    }
	    queueS->flag[queueS->tailQ] = 1;
        if (queueS->tailQ!=MAXQS-1)
        {
            queueS->tailQ++;
        }
        else
        {
            queueS->tailQ = 0;
        }
    }
    else puts("これ以上キューに入れられません。");
}

void getQS(QueueS* queueS, int puzzle[])
{	
	int i;
    if(!emptyQS(queueS))
    {
	    for (i=0;i<Psize;i++)
	    {
		    puzzle[i] = queueS->queue[i][queueS->headQ];
	    }
	    queueS->flag[queueS->headQ] = 0;
        if (queueS->headQ != MAXQS-1) {
            queueS->headQ++;
        }
        else
        {
            queueS->headQ = 0;
        }
    }
    else puts("キューの中身が存在しません。");
}

int emptyQS(QueueS* queueS)
{
	if(queueS->flag[queueS->headQ] ==  0)
	{
		return 1;	
	}
	return 0;
}

int fullQS(QueueS* queueS)
{
	if(queueS->headQ == queueS->tailQ && queueS->flag[queueS->headQ] == 1)
	{
		return 1;
	}
	return 0;
}
