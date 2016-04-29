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

//Testing card village

int main() {
   printf("TESTING CARD village...\n");
   int randomSeed = (3);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, council_room};
   struct gameState g;
   struct gameState * game = &g;
   int *bonus;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);
   int cards1,cards2,actions1,actions2;
   cards1 = numHandCards(game);
   actions1 = game->numActions;
   printf("NUMBER OF CARDS IN PLAYER 0 HAND: %d\n",cards1);
   printf("NUMBER OF ACTIONS FOR PLAYER 0: %d\n",actions1);
   printf("PLAYING VILLAGE...\n");
   cardEffect(kCards[3],1,1,1,game,1,bonus);
   cards2 = numHandCards(game);
   actions2 = game->numActions;
   printf("NUMBER OF CARDS IN PLAYER 0 HAND NOW: %d\n",cards2);
   printf("NUMBER OF ACTIONS FOR PLAYER 0 NOW: %d\n",actions2);
   if(cards1 == cards2)
      printf("\nTEST PASSED\n");
   else
      printf("\nTEST FAILED\n");
   if(actions2 == actions1+2)
      printf("\nTEST PASSED\n");
   else
      printf("\nTEST FAILED\n");
   return 0;
}
