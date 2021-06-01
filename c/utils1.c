#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"

/* conects2 strings*/
char* concat(char *s1, char *s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char *result = (char*)malloc(len1 + len2 + 1); /*+1 for the zero-terminator*/
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1); /*+1 to copy the null-terminator*/
	return result;
}
/*determins bits 5-2*/
char* caseof(char *inp) {
	char *ret = (char*) malloc(2 * sizeof(char));
	ret = "\0";
	char first = inp[0];
	char second = inp[1];
	char last = inp[strlen(inp) - 1];
	if (first == '#') {
		ret = "00";
	} else if (first == 'r' && (second >= '0' && second <= '7')) {
		ret = "11";
	} else if (last == ']') {
		ret = "10";
	} else {
		ret = "01";
	}
	return ret;
}

/* function to determon registers line*/
char *registers(char * input1, char * input2) {
	char * str1 = "0";
	char * str2 = "000000";
	char * str3 = "000000";
	char * str4 = "00";
	char *registerline = (char*) malloc(15 * sizeof(char));
	registerline = "\0";
	if ((caseof(input1) == "11") && (caseof(input2) == "11")) {
		str2 = toBin((input1[1]) - '0', 6);
		str3 = toBin(input2[1] - '0', 6);
	} else if (caseof(input1) == "11") {
		str2 = toBin(input1[1] - '0', 6);
	} else if (caseof(input2) == "11") {
		str3 = toBin(input2[1] - '0', 6);
	}
	registerline = concat(str1, str2);
	registerline = concat(registerline, str3);
	registerline = concat(registerline, str4);
	return registerline;
}

/*ading 1s to the string*/
char *addnumbers(char* input) {
	char *output = (char*) malloc(13 * sizeof(char));
	output = "\0";
	int size = (int) strlen(input);
	int i = 0;
	output = concat(output, input);
	while (13 - size > i) {
		output = concat("1", output);
		i++;
	}
	return output;
}
/*rotates the string*/
char *rotate(char* input) {
	char *output = (char*) malloc(15 * sizeof(char));
	int index = 0;
	while(index < strlen(input))
	{
		*(output + index) = *(input + strlen(input) - 1 - index);
		index++;
	}
	while(index < 15)
	{
		output[index] = '\0';
		index++;
	}
	return output;
}
/* cuts the substring of bits*/
char *gotoadreesandcut(char * input1, char * input2, char * input3, Database *db) {
	int tester = findmyplace(input1, db);
	char * line;
	int start = atoi(input2);
	int end = atoi(input3);
	int i = start;
	int size;
	char add = '\n';
	char *outpot = (char*) malloc((end - start + 1) * sizeof(char));
	if(tester > -1)
	{
		line = getmycodeline(tester, db);
		size = strlen(line);
		outpot = "\0";
		while ((end) >= i) {
			add = line[size - 1 - i];
			outpot = concat(outpot, &add);
			i++;
		}
		return rotate(outpot); /*rotating*/
	}
	return "\0";
}
/* dealing with substrings such as: k[2-4]*/
char *instructionsforcaseof3(char * input, Database *db) {
	char *outpot = (char*) malloc(15 * sizeof(char));
	char * str1 = (char*) malloc(15 * sizeof(char));
	char * str2 = (char*) malloc(15 * sizeof(char));
	char * str3 = (char*) malloc(15 * sizeof(char));
	outpot = "\0";
	str1 = "\0";
	str2 = "\0";
	str3 = "\0";
	int i = 0;
	char *add = '\0';
	while ((strlen(input) - 1) > i) {
		while (input[i] != '[') {
			add = input[i];
			str1 = concat(str1, &add);
			i++;
		}
		i++;
		while (input[i] != '-') {
			add = input[i];
			str2 = concat(str2, &add);
			i++;
		}
		i++;
		while (input[i] != ']') {
			add = input[i];
			str3 = concat(str3, &add);
			i++;
		}
		i++;
	}
	outpot = gotoadreesandcut(str1, str2, str3, db);
	if(outpot[0] != '\0')
	{
		outpot = addnumbers(outpot); /*ading 1's*/
		outpot = concat(outpot, "00");/*E R A needs adding*/
		return outpot;
	}
	return "\0";
}

