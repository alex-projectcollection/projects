#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"

/*makes main outpot file*/
void wrightbase8output(Database *db, char*fileName) {
	strcat(fileName, ".ob");
	FILE *f = fopen(fileName, "w");
	int addres = 100;
	char*addresbase8;
	char* line;
	while (addres < db->codeI) {
		addresbase8 = decimaltooctal(addres);
		line = frombinarytobase8(db->codeBlock[addres]);
		fprintf(f, "%s %s\n", addresbase8, line);
		addres++;
	}
	fclose(f);

} /*entry file creator*/
void makeentryfile(Database *db, char*fileName) {
	strcat(fileName, ".ent");
	FILE *ent = fopen(fileName, "w");
	int addres = 0;
	char* entry;
	char* addresof;
	while ((addres + 1) <= db->entInd) {
		entry = db->entries[addres];
		addresof = decimaltooctal(findmyplace(entry, db));
		fprintf(ent, "%s\t %s\n", entry, addresof);
		addres++;
	}
	fclose(ent);

}
/*extern file creator*/
void makeexternfile(Database *db, char*fileName) {
	strcat(fileName, ".ext");
	FILE *ext = fopen(fileName, "w");
	int addres = 0;
	char* extrn;
	char* addresof;
	while ((addres + 1) <= db->externsOutInd) {
		extrn = db->externsOut[addres];
		addresof = decimaltooctal(db->extVal[addres]);
		fprintf(ext, "%s\t %s\n", extrn, addresof);
		addres++;
	}
	fclose(ext);

}
/*makes output files*/
void makeoutput(Database *db, char*fileName) {
	char *nameEnt = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
	char *nameExt = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
	strcpy(nameEnt, fileName);
	strcpy(nameExt, fileName);
	wrightbase8output(db, fileName);
	if (db->entInd != 0) {
		makeentryfile(db, nameEnt);
	}
	if (db->externsOutInd != 0) {
		makeexternfile(db, nameExt);
	}

}
