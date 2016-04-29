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


//This unit test is desgined to test the draw function
//First, it will have player 0 discard a card and draw a card
//it will then check to make sure that the number of cards in 
//the players hand are equal before and after
//It will then discard teh players entire hand and draw a single card
//it will then check that the player has 1 card in hand 
//it does this for 5 random seeds

int main() {

   int count = 0;
   printf("Testing drawCard...\n");
      int x = rand() % 100;
      int randomSeed = (x);
      int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState g;
      struct gameState * game = &g;
      int cardsInHand1, cardsInHand2,i;
      memset(game,0,sizeof(struct gameState));
      initializeGame(2,kCards,randomSeed,game);

      cardsInHand1 = numHandCards(game);
      printf("PLAYER HAS %d CARDS\n",cardsInHand1);
      printf("DRAWING A CARD...\n");
      drawCard(0,game);
      cardsInHand2 = numHandCards(game);
      printf("PLAYER NOW HAS %d CARDS\n",cardsInHand2);
      if(cardsInHand1 == cardsInHand2)
	 printf("\nFIRST TEST FAILED\n");
      else
	 printf("\nFIRST TEST PASSED\n");

      cardsInHand1 = numHandCards(game);
      printf("\nPLAYER HAS %d CARDS\n",cardsInHand1);
      printf("DISCARDING A CARD...\n");
      discardCard(1,0,game,0);
      cardsInHand2 = numHandCards(game);
      printf("PLAYER NOW HAS %d CARDS\n",cardsInHand2);
      printf("DRAWING A CARD...\n");
      drawCard(0,game);
      cardsInHand2 = numHandCards(game);
      printf("PLAYER NOW HAS %d CARDS\n",cardsInHand2);
      if(cardsInHand1 == cardsInHand2)
         printf("\nSECOND TEST PASSED\n");
      else
         printf("\nSECOND TEST FAILED\n");


      printf("\nDISCARDING ENTIRE HAND...\n");
      for(i=0;i<5;i++) {
         discardCard(i,0,game,0);
      }
      printf("PLAYER HAS %d CARDS IN HAND\n",numHandCards(game));
      printf("DRAWING A CARD...\n");
      drawCard(0,game);
      printf("PLAYER NOW HAS %d CARDS IN HAND\n",numHandCards(game));

      if(numHandCards(game) > 0) 
         printf("\nTHIRD TEST PASSED\n\n");
      else
         printf("\nTHIRD TESTE FAILED\n\n");
      count++;

      return 0;

}
