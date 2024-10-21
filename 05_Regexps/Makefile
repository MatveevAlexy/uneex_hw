GENERATES = *.out esub

esub:	esub.c
		gcc $^ -o $@

test:	esub
		echo '1234567890' | sed -E 's/([1-5])*([6-9])*/\2\1/' >> sed.out
		./esub '([1-5])*([6-9])*' '\2\1' '1234567890' >> esub.out
		echo 'abcabcabc' | sed -E 's/c/C/' >> sed.out
		./esub 'c' 'C' 'abcabcabc' >> esub.out
		echo 'abcabcabc' | sed -E 's/(c)(a)/0\21\12/' >> sed.out
		./esub '(c)(a)' '0\21\12' 'abcabcabc' >> esub.out
		echo 'This is letters' | sed -E 's/([a-z]*$$)/nothing/' >> sed.out
		./esub '([a-z]*$$)' 'nothing' 'This is letters' >> esub.out
		cmp sed.out esub.out

clean:
		rm $(GENERATES)