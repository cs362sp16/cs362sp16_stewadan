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

//Testing  card council_room

int main() {

   printf("TESTING CARD council_room...\n");
   int randomSeed = (3);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, council_room};
   struct gameState g;
   struct gameState * game = &g;
   int *bonus;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);
   int cards1, cards2, buys1, buys2;

   buys1 = game->numBuys;
   cards1 = numHandCards(game);
   printf("NUMBER OF CARDS IN PLAYER 0 HAND: %d\n",cards1);
   printf("NUMBER OF BUYS FOR PLAYER 0: %d\n",buys1);
   printf("PLAYING COUNCIL ROOM...\n");
   cardEffect(kCards[9],1,1,1,game,1,bonus);
   cards2 = numHandCards(game);
   buys2 = game->numBuys;
   printf("NUMBER OF CARDS IN PLAYER 0 HAND IS NOW: %d\n",cards2);
   printf("NUMBER OF BUYS FOR PLAYER 0 NOW: %d\n",buys2);
   //draws 4 cards and discards itself, so you should have 3 more cards
   if(cards2 == cards1+3)
      printf("\nTEST 1 PASSED\n");
   else
      printf("\NTEST 1 FAILED\n");
   //test the number of buys has gone up
   if(buys2 > buys1)
      printf("\nTEST 2 PASSED\n\n");
   else
      printf("\nTEST 2 FAILED\n\n");

   endTurn(game);
   cards1 = numHandCards(game);
   printf("NUMBER OF CARDS IN PLAYER 1 HAND: %d\n",cards1);
   if(cards1 == 6)
      printf("\nTEST 3 PASSED\n\n");
   else
      printf("\nTEST 3 FAILED\n\n");



   return 0;
}


