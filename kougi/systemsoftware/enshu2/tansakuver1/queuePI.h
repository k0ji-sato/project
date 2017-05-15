//
// Created by 佐藤孝嗣 on 2017/05/12.
//

#ifndef TANSAKU_QUEUEPI_H
#define TANSAKU_QUEUEPI_H
#include<stdio.h>

#endif //TANSAKU_QUEUEPI_H

#define MAXQPI 400000
#define Psize 9



typedef struct
{
    int puzzleint;
    int lastmove;
    int depth;

}PuzzleInt;

//配列の中身の有無はflagの0or1で表す
typedef struct
{
    PuzzleInt queue[MAXQPI];
    int flag[MAXQPI];
    int headQ;
    int tailQ;
}QueuePI;

int emptyQPI(QueuePI* queuePI);
int fullQPI(QueuePI* queuePI);

void InitQPI(QueuePI* queuePI)
{
    int i;
    for (i=0;i<MAXQPI;i++)
    {
        queuePI->flag[i] = 0;
    }

    queuePI->headQ = 0;
    queuePI->tailQ = 0;
}

void putQPI(QueuePI* queuePI, PuzzleInt* puzzleint)
{
    if(!fullQPI(queuePI))
    {
        queuePI->queue[queuePI->tailQ] = *puzzleint;

        queuePI->flag[queuePI->tailQ] = 1;
        if (queuePI->tailQ!=MAXQPI-1)
        {
            queuePI->tailQ++;
        }
        else
        {
            queuePI->tailQ = 0;
        }
    }
    else puts("これ以上キューに入れられません。");
}

void getQPI(QueuePI* queuePI, PuzzleInt* puzzleint)
{
    if(!emptyQPI(queuePI))
    {
        *puzzleint = queuePI->queue[queuePI->headQ];
        queuePI->flag[queuePI->headQ] = 0;
        if (queuePI->headQ != MAXQPI-1) {
            queuePI->headQ++;
        }
        else
        {
            queuePI->headQ = 0;
        }
    }
    else puts("キューの中身が存在しません。");
}

int emptyQPI(QueuePI* queuePI)
{
    if(queuePI->flag[queuePI->headQ] ==  0)
    {
        puts("empty");
        return 1;

    }
    return 0;
}

int fullQPI(QueuePI* queuePI)
{
    if(queuePI->headQ == queuePI->tailQ && queuePI->flag[queuePI->headQ] == 1)
    {
        puts("full");
        return 1;
    }
    return 0;
}
