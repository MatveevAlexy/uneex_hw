GENERATES = prog README prog-a prog-so liboutput.so liboutput_static.a
TRASH = *.o *~ o.* output*
CFLAGS = -fPIC

all:    README prog prog-a prog-so

prog-so:	prog.o liboutput.so
	cc $^ -o $@

prog-a:	prog.o liboutput_static.a
	cc $^ -o $@

liboutput_static.a: fun.o const.o
	ar r $@ $^
	ranlib $@

liboutput.so: fun.o const.o
	cc -shared -fPIC -o $@ $^

prog:   const.o fun.o prog.o

README: prog
	./$< 2> $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)
	rm -f $(GENERATES)

distclean:      clean
	rm -f $(GENERATES) 

test:	prog prog-a prog-so
	./prog 2> output
	./prog-a 2> output-a
	./prog-so 2> output-so
	sed -i 's/prog-a/prog/' output-a
	sed -i 's/prog-so/prog/' output-so
	./prog 1 >> output
	./prog-a 1 >> output-a
	./prog-so 1 >> output-so
	sed -i 's/prog-a/prog/' output-a
	sed -i 's/prog-so/prog/' output-so
	./prog 1 2 3 >> output
	./prog-a 1 2 3 >> output-a
	./prog-so 1 2 3 >> output-so
	sed -i 's/prog-a/prog/' output-a
	sed -i 's/prog-so/prog/' output-so
	cmp output output-a
	cmp output output-so
