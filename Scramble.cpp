#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
	Code writting by Meesum Ali 
	Date: 12/29/2017
	Simple text scrambling c++ program
	Needs a text file to take input from in the same directory as this c++ source file.
*/



//-------------------------------------Declaring Global variables
const int BUFF = 300;
FILE * pFile = NULL;
char* changes;
int charcount = 0;


//function to get number of characters in file to prevent buffer overflow
int numofc(char* fname) {

	pFile = fopen(fname, "r");
	if (pFile == NULL) {
		perror("Error opening file"); return -1;
	}
	int ch;
	while (1) {
		ch = fgetc(pFile);
		if (ch == EOF)
			break;
		++charcount;
	}
	fclose(pFile);
	return charcount;
}

//function to extract all characters from inputfile and store it in char array "filestring"
char* getstring(char* fname, char* filestring) {

	pFile = fopen(fname, "r");
	char mystring[300];
	if (pFile == NULL) {perror("Error opening file"); }
	char ch;
	int i = 0;
	while (1) {
		ch = fgetc(pFile);
		filestring[i] = ch;
		if (ch == EOF)
			break;
		i++;
	}
	filestring[charcount] = '\0';
	fclose(pFile);
	return filestring;
}


//function to scrable text from inputfile. EDIT CONTENTS OF FUNCTION TO CREATE YOUR DESIRED TEXT SCRAMLE
//IF YOU CHOOSE TO EDIT FUCTION MAKE SURE TO EDIT UNDO FUNCTION ACCORDINGLY OR ELSE CODE WILL NOT BE INVERTABLE
void editone(char* fname, char* filestring) {

	pFile = fopen(fname, "w");

	if (pFile == NULL) perror("Error opening file"); 

	int ch='b';
	for (int i = 0; i < charcount; i++) {
		filestring[i] += 1;
		ch=filestring[i];
		fputc(ch, pFile);
	}

	fclose(pFile);
}


//function to descramble text from inputfile
//EDIT IF FUCTION ABOVE WAS MODIFIED
void undo_editone(char* fname, char* filestring) {

	pFile = fopen(fname, "w");
	//char mystring[300];
	if (pFile == NULL) perror("Error opening file");

	int ch = 'b';
	for (int i = 0; i < charcount; i++) {
		filestring[i] -= 1;
		ch = filestring[i];
		fputc(ch, pFile);
		//puts("Done");
	}

	fclose(pFile);
}


int main(int argc, char **argv) {

	//declaring neccesary variables for file parsing and char manipulations	
	char command=0;
	char fname[BUFF];
	char* filestring = NULL;
	char* mystring = NULL;

	//-------------------------------File input code-----------------------------------------------------------------------------------
	printf("Enter file to be edited <examplefile.txt>\n");
	do {
		scanf(" %s", fname);
		pFile = fopen(fname, "r");
		if (pFile == NULL) { printf("Error reading in filename please retry\n"); }
	} while (pFile == NULL);

	//--------------------------------Scramble or descramble input code--------------------------------------------------------------
	printf("Enter if it's an Scramble or Descramble file? s or d\n");

	while (command != 's' && command != 'd') {
		scanf(" %c", &command);
		tolower(command);
		if (command == 's') { printf("TEXT WILL BE SCRAMBLED\n"); }
		else if (command == 'd') { printf("TEXT WILL BE DESCRAMBLED\n"); }
		else { printf("invalid input please retry\n"); }
	}
	
	//---------------------------------Printing out number of character in file-and allocating a char array of that size---------------
    charcount = numofc(fname);
	//printf("char count is %d\n", charcount);
    filestring = (char*) malloc((charcount)*(sizeof(char)));

	//---------------------------------using getstring to store file contents into filestring---------------------------------------------
	getstring(fname, filestring);
	printf("before changes filecontents : %s\n", filestring);

	//----------------------------------Executing specified manipulation based on value of command-----------------------------------------

	if(command == 's' ){ editone(fname, filestring); }
	if (command == 'd') { undo_editone(fname, filestring); }

	printf("filecontents after specified changes : %s\n", filestring);

	//--------------------------------------freeing allocated memory----------------------------------------------------------------------
	//free(filestring);
	filestring = NULL;
	free(filestring);
	return 0;
}
