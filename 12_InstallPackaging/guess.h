#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include "config.h"

/** @file guess.c
 * Programm guesses number from 1 to 100 based on user input. Can be run with -r parameter to switch to roamn numbers.
 */

#define _(STRING) gettext(STRING) /**< Shortened name for gettext */

/** Turns @p num to roman notation.
 * 
 * @param num number to be transformed
 * @return Roman number equal to @p num
 */
char *to_roman(int num);