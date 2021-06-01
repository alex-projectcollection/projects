#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"
/*main function*/


int main(int argc, char**argv)
{
	char sentence[MAX_LINE_LENGTH];
	char broken[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
	Database *db = initDataBase();
	FILE *f;
	int lineCounter;
	char *fileName = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
	char *nameToSend = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
	int index;
	int errors = 0;

	while(--argc)
	{
		strcpy(fileName, *++argv);
		strcpy(nameToSend, fileName);
		strcat(fileName, ".as");
		f = fopen(fileName, "r");
		lineCounter = 0;
		printf("Program %s:\n", fileName);
		while(fgets(sentence, MAX_LINE_LENGTH, f))
			errors += setLineInDB(broken,breakLine(sentence, broken),db, ++lineCounter, 0);
		fclose(f);
		if(!errors)
		{
			if(!secondloop(db))
			{
				/**
				 * Uncomment in order to view the database
				 */
				/*printDB(db);*/
				makeoutput(db, nameToSend);
			}else
			{
				fprintf(stderr, "Errors encountered in iterration 2, program \"%s\" has been terminated.\n\n", fileName);
				errors = 1;
			}
		}else
			fprintf(stderr, "Errors encountered in iterration 1, program \"%s\" has been terminated.\n\n", fileName);
		resetDataBase(db);
		if(!errors)
			printf("Program %s was successfully compiled\n\n", fileName);
		errors = 0;
	}
	free(db);
	exit (0);
}
