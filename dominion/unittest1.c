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

//This unit test tests the whosTurn function, there are only 2 players
//player 0 and player 1, so it should start on player 0, go to 1, go back to 0
//and go to 1 again

int main() {

   int randomSeed = (3);
   int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   struct gameState g;
   struct gameState * game = &g;
   int turn[4];
   int passing = 1;
   memset(game,0,sizeof(struct gameState));
   initializeGame(2,kCards,randomSeed,game);

   //Test the whoseTurn function here
   printf("Testing whoseTurn...\n");
   int i;
   for(i=0;i<4;i++) {
      turn[i] = whoseTurn(game);
      endTurn(game);
      printf("PLAYER %d TURN\n",turn[i]);
   }
   for(i=0;i<2;i++) {
      if(turn[i] != turn[i+2]) {
	 passing = 0;
      }
   }
   if(passing == 1)
      printf("TESTS PASS\n");
   else
      printf("TESTS FAILED.\n");

   return 0;

}
