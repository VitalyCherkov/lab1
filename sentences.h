#ifndef sentences_h
#define sentences_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line{
  char *_line;
  unsigned long long hash;
};

int readFile(FILE *fl, struct line **arr);

int cmpULL(const void *a, const void *b);
int printUnique(const struct line *arr, const size_t numberOfLines);

#endif
