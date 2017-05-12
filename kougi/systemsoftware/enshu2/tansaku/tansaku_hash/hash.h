//
// Created by 佐藤孝嗣 on 2017/05/12.
//

#ifndef TESTINTTOPUZZLE_HASH_H
#define TESTINTTOPUZZLE_HASH_H

#endif //TESTINTTOPUZZLE_HASH_H

#define HashSIZE 200000

typedef struct{
    int hash[HashSIZE];
    int numhash;
}Hash;

void inithash(Hash* hash)
{
    hash->numhash = 0;
}

int searchhash(Hash* hash,int n)
{
    int i;
    for (i=0;i < hash->numhash;i++)
    {
        if(hash->hash[i]==n)
        {
            return 1;
        }
    }
    return 0;
}

void hashput(Hash* hash,int n)
{
    hash->hash[hash->numhash] = n;
    hash->numhash++;
}