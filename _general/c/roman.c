
/* C (C99 specfication) implementation of Roman-Arabic number conversion
 */

#include "roman.h"

// Define the regular expressions to enable parsing of the input
// These are different from the ones in Java/NodeJS as the alternative operator didn't
// work as epxected. 
static char *regexArabic = "^\\s*([0-9]+)\\s*$";
static char *regexRoman = "^\\s*([IVXLCDMivxlcdm]+)\\s*$";
static regex_t regexArabicCompiled;
static regex_t regexRomanCompiled;

// Define the 'sets' for the Roman symbols
static ROMAN_SETS setUnits = {'X', 'V', 'I'};
static ROMAN_SETS setTens = {'C', 'L', 'X'};
static ROMAN_SETS setHundreds = {'M', 'D', 'C'};

/** 
 * Repeat the input number times in the buffer at psBuffer
 * @param {char} input character to duplicate
 * @param {int} number of times to duplicaate this
 * @param {char*} psBuffer to contain the duplicated charactes
 * @return success/failure
 */
int repeat(char input, int number, char *psBuffer)
{
    for (int i = 0; i < number; i++)
    {
        psBuffer[i] = input;
    }
    return OK;
}

/**
 * Given a number, a set, and the output buffer, create the corect sequence of 
 * Romon numerals
 *
 * @param {int} num the number to converted into Roman
 * @param {ROMAN_SETS} symbols to use for the conversion
 * @param {char*} psBuffer ptr to where to put the symbols
 * @return the number characters that have been added
 */
int getRomanNumeral(int num, ROMAN_SETS symbols, char *psBuffer)
{
    int addedCount = 0;

    if (num == 9)
    {
        *psBuffer = symbols.low;
        *(psBuffer + 1) = symbols.high;
        addedCount += 2;
    }
    else if (num == 4)
    {
        *psBuffer = symbols.low;
        *(psBuffer + 1) = symbols.mid;
        addedCount += 2;
    }
    else if (num >= 5)
    {
        *psBuffer = symbols.mid;
        repeat(symbols.low, num - 5, (psBuffer + 1));
        addedCount += (1 + (num - 5));
    }
    else
    {
        repeat(symbols.low, num, psBuffer);
        addedCount = num;
    }
    return addedCount;
}

int fromArabicToRoman(int number, char *pRoman)
{

    int i = number;
    int thousands, hundreds, tens, units;
    int cursor = 0;
    int rc;

    if (i < 1)
    {
        return 0;
    }

    thousands = (i / 1000);
    i -= thousands * 1000;
    hundreds = (i / 100);
    i -= hundreds * 100;
    tens = (i / 10);
    i -= tens * 10;
    units = i;

    rc = repeat('M', thousands, pRoman);
    cursor += thousands;

    rc = getRomanNumeral(hundreds, setHundreds, pRoman + cursor);
    cursor += rc;

    rc = getRomanNumeral(tens, setTens, pRoman + cursor);
    cursor += rc;

    rc = getRomanNumeral(units, setUnits, pRoman + cursor);
    cursor += rc;

    *(pRoman + cursor) = 0;
    return 1;
}

int getValue(char roman)
{
    int r = 0;
    switch (toupper(roman))
    {
    case 'I':
        r = 1;
        break;
    case 'V':
        r = 5;
        break;
    case 'X':
        r = 10;
        break;
    case 'L':
        r = 50;
        break;
    case 'C':
        r = 100;
        break;
    case 'D':
        r = 500;
        break;
    case 'M':
        r = 1000;
        break;
    default:
        r = 0;
        break;
    }

    return r;
}

int fromRomanToArabic(char *psRoman, int *pNum)
{
    int result = 0;

    int length = strlen(psRoman);
    char *pTemp;
    int lastValue = 0;
    int thisValue = 0;

    if (length < 1)
    {
        return 0;
    }

    pTemp = malloc(length + 2);
    strcpy(pTemp, psRoman);

    pTemp[length] = 'E';

    for (int i = length - 1; i >= 0; i--)
    {
        lastValue = getValue(pTemp[i + 1]);
        thisValue = getValue(pTemp[i]);

        if (thisValue < lastValue)
        {
            result -= thisValue;
        }
        else
        {
            result += thisValue;
        }
    }

    free(pTemp);
    *pNum = result;
    return 1;
}

int main(int i, char **argv)
{

    FILE *pif;
    int rc;
    printf("Roman<->Arabic Number coversion - C Implementation\n\n");

    compileRegexp();

    if (i == 3)
    {
        if (strcmp(argv[1], "--file") == 0)
        {
            char pStr[30];
            char pTemp[30];// = malloc(30 * sizeof(char));
            printf("Processing File %s\n---START---\n", argv[2]);
            pif = fopen(argv[2], "r");
            while (fgets(pStr, 30,pif) != NULL)
            {
                Conversion conv;
                //printf("\nProcessing line :%s:\n",pStr);

                pStr[strcspn(pStr, "\n")] = 0;
                // printf("After :%s:\n",pStr);
                                //  continue;
                int valid = validate(pStr, pTemp, &conv);
                if (valid)
                {
                    if (conv == TO_ROMAN)
                    {
                        rc = fromArabicToRoman(atoi(pStr), pTemp);
                        if (rc)
                        {
                            printf("%s,%s\n", pStr, pTemp);
                        }
                        else
                        {
                            printf("%s,ERROR\n", pStr);
                        }
                    }
                    else
                    {
                        int value;
                        rc = fromRomanToArabic(pTemp, &value);
                        if (rc){
                        printf("%s,%d\n", pStr, value);
                        }  else
                        {
                            printf("%s,ERROR\n", pStr);
                        }
                    }
                }
                else
                {
                    printf("%s,ERROR\n", pStr);
                }
            }
            fclose(pif);
            printf("---END---\n");
            // free(pStr);
            //free(pTemp);
        }
    }

    regfree(&regexArabicCompiled);
    regfree(&regexRomanCompiled);

    return 0;
}

int compileRegexp()
{
    // compile the Arabic regexp
    int rc = regcomp(&regexArabicCompiled, regexArabic, REG_EXTENDED);
    if (rc)
    {
        printf("Could not compile regular expression.\n");
        char buf[256];
        regerror(rc, &regexArabicCompiled, buf, sizeof(buf));
        fprintf(stderr, "regcomp: %s\n", buf);
        return 0;
    };

    // compile the Roman regexp
    rc = regcomp(&regexRomanCompiled, regexRoman, REG_EXTENDED);
    if (rc)
    {
        printf("Could not compile regular expression.\n");
        char buf[256];
        regerror(rc, &regexRomanCompiled, buf, sizeof(buf));
        fprintf(stderr, "regcomp: %s\n", buf);
        return 0;
    };

    return 1;
}

int validate(char *psInput, char *psOutput, Conversion *pConv)
{
    size_t maxGroups = 2;
    regmatch_t groupArray[maxGroups];
    char *cursor;
    Conversion result = UNDEFINED;

    cursor = psInput;
    if (!regexec(&regexRomanCompiled, cursor, maxGroups, groupArray, 0))
    {
        unsigned int g = 1;
        if (groupArray[g].rm_so != (size_t)-1)
        {
            int length = groupArray[g].rm_eo - groupArray[g].rm_so;
            // roman = malloc(length + 1);
            strcpy(psOutput, cursor + groupArray[g].rm_so);
            psOutput[length] = 0;
            result = TO_ARABIC;
        }
    }
    cursor = psInput;

    if (!regexec(&regexArabicCompiled, cursor, maxGroups, groupArray, 0))
    {
        unsigned int g = 1;
        if (groupArray[g].rm_so != (size_t)-1)
        {
            int length = groupArray[g].rm_eo - groupArray[g].rm_so;
            // arabic = malloc(length + 1);
            strcpy(psOutput, cursor + groupArray[g].rm_so);
            psOutput[length] = 0;
            result = TO_ROMAN;
        }
    }

    if (result == UNDEFINED)
    {
        return 0;
    }
    else
    {
        *pConv = result;
        return 1;
    }
}
