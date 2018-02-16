#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "sbox.h"

int diff1(int sbox[4][16])
{
    char* init = "000000";
    char* dif = middleDiff(init);
    char* res1 = intToBinary(evaluateSbox(sbox, init));
    char* res2 = intToBinary(evaluateSbox(sbox, dif));
    int res;

    if(nbDiff(res1, res2) >= 2) res = 1;
    else res = 0;

    while(strcmp(init, "111111") != 0 && res)
    {
        init = next(init);
        dif = middleDiff(init);
        res1 = intToBinary(evaluateSbox(sbox, init));
        res2 = intToBinary(evaluateSbox(sbox, dif));
        if(nbDiff(res1, res2) < 2) res = 0;
    }

    return res;
}

char* next(char* binary)
{
    int tmp = binaryToInt(binary);
    return(intToBinary(++tmp));
}

char* middleDiff(char* binary)
{
    char* res = malloc(sizeof(char) * 6);
    res[0] = binary[0];
    res[1] = binary[1];
    res[2] = (binary[2] + 1) % 2;
    res[3] = (binary[3] + 1) % 2;
    res[4] = binary[4];
    res[5] = binary[5];

    return res;
}

int nbDiff(char* b1, char* b2)
{
    int res;
    int i;

    for(i = 0; i < 6; i++)
    {
        if(b1[i] != b2[i]) res++;
    }

    return res;
}

int evaluateSbox(int sbox[4][16], char* seq)
{
    char* ligne = malloc(sizeof(char) * 2);
    char* colonne = malloc(sizeof(char) * 4);
    int ligneI;
    int colonneI;
    int res;

    slice(seq, ligne, colonne);
    ligneI = binaryToInt(ligne);
    colonneI = binaryToInt(colonne);

    return sbox[ligneI][colonneI];
}

int isLinear(int sbox[4][16], char* seq1, char* seq2)
{
    char* add = addBinary(seq1, seq2);
    int res0 = evaluateSbox(sbox, add);
    int res1 = evaluateSbox(sbox, seq1);
    int res2 = evaluateSbox(sbox, seq2);
    if(res0 == (res1+res2)%16)
    {
        return 1;
    }
    return 0;
}

char* addBinary(char* s1, char* s2)
{
    int i;
    char* res = malloc(sizeof(char) * 6);

    for(i = 0; i < 6; i++)
    {
        if(s1[i] == '1' && s2[i] == '1')
        {
            res[i] = '0';
        }

        if((s1[i] == '0' && s2[i] == '1') || (s1[i] == '1' && s2[i] == '0'))
        {
            res[i] = '1';
        }

        if(s1[i] == '0' && s2[i] == '0')
        {
            res[i] = '0';
        }
    }

    return res;
}

void slice(char* seq, char* ligne, char* colonne)
{
    ligne[0] = seq[0];
    ligne[1] = seq[5];
    colonne[0] = seq[1];
    colonne[1] = seq[2];
    colonne[2] = seq[3];
    colonne[3] = seq[4];
}

int binaryToInt(char* binary)
{
    int result = 0;
    int len = strlen(binary);
    int i;
    for(i = 0; i < len; i++)
    {
        if(binary[i] == '0') continue;
        else result = result + pow(2, (i));
    }
    return result;
}

char* intToBinary(int seq)
{
    char* res = malloc(sizeof(char) * 4);
    int tmp = seq;
    int i;

    for(i = 3; i >= 0; i--)
    {
        res[i] = tmp%2 + '0';
        tmp = tmp/2;
    }

    return res;
}

int main(int argc, char const *argv[])
{
    int sbox1[4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };

    printf("%d\n", binaryToInt(argv[1]));

    return 0;
}
