#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

int main(int argc, char* argv[]) {


   if(argc != 2) {
      printf("USAGE ERROR\n");
      return 0;
   }

   int i,j,p,z,y,*bonus,check,buys1,buys2;
   int cardsBefore[] = {10,10,10,10,10,10};
   int cardsAfter[] = {0,0,0,0,0,0};
   int RandSeed = atoi(argv[1]);

   int k[10] = {adventurer,council_room,feast,gardens,mine,remodel,salvager,gold,silver,copper};

   struct gameState G;

   /* 
    * Set up a random gamestate, we don't really care to check which player is playing the card as we're only checking
    * the implimentation of  the card itself, not the playcard function or anything like that 
    * so we always set deckCount, discardCount and handCount for the player to be a value less than their max value
    * we then fill these with random cards, choosing a random value from 0-9 and putting a card in from k
    */

   SelectStream(2);
   PutSeed(RandSeed);
   printf("-------------------------------------------------\n");

   for(i=0;i<20;i++) {
      for(j=0;j<sizeof(struct gameState);j++) {
	 ((char*)&G)[j] = floor(Random() * 256);
      }
      p = floor(Random() * 2) + 2;
      G.numPlayers = p;
      for(y=0;y<G.numPlayers;y++) {
	 G.handCount[y] = floor(Random() * 20);
         for(z=0;z<G.handCount[y];z++) {
	    p = floor(Random() * 10);
	    G.hand[y][z] = k[p];
	 }
      }
      for(y=0;y<G.numPlayers;y++) {
	 G.discardCount[y] = floor(Random() * 20);
         for(z=0;z<G.discardCount[y];z++) {
	    p = floor(Random() * 10);
	    G.discard[y][z] = k[p];
	 }
      }
      for(y=0;y<G.numPlayers;y++) {
	 G.deckCount[y] = floor(Random() * 20);
         for(z=0;z<G.deckCount[y];z++) {
	    p = floor(Random() * 10);
	    G.deck[y][z] = k[p];
	 }
      }
      G.whoseTurn = 0;
      G.playedCardCount = 0;
      check = 1;
      buys1 = G.numBuys;

      for(z=0;z<G.numPlayers;z++) {
         printf("number of cards in Player %d's hand: %d\n",z+1,G.handCount[z]);
	 cardsBefore[z] = G.handCount[z];
      }
      printf("PLAYING COUNCIL ROOM...\n");
      cardEffect(council_room,1,1,1,&G,0,bonus);
      for(z=0;z<G.numPlayers;z++) {
         printf("number of cards in Player %d's hand now: %d\n",z+1,G.handCount[z]);
	 cardsAfter[z] = G.handCount[z];
      }
      for(z=0;z<G.numPlayers;z++) {
	 if(cardsBefore[z] > cardsAfter[z])
	    check = 0;
      }
      buys2 = G.numBuys;
      
      if(check == 1 && cardsAfter[0] == cardsBefore[0]+3 && buys2 == buys1+1)
	 printf("\n---PASSED\n\n");
      else
	 printf("\n---FAILED\n\n");

   }


   printf("-------------------------------------------------\n");

   return 0;
}
