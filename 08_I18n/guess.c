#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po" 

int main(int argc, char *argv[])
{
	int max_poss = 100, min_poss = 1;
    char ans[5];

	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALE_PATH);
	textdomain (PACKAGE);

	puts(_("Think of a number from 1 to 100.\n"));

	while (min_poss < max_poss) {
		printf(_("Is your number greater than %d?\n"), (max_poss + min_poss) / 2);
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
    printf(_("Your number is %d.\n"), max_poss);
	return 0;
}