SRCPATH=src/
BINPATH=bin/
TMPPATH=tmp/
PREFIX=stenc

all: makedirs $(PREFIX).y $(PREFIX).l
	gcc -o $(BINPATH)scc \
		-I $(SRCPATH) -I $(TMPPATH) \
	 	$(SRCPATH)main.c $(SRCPATH)symtab.c $(TMPPATH)scc.y.c $(TMPPATH)scc.lex.c -ly -lfl

$(PREFIX).y:
	yacc -o $(TMPPATH)scc.y.c -d -v $(SRCPATH)$(PREFIX).y

$(PREFIX).l:
	lex -o $(TMPPATH)scc.lex.c $(SRCPATH)$(PREFIX).l

makedirs:
	mkdir -p $(BINPATH)
	mkdir -p $(TMPPATH)

clean:
	rm *.o y.tab.c y.tab.h lex.yy.c a.out
