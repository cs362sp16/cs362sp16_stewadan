CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: $(unittest*.c) $(cardtest*.c) dominion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	rm -f unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randomtestadventurer.out: dominion.o randomtestadventurer.c 
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o interface.o $(CFLAGS)
	rm -f randomtestadventurer.out
	./randomtestadventurer 42 >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out

randomtestcard1.out: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	rm -f randomtestcard1.out
	./randomtestcard1 42 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out

randomtestcard2.out: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	rm -f randomtestcard2.out
	./randomtestcard2 42 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard1.out

testdominion: dominion.o testdominion.c
	gcc -o testdominion testdominion.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	gcov dominion.c >> testdominion.out

all: playdom player testdominion
clean: 
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer.out randomtestcard1.out randomtestcard2.out player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM rtest1
