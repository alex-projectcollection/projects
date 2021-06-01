#ifndef HEADQUARTERS_H_
#define HEADQUARTERS_H_

/**
 * database
 */
#define MAX_LINE_LENGTH 80
#define MAX_DB_SIZE 1000
#define MAX_FUNC_WORD_COUNT 3



typedef struct Database
{
	char codeBlock[MAX_DB_SIZE][16];
	int codeI;

	char varBlock[MAX_DB_SIZE][MAX_LINE_LENGTH];
	int varVal[MAX_DB_SIZE];
	int varI;

	char varBlock2[MAX_DB_SIZE][MAX_LINE_LENGTH];
	int varI2;

	char externs[MAX_DB_SIZE][MAX_LINE_LENGTH];
	char externsOut[MAX_DB_SIZE][MAX_LINE_LENGTH];
	int externsOutInd;
	int extVal[MAX_DB_SIZE];
	int extInd;

	char entries[MAX_DB_SIZE][MAX_LINE_LENGTH];
	int entInd;
} Database;

typedef struct BinStr
{
	char begin[4];
	char group[MAX_FUNC_WORD_COUNT];
	char opCode[5];
	char opOrigin[MAX_FUNC_WORD_COUNT];
	char opDestin[MAX_FUNC_WORD_COUNT];
	char era[MAX_FUNC_WORD_COUNT];
} BinStr;


/**
 * Database functions
 */
Database * initDataBase();
void resetDataBase(Database *db);
void setArray(char current[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, Database *db);
void setString(char word[MAX_LINE_LENGTH], Database *db);
void setEntry(char word[MAX_LINE_LENGTH], Database *db);
void setExtern(char word[MAX_LINE_LENGTH], Database *db);
int isExtern(char word[MAX_LINE_LENGTH], Database *db);
int checkForErrors(char words[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, int codeLine);
int setLineInDB(char broken[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, Database *db, int lineCounter, int errors);
void printDB(Database *db);
BinStr *createBinStruct(char words[MAX_FUNC_WORD_COUNT][MAX_LINE_LENGTH]);

/**
 * UtilFunctions
 */
int getSavedName(char word[8]);
int getIntFromBin(char word[MAX_FUNC_WORD_COUNT]);
int getFunctionNum(char word[4]);
int breakLine(char string[MAX_LINE_LENGTH], char saved[MAX_LINE_LENGTH][MAX_LINE_LENGTH]);
char *toBin(int num, int len);
char *getBinary(BinStr *word);

/**
 * Utils1
 */
char *concat(char *s1, char *s2);
char *caseof(char *inp);
char *registers(char * input1, char * input2);
char *rotate(char* input);
char *addnumbers(char* input);
char *gotoadreesandcut(char * input1, char * input2, char * input3, Database *db);
char *instructionsforcaseof3(char * input, Database *db);

/**
 * Utils2
 */
char *getlinefromnum(char * input);
char *addindvariableline(char * input, Database *db);
int secondloop(Database *db);

/**
 * FromBinary
 */
char *frombinarytobase8(char* input);
char* decimaltooctal(int addres);

/**
 * Utils3
 */
char *theveriabal(char * input);
int isveriabal(char* input);
int findmyplace(char* tofind, Database *db);
char *getmycodeline(int place, Database *db);

/**
 * File maker
 */
void makeentryfile(Database *db, char*fileName);
void wrightbase8output(Database *db, char*fileName);
void makeexternfile(Database *db, char*fileName);
void makeoutput(Database *db, char*fileName);

#endif

