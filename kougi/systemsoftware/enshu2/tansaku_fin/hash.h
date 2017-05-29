//
// Created by 佐藤孝嗣 on 2017/05/12.
//

#ifndef TESTINTTOPUZZLE_HASH_H
#define TESTINTTOPUZZLE_HASH_H

#endif //TESTINTTOPUZZLE_HASH_H

#define HashSIZE 45

typedef struct{
    int hash[9876][HashSIZE];
    int numhash[9876];
}Hash;

void inithash(Hash* hash)
{
    int i;

    for (i = 0; i < 9; i++) {
        hash->numhash[i] = 0;

    }
}

int searchhash(Hash* hash,int n)
{
    int i,j;
    j = n %10000;

    for (i=0;i < hash->numhash[j];i++)
    {
        if(hash->hash[j][i]==n)
        {
            return 1;
        }
    }
    return 0;
}

void hashput(Hash* hash,int n)
{
    int i;

    i = n%10000;
    hash->hash[i][hash->numhash[i]] = n;
    hash->numhash[i]++;
}