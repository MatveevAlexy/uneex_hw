GENERATES = *.out makeMaze1.c makeMaze2.c makeMaze3.c

maze.out:	makeMaze.c 
	gcc $^ -o $@

maze1.out:	makeMaze1.c 
	gcc $^ -o $@

maze2.out:	makeMaze2.c 
	gcc $^ -o $@

maze3.out:	makeMaze3.c 
	gcc $^ -o $@

makeMaze1.c: makeMaze.c size.patch
	patch makeMaze.c -i size.patch -o makeMaze1.c

makeMaze2.c: makeMaze1.c sym.patch
	patch makeMaze1.c -i sym.patch -o makeMaze2.c

makeMaze3.c: makeMaze2.c rand.patch
	patch makeMaze2.c -i rand.patch -o makeMaze3.c

run: maze.out maze1.out maze2.out maze3.out
	./maze.out
	./maze1.out 10
	./maze2.out -0 14
	./maze3.out 42 *8 18

clean:
	rm $(GENERATES)