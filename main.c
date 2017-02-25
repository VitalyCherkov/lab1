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
		printf("\tFirst line - number N (max: 100000) of strings\n");
		printf("\tThen N lines ending with '\\n'. Max lenth: 1000 (or 1001 with '\\n')\n");
		return EXIT_FAILURE;
	}

	if(!numberOfLines){
		printf("There is no strings in your file\n");
		return EXIT_FAILURE;
	}

	printUnique(arr, numberOfLines);

	for(size_t i = 0; i < numberOfLines; i++){
		free(arr[i]._line);
	}
	free(arr);

	return EXIT_SUCCESS;
}
