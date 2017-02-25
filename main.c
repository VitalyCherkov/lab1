#include <stdio.h>
#include <stdlib.h>
#include "sentences.h"

int main(int argv, char *args[]){

	if(argv != 2){
		printf("Usage: fileName\n");
		return EXIT_FAILURE;
	}

	FILE *fl = NULL;
	if(!(fl = fopen(args[1], "r"))){
		printf("Incorrect fileName: %s\n", args[1]);
		return EXIT_FAILURE;
	}

	struct line *arr = NULL;
	if(!readFile(fl, arr)){
		printf("Can not read file %s\n", args[1]);
		printf("Format of file:\n");
		printf("First line - number N of strings, then N lines ending with '\\n'\n");
		return EXIT_FAILURE;
	}

	if(!sizeof(arr)){
		printf("There is no strings in your file\n");
		return EXIT_FAILURE;
	}

	printUnique(arr, sizeof(arr) / sizeof(arr[0]));

	free(fl);
	free(arr);
	return EXIT_SUCCESS;
}

