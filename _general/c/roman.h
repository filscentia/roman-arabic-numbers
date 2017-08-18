#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>
#include <ctype.h>

#define OK 1
#define FAIL 0

typedef struct ROMAN_SETS {
    char high;
    char mid;
    char low;
} ROMAN_SETS;

typedef enum Conversion { TO_ROMAN,
                          TO_ARABIC,
                          UNDEFINED } Conversion;

int repeat(char input, int number, char *psBuffer);
int getRomanNumeral(int num, ROMAN_SETS symbols, char *psBuffer);
int fromArabicToRoman(int number, char *pRoman);
int fromRomanToArabic(char *psRoman,int *pNum);
int getValue(char roman);
int validate(char *psInput, char *psOutput, Conversion *pConv);
int compileRegexp();