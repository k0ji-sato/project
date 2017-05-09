#define MAXQI 100;


//flagの0or1で配列の中身の有無を表す
typedef struct
{
	int queue[MAXQI];
	int flag[MAXQI];
	int headQ;
	int tailQ;
}QueueI

void InitQI(QueueI* queueI)
{
	int i;
	for (i=0;i<MAXQI;i++)
	{
		queueI->flag[i] = 0;		
	}
	
	queueI->headQ = 0;
	queueI->tailQ = 0;
}

void putQI(QueueI* queueI, int n)
{
	queueI->queue[queueI->tailQ] = n;
	queueI->flag[queueI->tailQ] = 1;
	tailQ++;
} 

void getQI(QueueI* queueI, int* tmp)
{	
	tmp* = queueI->queue[queueI->headQ];
	queueI->flag[queueI->headQ] = 0;
	headQ++;
}

int emptyQI(QueueI* queueI)
{
	if(queueI->flag[queueI->headQ] ==  0)
	{
		return 1;	
	}
	return 0;
}

int maxQI(QueueI* queueI)
{
	if(queueI->headQ == queueI->tailQ && queueI->flag[queueI->headQ] == 1)
	{
		return 1;
	}
	return 0;
}
