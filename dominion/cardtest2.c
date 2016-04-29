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

//testing minion card

int main() {

   printf("TESTING CARD minion...\n");
   int count = 0;
   while(count < 2) {
      int randomSeed = (3);
      int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState g;
      struct gameState * game = &g;
      int *bonus;
      memset(game,0,sizeof(struct gameState));
      initializeGame(2,kCards,randomSeed,game);
      int cards1,cards2,coins1,coins2;
      coins1 = game->coins;


      if(count == 0) {
         //first we test mode 1, which is to get 2 coins
         printf("NUMBER OF COINS: %d\n",coins1);
         printf("PLAYING MINION...\n");
         cardEffect(kCards[4],1,1,1,game,0,bonus);
         coins2 = game->coins;
         printf("NUMBER OF COINS: %d\n",coins2);
         if(coins2 == coins1+2)
            printf("\nTEST PASSED\n\n");
         else
            printf("\nTEST FAILED\n\n");
      }

      if(count == 1) {
         //then test mode 2, which is to discard your hand and draw 4 cards
         //player 1 should also discard and draw 4, since they'll have 5 cards
         cards1 = numHandCards(game);
         cardEffect(kCards[4],0,1,1,game,0,bonus);
         cards1 = numHandCards(game);
         printf("NUMBER OF CARDS IN PLAYER %d HAND: %d\n",whoseTurn(game),cards1); 
         if(cards1 == 4)
	    printf("\nTEST PASSED\n\n");
         else
	    printf("\nTEST FAILED\n\n");
         endTurn(game);
         cards2 = numHandCards(game);
         printf("NUMBER OF CARDS IN PLAYER %d HAND: %d\n",whoseTurn(game),cards2);
         if(cards2 == 4)
	    printf("\nTEST PASSED\n\n");
         else
	    printf("\nTEST FAILED\n\n");
      }
      count++;
   }

   return 0;
}


