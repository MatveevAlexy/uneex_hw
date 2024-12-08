@DX_RULES@

bin_PROGRAMS=guess

doxygen-doc/man/man1/guess.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1

pkgdata_DATA = ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo:	ru.po
		mkdir -p `dirname $@`
		msgfmt $< -o $@

ru.po: ru.pot
	msgmerge -U $@ $<

ru.pot: guess.pot guess.c
	xgettext --keyword=_ guess.c -o guess.new.pot
	cp guess.pot $@
	msgmerge -U $@ guess.new.pot

install-data-local:
		mkdir -p $(DESTDIR)/$(docdir)
		cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

clean:
	rm -rf *.cache doxygen-doc *.m4 compile config.* configure depcomp Doxyfile guess guess.o install-sh Makefile.in missing stamp* ru.pot ru *~
