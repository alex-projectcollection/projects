#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"

/*bring back only a variabal even if its a substunig.*/
char* theveriabal(char * input) {
	char * var = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
	int index = 0;
	while (strlen(input) >= index) {
		if (input[index] == '[') {
			return var;
		}
		var[index] = input[index];
		index++;
	}
	return var;
}
/* returns 1 if the char is a substring if not returns 0*/
int isveriabal(char* input){
	int index =0;
	int anser=0;
	while (index <= (strlen(input)-1)){
		if (input[index]=='['){
			anser=1;
		}
		index++;
	}


	return anser;
}/*returns line num*/
int findmyplace(char* tofind, Database *db) {
	int line = 0;
	int size = strlen(tofind);
	int eqwalls = 0;
	while ((line < db->varI) && (eqwalls != size)) {
		if (db->varBlock[line][eqwalls] == tofind[eqwalls]) {
			eqwalls++;
			continue;
		}
		line++;
if(line ==db->varI){
	fprintf(stderr, "Argument \"%s\" is undefined.\n", tofind);
	return -1;
}
	}
	return db->varVal[line];
}

/*get code in line*/
	char * getmycodeline(int place, Database *db) {
		char* line = (char*) malloc(15 * sizeof(char));
		line = db->codeBlock[place];
		return line;
	}
