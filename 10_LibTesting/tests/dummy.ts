#include <check.h>
#include "buf.h"


float *a = 0;

#test capacity_init
	fail_unless(buf_capacity(a) == 0);

#test size_init
	fail_unless(buf_size(a) == 0);

#test test1
	buf_push(a, 1.3f);
	fail_unless(buf_size(a) == 1);

#test value
	fail_unless(a[0] == (float)1.3f);

#test clear
	buf_clear(a);
	fail_unless(buf_size(a) == 0);

#test free
	buf_free(a);
    fail_unless(a == 0);

#test clear_empty
    buf_clear(a);
    fail_unless(buf_size(a) == 0);

#test clear_no_op
    fail_unless(a == 0);

#test size_10000
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    fail_unless(buf_size(ai) == 10000);

#test match_10000
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    fail_unless(match == 10000);

#test grow_1000
    buf_free(ai);
    buf_grow(ai, 1000);
    fail_unless(buf_capacity(ai) == 1000);

#test size_0_grow
    fail_unless(buf_size(ai) == 0);

#test trunc_100
    buf_trunc(ai, 100);
    fail_unless(buf_capacity(ai) == 100);
    buf_free(ai);


#test size_4
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    fail_unless(buf_size(a) == 4);

#test pop_3
    fail_unless(buf_pop(a) == (float)1.4f);

#test size_3
    buf_trunc(a, 3);
    fail_unless(buf_size(a) == 3);

#test pop_2
    fail_unless(buf_pop(a) == (float)1.3f);

#test pop_1
    fail_unless(buf_pop(a) == (float)1.2f);

#test pop_0
    fail_unless(buf_pop(a) == (float)1.1f);

#test size_0_pop
    fail_unless(buf_size(a) == 0);
    buf_free(a);