#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"

/*makes a # line in database*/
char* getlinefromnum(char * input) {
	int num = 0;
	char simbul = "";
	char digit = "0";
	char * strnum = (char*) malloc(sizeof(input) - 1);
	int i = 1;
	int j = 0;
	char * fullstr = (char*) malloc(15 * sizeof(char));
	while ((strlen(input) - 1) >= i) {
		if (input[i] == '-') {
			simbul = '-';
			i++;
			continue;
		}
		digit = *(input + i);
		strnum[j] = digit;
		j++;
		i++;
	}
	if (simbul == '-') {
		num = -atoi(strnum);
	} else {
		num = atoi(strnum);
	}
	fullstr = toBin(num, 13);
	fullstr = concat(fullstr, "00");
	return fullstr;
}
/*adding veriabal x line to database*/
char * addindvariableline(char * input, Database *db) {
	char * outpot = (char*) malloc(15 * sizeof(char));
	int i = 0;
	while ((strlen(input) - 1) >= i) {
		if (input[i] == '[') {
			outpot = instructionsforcaseof3(input, db);
			break;
		}
		outpot = concat(outpot, input);
		i++;
	}

	return outpot;
}
/*doing the second loop*/
int secondloop(Database *db) {
	char* line = (char*) malloc(15 * sizeof(char));
	int index = 100;
	int varindex = 0;
	int tester;
	int errors = 0;
	char *myPlace = "1";
	while ((db->codeI) >= index)
	{
			if (*getmycodeline(index, db) == '2')
			{
				if (isveriabal(db->varBlock2[varindex]) == 1)
				{
					myPlace = instructionsforcaseof3(db->varBlock2[varindex], db);
					if(myPlace[0] != '\0')
						strcpy(db->codeBlock[index], myPlace);
					else errors = 1;
				} else {
					tester = findmyplace(theveriabal(db->varBlock2[varindex]), db);
					if(tester < 0)
						errors = 1;
					line = toBin(tester,13);
					line = concat(line, "10");
					strcpy(db->codeBlock[index], line);
				}
				varindex++; /*put the right line in place*/
			}
		index++;

	}
	return errors;
}
