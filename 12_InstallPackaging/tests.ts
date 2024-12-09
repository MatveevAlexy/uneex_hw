#include <check.h>
#include "guess.h"



#test to_roman_1
	fail_unless(strcmp(to_roman(1), "I") == 0);

#test to_roman_50
	fail_unless(strcmp(to_roman(50), "L") == 0);

#test to_roman_100
	fail_unless(strcmp(to_roman(100), "C") == 0);