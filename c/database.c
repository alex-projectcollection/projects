#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"


/*Creates a database*/
Database *initDataBase()
{
	Database *db = (Database*)malloc(sizeof(Database));
	resetDataBase(db);
	return db;
}

/*Resets the database*/
void resetDataBase(Database *db)
{
	db->codeI = 100;
	db->varI = 0;
	db->varI2 = 0;
	db->extInd = 0;
	db->entInd = 0;
	db->externsOutInd = 0;
}

/*Recursively inserts an array into the database, such as .data 1,2,3,4,5,6,7*/
void setArray(char current[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, Database *db)
{
	if(len)
	{
		strcpy(db->codeBlock[db->codeI++], (char*)toBin(atoi(current++), 15));
		setArray(current,len-1, db);
	}
}

/*Inserts a string into the database*/
void setString(char word[MAX_LINE_LENGTH], Database *db)
{
	char *current = (char*)malloc(sizeof(char));
	strcpy(current, word);
	if(current[0] == '\"')
		current++;
	while(current[0] != '\"')
		strcpy(db->codeBlock[db->codeI++], (char*)toBin((int)((current++)[0]), 15));
	strcpy(db->codeBlock[db->codeI++], "000000000000000");
}

/*Inserts an entry tag into the database*/
void setEntry(char word[MAX_LINE_LENGTH], Database *db)
{
	strcpy(db->entries[db->entInd++], word);
}

/*Inserts an extern tag into the database*/
void setExtern(char word[MAX_LINE_LENGTH], Database *db)
{
	strcpy(db->externs[db->extInd++], word);
}

/*Checks if a certain String is an extern*/
int isExtern(char word[MAX_LINE_LENGTH], Database *db)
{
	int opNum = 0;
	int charNum = 0;
	char keepLooking = 0;
	for(;(opNum < db->extInd) && !keepLooking; opNum++, charNum = 0)
		for(keepLooking = 1;((db->externs[opNum][charNum] != '\0') && keepLooking);charNum++)
			keepLooking = !(*(db->externs[opNum] + charNum) ^ *(word + charNum));
	if(!keepLooking)
		opNum = -1;
	return opNum;
}

/*Checks for errors in the input*/
int checkForErrors(char words[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, int codeLine)
{
	int ret = 0;
	int opNum = getFunctionNum(words[0]);
	int element1 = getIntFromBin(caseof(words[1]));
	int element2 = getIntFromBin(caseof(words[2]));
	if(opNum == 14 || opNum == 15)
	{
		if(len > 1)
		{
			fprintf(stderr,"ERROR: Too many variables in line %d\n", codeLine);
			ret = 1;
		}
	}
	else if((opNum < 4) && (opNum != 1))
	{
		if(len > 3)
		{
			fprintf(stderr,"ERROR: Too many variables in line %d\n", codeLine);
			ret = 1;
		}
		if(len < 3)
		{
			fprintf(stderr,"ERROR: Too few variables in line %d\n", codeLine);
			ret = 1;
		}
		else if((element2 != 1) && (element2 != 3))
		{
			fprintf(stderr,"ERROR: Wrong type of variable 2 in line %d\n", codeLine);
			ret = 1;
		}
	}else if((opNum >3) && (opNum < 14))
	{
		if(element1 != 1 && element1 != 3 && opNum != 12)
		{
			fprintf(stderr,"ERROR: Wrong type of variable in line %d\n", codeLine);
			ret = 1;
		}
		else if(opNum != 6 && len>2)
		{
			fprintf(stderr,"ERROR: Too many variables in line %d\n", codeLine);
			ret = 1;
		}
		else if(opNum == 6)
		{
			if(len!=3)
			{
				fprintf(stderr,"ERROR: Wrong number of variables in line %d\n", codeLine);
				ret = 1;
			}else if(element1 != 1)
			{
				fprintf(stderr,"ERROR: Wrong type of variable 1 in line %d\n", codeLine);
				ret = 1;
			}else if(element2 != 1 || element2 != 3)
			{
				fprintf(stderr,"ERROR: Wrong type of variable 2 in line %d\n", codeLine);
				ret = 1;
			}
			ret = 1;
		}
	}
	return ret;
}

/**
 * Main function for Itteration 1.
 * This function receives an assembly command from the input file, and
 * analyzes it, and sets the different arguments into their proper places
 * in the database.
 *
 * The function sets all command lines and variables into the database, and
 * leaves the places that need to hold TAG addresses with the symbol '2' to
 * be handled in itteration 2.
 *
 */
int setLineInDB(char broken[MAX_LINE_LENGTH][MAX_LINE_LENGTH], int len, Database *db, int lineCounter, int errors)
{
	int index = 0;
	char commandLine[MAX_FUNC_WORD_COUNT][MAX_LINE_LENGTH];
	int opNum = getFunctionNum(broken[0]);
	int nameSpace = getSavedName(broken[0]);
	int element1;
	int element2;
	FILE *externFile;

	if(strlen(broken[0]))
	{

		if(!errors) /*Checks if line is empty*/
		if(opNum + 1)
		{
			if(checkForErrors(broken, len, lineCounter))
				return 1;
			element1 = getIntFromBin(caseof(broken[1]));
			element2 = getIntFromBin(caseof(broken[2]));

			strcpy(commandLine[0], getBinary(createBinStruct(broken)));
			strcpy(commandLine[1], "\0");
			strcpy(commandLine[2], "\0");


			if((opNum < 4) || (opNum == 6)) /*Binary function*/
			{
				if(element1 == 3)
				{
					if(element2 == 3)/*2 registers*/
						strcpy(commandLine[1],registers(broken[1], broken[2]));
					else
					{
						strcpy(commandLine[1], registers(broken[1], "NoRegister"));
						if(!element2)
							strcpy(commandLine[2],(char*)getlinefromnum(broken[2]));
						else
						{
							if(isExtern(broken[2], db) + 1)
							{
								strcpy(commandLine[2], "000000000000001");
								strcpy(db->externsOut[db->externsOutInd], broken[2]);
								db->extVal[db->externsOutInd++] = db->codeI+2;
							}
							else
							{
								strcpy(commandLine[2], "2\0");
								strcpy(db->varBlock2[db->varI2++], broken[2]);
							}
						}
					}
				}else
				{
					if(isExtern(broken[1], db) + 1)
					{
						strcpy(commandLine[1], "000000000000001");
						strcpy(db->externsOut[db->externsOutInd], broken[1]);
						db->extVal[db->externsOutInd++] = db->codeI+1;
					}
					else
					{
						strcpy(commandLine[1], "2\0");
						strcpy(db->varBlock2[db->varI2++], broken[1]);
					}
					if(element2 == 3)
						strcpy(commandLine[2], registers("NoRegister", broken[2]));
					else
						if(!element2)
							strcpy(commandLine[2],(char*)getlinefromnum(broken[2]));
						else
						{

							if(isExtern(broken[2], db) + 1)
							{
								strcpy(commandLine[2], "000000000000001");
								strcpy(db->externsOut[db->externsOutInd], broken[2]);
								db->extVal[db->externsOutInd++] = db->codeI+2;
							}
							else
							{
								strcpy(db->varBlock2[db->varI2++], broken[2]);
								strcpy(commandLine[2], "2\0");
							}
						}
				}
			}
			else if(opNum < 14)/*Unary function*/
			{
				if(checkForErrors(broken, len, lineCounter))
					return 1;
				if(element1 == 3)
					strcpy(commandLine[1],registers("NoRegister", broken[1]));
				else
					switch(element1)
					{
					case 0:
						strcpy(commandLine[1],(char*)getlinefromnum(broken[1]));
						break;
					default:
						if(isExtern(broken[1], db) + 1)
						{
							strcpy(commandLine[1], "000000000000001");
							strcpy(db->externsOut[db->externsOutInd], broken[1]);
							db->extVal[db->externsOutInd++] = db->codeI+1;
						}
						else
						{
							strcpy(db->varBlock2[db->varI2++], broken[1]);
							strcpy(commandLine[1], "2\0");
						}
						break;
					}
			}
			for(index = 0; index < 3; index++)
				if(commandLine[index][0] != '\0')
					strcpy(db->codeBlock[db->codeI++], commandLine[index]);
		}else if(nameSpace > -1) /*checks if the line is an Instruction (Hanhaya)*/
			switch(nameSpace)
			{
			case 0: setArray(&broken[1], len-1, db);
				break;
			case 1: setString(&broken[1], db);
				break;
			case 2: setEntry(&broken[1], db);
				break;
			case 3: setExtern(&broken[1], db);
				break;
			}
		else
		{
			if(broken[0][strlen(broken[0]) - 1] != ':')
			{
				fprintf(stderr, "Unknown argument \"%s\"\n", broken[0]);
				return 1;
			}
			index = strlen(broken[0]) - 2;
			db->varBlock[db->varI][index + 1] = '\0';
			for(; index +1; index--)
				db->varBlock[db->varI][index] = broken[0][index];
			db->varVal[db->varI] = db->codeI;
			db->varI++;

			errors = setLineInDB(&broken[1], len-1, db, lineCounter, errors);
		}
	}
	return errors;
}

/*Prints the database*/
void printDB(Database *db)
{
	int index;
	printf("~~~~~~~Code Block~~~~~~~\n\n");
	for(index = 100;index < db->codeI;index++)
			printf("%d:   |%s|\n", index, db->codeBlock[index]);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

	printf("~~~~~~~Variable Block~~~~~~~\n\n");
	for(index = 0;index < db->varI; index++)
		printf("|%s|%d|\n", db->varBlock[index], db->varVal[index]);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

	printf("~~~~~~~Variable Block 2nd Itteration~~~~~~~\n\n");
	for(index = 0;index < db->varI2; index++)
			printf("|%s|\n", db->varBlock2[index]);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

	printf("~~~~~~~Externs~~~~~~~\n\n");
		for(index = 0;index < db->extInd; index++)
				printf("|%s|\n", db->externs[index]);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

	printf("~~~~~~~Entries~~~~~~~\n\n");
			for(index = 0;index < db->entInd; index++)
					printf("|%s|\n", db->entries[index]);
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}
