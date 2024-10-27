GENERATES = move unlink.so *_file

all:	move unlink.so

move:	move.c
		gcc $^ -o $@

unlink.so:	unlink.c
		gcc -shared -fPIC $^ -o $@

test:	move unlink.so
		./test.sh
		

clean:
		rm $(GENERATES)
