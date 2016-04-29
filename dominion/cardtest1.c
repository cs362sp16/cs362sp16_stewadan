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

//Testing smithy card

int main() {

   printf("TESTING CARD smithy...\n");
   int randomSeed = (3);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   struct gameState g;
   struct gameState * game = &g;
   int *bonus;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);
   int cards1,cards2;
   cards1 = numHandCards(game);
   printf("NUMBER OF CARDS IN HAND: %d\n",cards1);
   printf("PLAYING SMITHY...\n");
   cardEffect(kCards[9],1,1,1,game,0,bonus);
   cards2 = numHandCards(game);
   printf("NUMBER OF CARDS IN HAND: %d\n",cards2);

   //smithy draws 3 cards and discards itself, so we should have +2 cards
   if(cards2 == cards1+2)
      printf("\nTEST PASSED\n");
   else
      printf("\nTEST FAILED\n");


   return 0;
}


