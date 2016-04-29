

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

//This unit test tests the buyCard function. Its pretty simple, 
//it just checks how many coins the player has, then attempts to buy a random card
//if the card costs more than the number of coins the player had, the playler shouldnt get
//the card added to their discard pile, if it costs less or the same then they should


int main() {

   printf("TESTING buyCard...\n");
   srand(time(NULL));
   int randomSeed = (4);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   //values are adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy
   //7,10,22,14,17,11,21,25,19,13 enum numberes
   //6,4,2,3,5,5,4,4,3,4 value of each in coins
   struct gameState g;
   struct gameState * game = &g;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);
   int size1,size2,coins,cost,r;

   size1 = game->discardCount[0];
   coins = game->coins;
   printf("NUMBER OF COINS IS %d\n",coins);
   printf("NUMBER OF CARDS IN DISCARD IS %d\n",size1);
   r = rand() % 10;
   printf("ATTEMPTING TO BUY CARD %d FOR %d COINS\n",r,getCost(kCards[r]));
   cost = getCost(kCards[r]);
   buyCard(kCards[r],game);

   size2 = game->discardCount[0];
   printf("NUMBER OF COINS IS %d\n",game->coins);
   printf("NUMBER OF CARDS IN DISCARD IS NOW %d\n",size2);
   
   if(cost < coins || cost == coins) {
      if(size1 != size2) 
	 printf("\nTEST PASSED\n");
      else
	 printf("\nTEST FAILED\n");
   }
   if(cost > coins) {
      if(size1 == size2)
	 printf("\nTEST PASSED\n");
      else
	 printf("\nTEST FAILED\n");
   }

   
   return 0;
}
