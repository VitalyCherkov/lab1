#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sentences.h"

// Вычисление хэша строки
static unsigned long long getHash(const char *str){
	const unsigned long long P = 51;
	unsigned long long p = 1;
	unsigned long long result = 0;

	for(; *str != '\0'; str++){
		result += *str * p;
		p *= P;
	}

	return result;
}

// Ввод текстового файла
int readFile(FILE *fl, struct line **arr){
	size_t numberOfLines;
	char sNumberOfLines[20];

	if(!fgets(sNumberOfLines, sizeof(sNumberOfLines), fl)){
		*arr = NULL;
		return 0;
	}
	if(!(numberOfLines = atoi(sNumberOfLines))){
		*arr = NULL;
		return 0;
	}

	*arr = malloc(sizeof(struct line) * numberOfLines);

	char inputString[1000];
	for(size_t i = 0; i < numberOfLines; i++){
		if(!fgets(inputString, sizeof(inputString), fl)){
			*arr = NULL;
			return 0;
		}

		(*arr)[i]._line = malloc(sizeof(inputString));
		strcpy((*arr)[i]._line, inputString);
		(*arr)[i].hash = getHash((*arr)[i]._line);
	}

	return numberOfLines;
}

// Компаратор для анс. логн лонг
int cmpULL(const unsigned long long *a, const unsigned long long *b){
	if(*a > *b)
		return 1;
	if(*a < *b)
		return -1;
	return 0;
}

// Нахождение уникальных строк
int printUnique(const struct line *arr, const size_t numberOfLines){
	unsigned long long *hashes = malloc(numberOfLines * sizeof(unsigned long long));
	for(size_t i = 0; i < numberOfLines; i++){
		hashes[i] = arr[i].hash;
	}
	qsort(hashes, numberOfLines, sizeof(unsigned long long),
		(int (*)(const void*, const void*)) cmpULL);

	short *isPrinted = malloc(sizeof(short) * numberOfLines);
	memset(isPrinted, 0, sizeof(short) * numberOfLines);

	unsigned long long *pPos = NULL;
	size_t rPos;
	for(size_t i = 0; i < numberOfLines; i++){
		pPos = (unsigned long long *)bsearch(&arr[i].hash, hashes, numberOfLines,
			sizeof(hashes), 	(int (*)(const void*, const void*)) cmpULL);
		rPos = pPos - hashes;
		if(!isPrinted[rPos]){
			isPrinted[rPos] = 1;
			printf("%s", arr[i]._line);
		}
	}

	free(hashes);
	free(isPrinted);
	//free(pPos);
	return EXIT_SUCCESS;
}
