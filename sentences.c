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
struct line* readFile(FILE *fl){
	struct line *arr;
	size_t valueOfLines;
	char sValueOfLines[20];

	if(!fgets(sValueOfLines, sizeof(sValueOfLines), fl))
		return NULL;
	if(!(valueOfLines = atoi(sValueOfLines)))
		return NULL;

	arr = malloc(sizeof(struct line) * valueOfLines);

	char inputString[1000];
	for(size_t i = 0; i < valueOfLines; i++){
		if(!fgets(inputString, sizeof(inputString), fl))
			return NULL;

		arr[i]._line = malloc(sizeof(inputString));
		strcpy(arr[i]._line, inputString);
		arr[i].hash = getHash(arr[i]._line);
	}

	return arr;
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
int printUnique(const struct line *arr, const size_t valueOfLines){
	unsigned long long *hashes = malloc(valueOfLines * sizeof(unsigned long long));
	for(size_t i = 0; i < valueOfLines; i++){
		hashes[i] = arr[i].hash;
	}
	qsort(hashes, valueOfLines, sizeof(unsigned long long),
		(int (*)(const void*, const void*)) cmpULL);

	short *isPrinted = malloc(sizeof(short) * valueOfLines);
	memset(isPrinted, 0, sizeof(short) * valueOfLines);

	unsigned long long *pPos = NULL;
	size_t rPos;
	for(size_t i = 0; i < valueOfLines; i++){
		pPos = (unsigned long long *)bsearch(&arr[i].hash, hashes, valueOfLines,
			sizeof(hashes), 	(int (*)(const void*, const void*)) cmpULL);
		rPos = pPos - hashes;
		if(!isPrinted[rPos]){
			isPrinted[rPos] = 1;
			printf("%s\n", arr[i]._line);
		}
	}

	free(hashes);
	free(isPrinted);
	free(pPos);
	return EXIT_SUCCESS;
}
