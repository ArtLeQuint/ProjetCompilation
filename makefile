SRCPATH=src/
BINPATH=bin/
TMPPATH=tmp/
PREFIX=compilateurStenC

all: makedirs $(PREFIX).y $(PREFIX).l
	gcc -o $(BINPATH)cfss \
		-I $(SRCPATH) -I $(TMPPATH) \
	 	$(TMPPATH)cfss.y.c $(TMPPATH)cfss.lex.c -ly -lfl

$(PREFIX).y:
	yacc -o $(TMPPATH)cfss.y.c -d -v $(SRCPATH)$(PREFIX).y

$(PREFIX).l:
	lex -o $(TMPPATH)cfss.lex.c $(SRCPATH)$(PREFIX).l

makedirs:
	mkdir -p $(BINPATH)
	mkdir -p $(TMPPATH)

clean:
	rm *.o y.tab.c y.tab.h lex.yy.c a.out
