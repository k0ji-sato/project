#define MAXQI 4

//flagの0or1で配列の中身の有無を表す
typedef struct
{
	int queue[MAXQI];
	int flag[MAXQI];
	int headQ;
	int tailQ;
}QueueI;

int emptyQI(QueueI* queueI);
int fullQI(QueueI* queueI);

void InitQI(QueueI* queueI)
{
	int i;
	for (i=0;i<MAXQI ; i++)
	{
		queueI->flag[i] = 0;		
	}
	
	queueI->headQ = 0;
	queueI->tailQ = 0;
}

void putQI(QueueI* queueI, int n)
{
    if (!fullQI(queueI))
    {
        queueI->queue[queueI->tailQ] = n;
        queueI->flag[queueI->tailQ] = 1;
        if (queueI->tailQ!=MAXQI-1)
        {
            queueI->tailQ++;
        }
        else
        {
            queueI->tailQ = 0;
        }

    }
    else puts("これ以上キューに入れられません。");
}

void getQI(QueueI* queueI, int* tmp)
{
    if (!emptyQI(queueI)) {
        *tmp = queueI->queue[queueI->headQ];
        queueI->flag[queueI->headQ] = 0;

        if (queueI->headQ != MAXQI-1) {
            queueI->headQ++;
        }
        else
        {
            queueI->headQ = 0;
        }
    }
    else puts("キューの中身が存在しません。");
}

int emptyQI(QueueI* queueI)
{
	if(queueI->flag[queueI->headQ] ==  0)
	{
		return 1;	
	}
	return 0;
}

int fullQI(QueueI* queueI)
{
	if(queueI->headQ == queueI->tailQ && queueI->flag[queueI->headQ] == 1)
	{
		return 1;
	}
	return 0;
}
