#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  initializeGame(2, k, 235, &G);

  int c1 = 0,
      c2 = 0,
      c3 = 0,
      bonus = 0;

  int currentPlayer = G.whoseTurn,
      nextPlayer = (currentPlayer + 1) % 2;

  printf("\n-----Testing the sea hag card implementation.-----\n");

  int dcount = G.deckCount[nextPlayer],
      disc = G.discardCount[nextPlayer];
  printf("\nBefore playing sea hag:\n");
  printf("Deckcount: %d\n", dcount);
  printf("Discardcount: %d\n", disc);
  
  int  starttop = G.deck[nextPlayer][G.deckCount[nextPlayer] - 1];
  cardEffect(sea_hag, c1, c2, c3, &G, 0, &bonus);
  printf("\nAfter playing sea hag:\n");
  printf("Discardcount: %d  ", G.discardCount[nextPlayer]);
  printf("(Expected: %d)\n", disc + 1);

  printf("Deckcount: %d  ", G.deckCount[nextPlayer]);
  printf("(Expected: %d)\n", dcount);

  int  top = G.deck[nextPlayer][G.deckCount[nextPlayer] - 1];
  printf("\nVerifying top of opponent's deck is a curse card...\n");
  if (top == curse) {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Top card is not a curse.\n");
  }

  printf("\nVerifying top of opponent's discard pile is the same that was ");
  printf("at the top of that player's deck before sea hag was played...\n");
  top = G.discard[nextPlayer][0];
  if (G.discardCount[nextPlayer] > 0)
  {
      top = G.discard[nextPlayer][G.discardCount[nextPlayer] - 1];
  }
  if (top == starttop) {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Cards do not match.\n");
  }

  return 0;

}