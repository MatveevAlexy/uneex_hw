TRASH = *.o r *.out
CFLAGS = -O0 -g

all: r

r: range.c
	gcc $^ $(CFLAGS) -o $@

clean:
	rm -rf $(TRASH)

test: r
	gdb --batch --quiet -x 1.gdb r | grep '@@@' > 1.out
	gdb --batch --quiet -x 2.gdb r | grep '@@@' > 2.out
	cmp 1.out 1.tst
	cmp 2.out 2.tst
