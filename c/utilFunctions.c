#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"
/*Returns the number of a saved word if exists, otherwise returns -1*/
int getSavedName(char word[8])
{
	char savedStrings[4][8] = {".data", ".string", ".entry", ".extern"};
	int len = strlen(word);
	int opNum = -1;
	int charNum = 1;
	char keepLooking = 0;
	if(word[0] == '.')
	{
		for(;(opNum < 3) && !keepLooking; charNum = 0)
			for(keepLooking = 1,(++opNum);((savedStrings[opNum][charNum] != '\0') && keepLooking);charNum++)
				keepLooking = !(*(savedStrings[opNum] + charNum) ^ *(word + charNum));
	}
	if(!keepLooking)
		opNum = -1;
	return opNum;
}

/*Converts a binary string into an integer*/
int getIntFromBin(char word[MAX_FUNC_WORD_COUNT])
{
	int ret = 0;
	int one;
	int two;
	int three;
	switch(strlen(word))
	{
	case 2:
		(word[0] == '0') ? (two = 0) : (two = 1);
		(word[1] == '0') ? (one = 0) : (one = 1);
		three = 0;
		break;
	case 3:
		(word[0] == '0') ? (three = 0) : (three = 1);
		(word[1] == '0') ? (two = 0) : (two = 1);
		(word[2] == '0') ? (one = 0) : (one = 1);
		break;
	}
	ret = one + two * 2 + three * 4;
	return ret;
}

/*Returns the number of an operation if exists, otherwise returns -1*/
int getFunctionNum(char word[4])
{
	char operators[16][4] = {
			"mov", "cmp", "add",
			"sub", "not", "clr",
			"lea", "inc", "dec",
			"jmp", "bne", "red",
			"prn", "jsr", "rts",
			"stop"
	};

	int opNum = -1;
	int charNum = 0;
	char keepLooking = 0;
	if(strlen(word) < 5)
	{
		for(;(opNum < 15) && !keepLooking;charNum = 0)
			for(keepLooking = 1,(++opNum);((charNum < 3) && keepLooking);charNum++)
				keepLooking = !(*(operators[opNum] + charNum) ^ *(word + charNum));
		if(keepLooking && (((opNum < 15) && (strlen(word) == 3)) || (*(operators[opNum] + 3) == 'p')))
			return opNum;
	}
	return -1;
}

/**
 * breakLine - receives an input string, an output
 * memory allocation, and returns the number of words.
 */
int breakLine(char string[MAX_LINE_LENGTH], char saved[MAX_LINE_LENGTH][MAX_LINE_LENGTH])
{
	int wordNum = 0;
	int writer = 0;
	int letter = 0;
	while((string[letter]=='\n') || (string[letter]==' ') || (string[letter]=='\t'))
		letter++;
	while((string[letter] != '\n') && (string[letter]!='\0'))
	{
		if((string[letter]>32) && (string[letter]<127) && (string[letter] != ',') && (letter < MAX_LINE_LENGTH))
			saved[wordNum][writer++] = string[letter++];
		else
		{
			while((string[letter] == '\t') || (string[letter] == ' ') || (string[letter] == ','))
				letter++;
			while(writer < MAX_LINE_LENGTH)
			{
				saved[wordNum][writer] = '\0';
				writer++;
			}
			wordNum++;
			writer = 0;
		}
	}

	while(writer < MAX_LINE_LENGTH)
	{
		saved[wordNum][writer] = '\0';
		writer++;
	}
	wordNum++;

	return wordNum;
}

/**
 * Converts a decimal number "num" into a binary string
 * of length "len", and returns is.
 */
char *toBin(int num, int len)
{
	int lenNeg = len;
	int negative;
	char *ret = (char*)malloc(len * sizeof(char));
	(num<0)?(negative = 1):(negative = 0);
	for(len--;num; num = num/2)
		(num%2)?(*(ret + len--) = '1'):(*(ret + len--) = '0');
	while(len + 1)
		ret[len--] = '0';

	if(negative)/*Calculates the 2's complementary*/
	{
		while(ret[--lenNeg] == '0');
		while(--lenNeg + 1)
			(ret[lenNeg] == '0')?(ret[lenNeg] = '1'):(ret[lenNeg] = '0');
	}
	return ret;
}

/**
 * Function receives 3 strings:
 * 1. Command
 * 2. Element1
 * 3. Element2
 * The function analyzes the strings according
 * to their position in the array, and sets the
 * necessary data into a BinStr struct, and then returns is.
 */
BinStr *createBinStruct(char words[MAX_FUNC_WORD_COUNT][MAX_LINE_LENGTH])
{
	BinStr *line = (BinStr*)malloc(sizeof(BinStr));
	int opNum = getFunctionNum(words[0]);
	char helperOrigin[MAX_LINE_LENGTH], helperDestin[MAX_LINE_LENGTH];

	strcpy(helperOrigin, words[1]);
	if(words[2][0] != '\0')
		strcpy(helperDestin, words[2]);
	else
		strcpy(helperDestin, "#");
	strcpy(line->begin, "101");

	if((opNum < 4) || (opNum == 6))
		strcpy(line->group, "10");
	else if(opNum < 14)
	{
		strcpy(line->group, "01");
		helperOrigin[0] = '#';
		strcpy(helperDestin, words[1]);
	}
	else strcpy(line->group, "00");


	strcpy(line->opCode, toBin(opNum, 4));
	if(opNum > 13)
	{

		strcpy(line->opDestin, "00");
		strcpy(line->opOrigin, "00");
	}else
	{
		strcpy(line->opOrigin, (char*)caseof(helperOrigin));
		strcpy(line->opDestin, (char*)caseof(helperDestin));
	}
	strcpy(line->era, "00");
	return line;
}

/**
 * Creates a binary string from a given BinStr
 */
char *getBinary(BinStr *word)
{
	char *ret = (char*)malloc(sizeof(char));
	strcat(ret, "101");
	strcat(ret, word->group);
	strcat(ret, word->opCode);
	strcat(ret, word->opOrigin);
	strcat(ret, word->opDestin);
	strcat(ret, word->era);
	return ret;
}
