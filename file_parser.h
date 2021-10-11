#ifndef FILE_PARSER
#define FILE_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie
{
    char *title;
    int year;
    char *langs[5];
    int num_langs;
    float rating;
    struct movie *next;
};

struct movie *createMovie(char*);
struct movie *processFile(char*);

#endif