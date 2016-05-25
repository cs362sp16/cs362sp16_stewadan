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


char *cardNames[] = {"curse","estate","duchy","province","copper","silver","gold","adventurer","council_room","feast", "gardens","mine", "remodel", "smithy","village","baron", "great_hall","minion","steward","tribute","ambassador","cutpurse","embargo","outpost","salvager","sea_hag","treasure_map"};


int countCoins(int player, struct gameState *game);

void TakeTurn(int player, int *turnNum, struct gameState *game,int kCards[], int *bonus);

int main(int argc, char* argv[]) { 
   if(argc != 2) {
      printf("USAGE ERROR: PROVIDE RANDOM SEED\n");
      return 0;
   }
   int RandSeed = atoi(argv[1]);
   int i,r,r1,player,playerNum;
   int *bonus = NULL;
   int turnNum = 0;
   int AllCards[] = {adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall,minion,steward,tribute,ambassador,cutpurse,embargo,outpost,salvager,sea_hag,treasure_map};
   int CountCards[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   int kCards[] = {0,0,0,0,0,0,0,0,0,0};
   SelectStream(1);
   PutSeed(RandSeed);

   for(i=0;i<10;i++) {
      r = floor(Random() * 20);
      while(CountCards[r] != 0) {
         r = floor(Random() * 20);
      }
      r1 = AllCards[r];
      CountCards[r] = 1;
      kCards[i] = r1;
   }

   //decide how many players, from 2-4
   int rplayers = floor(Random() * 3) + 2;
   //create a vector to hold the players, fill it with that players number, starting at 1 not 0
   int *players = (int*)calloc(rplayers,sizeof(int));
   
   for(i=0;i<rplayers;i++) {
      players[i] = i;
   }

   //initiate the game with all of our data
   struct gameState g;
   struct gameState * game = &g;
   memset(game,0,sizeof(struct gameState));
   initializeGame(rplayers,kCards,RandSeed,game);

   //play the game
   int GameOver = 0;	//keep track of whether or not the game is still going
   while(!GameOver) {
      for(i=0;i<rplayers;i++) {
         player = whoseTurn(game);
	 //have bot player take their turn
	 TakeTurn(i,&turnNum,game,kCards,&bonus);
	 GameOver = isGameOver(game);
	 if(GameOver == 1){
	    printSupply(game);
	    printScores(game);
	    getWinners(players, game);
	    printf("After %d turns, the winner(s) are:\n", turnNum);
	    for(playerNum = 0; playerNum < game->numPlayers; playerNum++){
	       if(players[playerNum] == WINNER) { 
		  printf("Player %d\n", playerNum);
	       }
	    }
	    for(playerNum = 0; playerNum < game->numPlayers; playerNum++){
	       printHand(playerNum, game);
	       printPlayed(playerNum, game);
	       printDiscard(playerNum, game);
	       printDeck(playerNum, game);
	    }
	    break;
	 }
      }
      turnNum++;
      GameOver = isGameOver(game);
   }
   return 0;
}

int countCoins(int player, struct gameState *game) {
  int card, index, coinage = 0;
  for(index = 0; index < game->handCount[player]; index++) {
    card = game->hand[player][index];
    switch(card) {
    case copper: coinage = coinage+1;
      break;
    case silver: coinage = coinage+2;
      break;
    case gold: coinage = coinage+3;
      break;
    }
  }
  return coinage;
}

int countCoinCards(int player, struct gameState *game) {
   int card, index, coins = 0;
 
   for(index = 0; index < game->handCount[player]; index++) {
      card = game->hand[player][index];
      switch(card) {
      case copper: coins++;
        break;
      case silver: coins++;
        break;
      case gold: coins++;
        break;
      }
   }

   return coins;

}

int countVictoryCards(int player, struct gameState *game) {
   int card, index, victories = 0;
 
   for(index = 0; index < game->handCount[player]; index++) {
      card = game->hand[player][index];
      switch(card) {
      case estate: victories++;
        break;
      case duchy: victories++;
        break;
      case province: victories++;
        break;
      }
   }

   return victories;

}

void TakeTurn(int player, int *turnNum, struct gameState *game, int kCards[], int *bonus) {
  int i,choice,j,cardToBuy,cardToPlay,canBuy = 0;
  int cardsToBuy[] = {0,0,0,0,0,0,0,0,0,0};
  int cardsToPlay[] = {0,0,0,0,0};
  int coins = countCoins(player, game);
  int numVictories = countVictoryCards(player, game);
  int numCoins = countCoinCards(player, game);
  printf("*****************Executing Bot Player %d Turn Number %d*****************\n", player, *turnNum);
  printSupply(game);	
  //sleep(1); //Thinking...

  j = 0;
  //check to see if player can afford any of the cards
  for(i=0;i<10;i++) {
     if(getCost(kCards[i]) <= coins && supplyCount(kCards[i],game) > 0) {
	canBuy++;
	cardsToBuy[j] = kCards[i];
	j++;
     }
  }

  //roll a random number, to either buy a kingdom card, buy a province/money card.
  choice = floor(Random() * 2);
  //if all you have are victory cards and money, can't play anything.
  if(choice == 1 || canBuy == 0) {
     if(coins >= PROVINCE_COST && supplyCount(province,game) > 0) {
	buyCard(province,game);
        printf("Player %d buys card province\n\n", player);
     }
     else if(coins >= GOLD_COST && supplyCount(gold,game) > 0) {
	buyCard(gold,game);
	printf("Player %d buys card gold\n\n", player);
     }
     else if(supplyCount(province,game) == 0 && coins >= DUCHY_COST ) {
	buyCard(duchy,game);
        printf("Player %d buys card duchy\n\n", player);
     }
     else if(coins >= SILVER_COST && supplyCount(silver,game) > 0) {
	buyCard(silver,game);
	printf("Player %d buys card silver\n\n", player);
     }
     else if(supplyCount(estate,game) == 0 && coins >= ESTATE_COST ) {
	buyCard(estate,game);
        printf("Player %d buys card estate\n\n", player);
     }
     else if(supplyCount(copper,game) == 0) {
	buyCard(copper,game);
        printf("Player %d buys card copper\n\n", player);
     }
  }
  else if(choice == 0 && canBuy > 0) {
     cardToBuy = floor(Random() * j);
     printf("Player %d buys card %s\n\n",player,cardNames[cardsToBuy[cardToBuy]]);
     if (buyCard(cardsToBuy[cardToBuy],game) > 0)
	printf("ERROR: could not buy card %s\n\n",cardNames[cardsToBuy[cardToBuy]]);
  }

  j = 0;
  //see if the player can play a card from their hand
  if( numHandCards(game) > numCoins+numVictories) {
     for(i=0;i<numHandCards(game);i++) {
	if(game->hand[player][i] > 6) {
	   cardsToPlay[j] = i;
	   j++;
	}
     }
     cardToPlay = floor(Random() * j);
     printf("Player %d plays card %s\n\n",player,cardNames[game->hand[player][cardsToPlay[cardToPlay]]]);
     if (cardEffect(cardsToPlay[cardToPlay],0,1,2,game,cardsToPlay[cardToPlay],bonus) > 0)
	printf("ERROR: Could not play card %s\n\n",cardNames[game->hand[player][cardsToPlay[cardToPlay]]]);
  }

  endTurn(game);
}
