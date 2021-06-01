#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "headquarters.h"

/* takes a binery string line and gives back a base8 line*/
char * frombinarytobase8(char* input) {
	char* output = (char*) malloc(5 * sizeof(char));
	int index = 0;
	char base8[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
	char* temp8[5];
	int i = 0;
	int j = 0;
	char * temp = (char*) malloc(3 * sizeof(char));
	while (index <= 15) {
		if (i == 3) {
			i = 0;
			temp8[j] = temp;
			j++;
			temp = (char*) malloc(3 * sizeof(char));
		}
		temp[i] = input[index];
		i++;
		index++;
	}
	index = 0;
	while (index < 5) {
		output[index] = base8[getIntFromBin(temp8[index])];
		index++;
	}

	return output;
}
/* converts numbers to a base 8 char*/
char* decimaltooctal(int addres) {
	int rem, i = 0, octal = 0;
	char* octalchar = (char*) malloc(4 * sizeof(char));
	;
	int j = 0;
	char* buffer;
	char base8[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
	while (addres != 0) {
		rem = addres % 8;
		octalchar[j] = base8[rem];
		j++;
		addres /= 8;
		octal += rem * i;
		i *= 10;
	}
	octalchar = rotate(octalchar);
	return octalchar;
}
