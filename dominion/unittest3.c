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

int main() {

   printf("TESTING fullDeckCount...\n");
   int randomSeed = (4);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   //values are adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy
   //7,10,22,14,17,11,21,25,19,13 
   struct gameState g;
   struct gameState * game = &g;
   int deckCards,handCards,discardCards,totalCards1,totalCards2;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);

   int i,r,count,j;
   count = 0;
   j = 0;

   deckCards = game->deckCount[0];
   handCards = game->handCount[0];
   discardCards = game->discardCount[0];
   printf("NUMBER OF CARDS IN PLAYER %d DECK: %d\n",0,deckCards);
   printf("NUMBER OF CARDS IN PLAYER %d HAND: %d\n",0,handCards);
   printf("NUMBER OF CARDS IN PLAYER %d DISCARD: %d\n",0,discardCards);
   totalCards1 = deckCards + handCards + discardCards;
   for(i=0;i<27;i++) {
      totalCards2 = totalCards2 + fullDeckCount(0,i,game);
   }
   printf("FULL DECK COUNT FOR EVERY CARD IS %d\n",totalCards2);

   if(totalCards1 == totalCards2)
      printf("\nTEST PASSED\n");
   else
      printf("\nTEST FAILED\n");

   r = rand() % 2;
   while(count < 5) {
      if(r == 0) {
	 drawCard(0,game);
      }
      else if(r == 1) {
	 discardCard(j,0,game,0);
	 j++;
      }
      count++;
      r = rand() % 2;
   }

   totalCards2 = 0;
   deckCards = game->deckCount[0];
   handCards = game->handCount[0];
   discardCards = game->discardCount[0];
   printf("\nNUMBER OF CARDS IN PLAYER %d DECK: %d\n",0,deckCards);
   printf("NUMBER OF CARDS IN PLAYER %d HAND: %d\n",0,handCards);
   printf("NUMBER OF CARDS IN PLAYER %d DISCARD: %d\n",0,discardCards);
   totalCards1 = deckCards + handCards + discardCards;
   
   for(i=0;i<27;i++) {
      totalCards2 = totalCards2 + fullDeckCount(0,i,game);
   }
   printf("FULL DECK COUNT FOR EVERY CARD IS %d\n",totalCards2);

   if(totalCards1 == totalCards2)
      printf("\nTEST PASSED\n");
   else
      printf("\nTEST FAILED\n");



   


   return 0;
}
