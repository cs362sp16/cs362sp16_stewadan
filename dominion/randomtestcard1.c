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

   int i,j,p,z,coins1,coins2,price,*bonus,randCard;
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
      G.deckCount[0] = floor(Random() * 20);
      for(z=0;z<G.deckCount[0];z++) {
	 p = floor(Random() * 10);
	 G.deck[0][z] = k[p];
      }
      G.discardCount[0] = floor(Random() * 20);
      for(z=0;z<G.discardCount[0];z++) {
	 p = floor(Random() * 10);
	 G.discard[0][z] = k[p];
      }
      G.handCount[0] = floor(Random() * 20);
      for(z=0;z<G.handCount[0];z++) {
	 p = floor(Random() * 10);
	 G.hand[0][z] = k[p];
      }
      G.handCount[0] = G.handCount[0]+1;
      G.hand[0][G.handCount[0]-1] = k[6];
      //salvager will crash when you try to call discardcard with 0 if playedcardcount isn't set to something
      G.playedCardCount = 0;
      G.whoseTurn = 0;
      G.coins = 0;
      //set initial amount of coints to 0
      printf("\n");
      printf("COINS ARE: %d\n",G.coins);
      randCard = floor(Random() * (G.handCount[0]-2));
      printf("Trying to sell card %d\n",G.hand[0][randCard]);
      printf("for: %d\n",getCost(G.hand[0][randCard]));
      price = getCost(G.hand[0][randCard]);
      coins1 = G.coins;
      
      printf("PLAYING SALVAGER...\n");
      cardEffect(salvager,randCard,1,1,&G,G.handCount[0]-1,bonus);
      printf("COINS ARE NOW: %d\n",G.coins);
      coins2 = G.coins;


      if(coins2 == coins1+price)
	 printf("\n---PASSED\n");
      else
	 printf("\n---FAILED\n");

   }


   printf("\n");

   return 0;
}

