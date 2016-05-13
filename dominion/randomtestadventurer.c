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

   int i,j,p,z,treasure1,treasure2,totalTreasure,*bonus;
   int RandSeed = atoi(argv[1]);

   int k[10] = {adventurer,council_room,feast,gardens,mine,remodel,smithy,gold,silver,copper};

   struct gameState G;


   /* 
    * Set up a random gamestate, we don't really care to check which player is playing the card as we're only checking
    * the implimentation of  the card itself, not the playcard function or anything like that 
    * so we always set deckCount, discardCount and handCount for the player to be a value less than their max value
    * we then fill these with random cards, choosing a random value from 0-9 and putting a card in from k
    */

   SelectStream(2);
   PutSeed(RandSeed);
   treasure1 = 0;
   printf("-------------------------------------------------\n");

   for(i=0;i<20;i++) {
      for(j=0;j<sizeof(struct gameState);j++) {
	 ((char*)&G)[j] = floor(Random() * 256);
      }
      G.deckCount[0] = floor(Random() * 100);
      for(z=0;z<G.deckCount[0];z++) {
	 p = floor(Random() * 10);
	 G.deck[0][z] = k[p];
      }
      G.discardCount[0] = floor(Random() * 100);
      for(z=0;z<G.discardCount[0];z++) {
	 p = floor(Random() * 10);
	 G.discard[0][z] = k[p];
      }
      G.handCount[0] = floor(Random() * 100);
      for(z=0;z<G.handCount[0];z++) {
	 p = floor(Random() * 10);
	 G.hand[0][z] = k[p];
      }
      //count the number of treasure cards in the players hand
      for(z=0;z<G.handCount[0];z++) {
	 if(G.hand[0][z] == 4 || G.hand[0][z] == 5 || G.hand[0][z] == 6)
	    treasure1++;
      }
      printf("INITIAL NUMBER OF TREASURE CARDS: %d\n",treasure1);
      totalTreasure = fullDeckCount(0,4,&G)+fullDeckCount(0,5,&G)+fullDeckCount(0,6,&G);
      printf("TOTAL NUMBER OF TREASURE CARDS: %d\n",totalTreasure);
      printf("PLAYING ADVENTURER...\n");
      G.whoseTurn = 0;
      cardEffect(k[0],1,1,1,&G,0,bonus);

      for(z=0;z<G.handCount[0];z++) {
	 if(G.hand[0][z] == 4 || G.hand[0][z] == 5 || G.hand[0][z] == 6)
	    treasure2++;
      }
      printf("NUMBER OF TREASURE CARDS NOW: %d\n",treasure2);
      if(treasure2 == treasure1+2)
	 printf("\n---PASSED\n\n");
      else if(totalTreasure == treasure1)
	 printf("\n---PASSED*\n\n");    //put passed here, since if all the treasure cards are in the hand you can't get any from the deck/discard
      else if(treasure1-1 == totalTreasure && treasure1+1 == treasure2)
	 printf("\n---PASSED\n\n");
      else
	 printf("\n---FAILED\n\n");
      treasure1=0;
      treasure2=0;
   }
   printf("-------------------------------------------------\n");

   return 0;
}
