int evaluateSbox(int sbox[4][16], char* seq);
int isLinear(int sbox[4][16], char* seq1, char* seq2);
char* addBinary(char* s1, char* s2);
void slice(char* seq, char* ligne, char* colonne);
int binaryToInt(char* binary);
char* intToBinary(int seq);
char* middleDiff(char* binary);
int nbDiff(char* b1, char* b2);
char* next(char* binary);
