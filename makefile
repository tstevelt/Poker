PROG = Poker
LIB = $(PROG).a
XLIB = /usr/local/lib64/weblib.a /usr/local/lib64/shslib.a CactusKev/pokerlib.o
DEF = /usr/local/include
WEBDIR = /var/www/vhosts/silverhammersoftware/html
PRG = $(WEBDIR)/$(PROG).cgi

FILES = \
	$(LIB)(Poker.o)				\
	$(LIB)(AutoFoldOneHole.o)	\
	$(LIB)(AutoFoldTwoHole.o)	\
	$(LIB)(Deal.o)				\
	$(LIB)(EvalBet.o)			\
	$(LIB)(FindImage.o)			\
	$(LIB)(Functions.o)			\
	$(LIB)(GameFuncs.o)			\
	$(LIB)(GetInput.o)			\
	$(LIB)(InitDeck.o)			\
	$(LIB)(PaintBottom.o)		\
	$(LIB)(PaintButtons.o)		\
	$(LIB)(PaintScreen.o)		\
	$(LIB)(PaintStartup.o)		\
	$(LIB)(PaintStats.o)		\
	$(LIB)(PaintTop.o)			\
	$(LIB)(PayAnteToWinner.o)	\
	$(LIB)(SessionFuncs.o)		\
	$(LIB)(Shuffle.o)

.SILENT:

STAMP: $(PRG)

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -g -Wall -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): Poker.h $(DEF)/shslib.h $(DEF)/weblib.h

extra:
	cp -pv Poker.css $(WEBDIR)/Poker.css
	cp -pv Poker.js  $(WEBDIR)/Poker.js

clean:
	rm -f $(LIB)

all:
	make clean
	make
	make extra

.PRECIOUS: $(LIB)

