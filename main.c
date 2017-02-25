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
	size_t numberOfLines = readFile(fl, &arr);

	if(!arr){
		printf("Can not read file %s\n", args[1]);
		printf("Format of file:\n");
		printf("First line - number N of strings, then N lines ending with '\\n'\n");
		return EXIT_FAILURE;
	}

	if(!numberOfLines){
		printf("There is no strings in your file\n");
		return EXIT_FAILURE;
	}

	printUnique(arr, numberOfLines);

	printf("\n\nOK\n\n");

	free(arr);
	return EXIT_SUCCESS;
}
