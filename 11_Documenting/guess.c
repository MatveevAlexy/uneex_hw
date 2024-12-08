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
#define LOCALE_PATH "po" 

char *roman[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"}; /**< Table of translation from decimal to roman */

/** Turns @p num to roman notation.
 * 
 * @param num number to be transformed
 * @return Roman number equal to @p num
 */
char *to_roman(int num) {
    return roman[num - 1];
}

int main(int argc, char *argv[])
{
	int max_poss = 100, min_poss = 1, rom = 0;
    char ans[5];

    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf(_("The programm guesses number from 1 to 100. Options:\n-r -- to run with Roman numbers\n-h or --help -- to show this message\n"));
    } 

    if (argc > 1 && strcmp(argv[1], "-r") == 0) {
        rom = 1;
    } 

	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALE_PATH);
	textdomain (PACKAGE);

    if (rom) {
        puts(_("Think of a number from I to C.\n"));
    } else {
    	puts(_("Think of a number from 1 to 100.\n"));
    }

	while (min_poss < max_poss) {
        if (rom) {
            printf(_("Is your number greater than %s?\n"), to_roman((max_poss + min_poss) / 2));
        } else {
            printf(_("Is your number greater than %d?\n"), (max_poss + min_poss) / 2);
        }
        if (scanf("%s", ans) < 0) {
            return 1;
        }
        if (strcmp(ans, _("yes")) == 0) {
            min_poss = (max_poss + min_poss) / 2 + 1;
        } else if (strcmp(ans, _("no")) == 0) {
            max_poss = (max_poss + min_poss) / 2;
        } else {
            printf(_("Please answer yes or no.\n"));
        }
    }
    if (rom) {
        printf(_("Your number is %s.\n"), to_roman(max_poss));
    } else {
    	printf(_("Your number is %d.\n"), max_poss);
    }
	return 0;
}