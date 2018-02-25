#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/*NOTE:  This test should fail due to a bug introduced in Assignment 2 where
discardCard is called in the for loop (3 times) instead of after it.*/

int main(int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  initializeGame(2, k, 235, &G);

  int c1 = 0,
      c2 = 0,
      c3 = 0,
      bonus = 0;

  //Precondition: smithy in supply pile
  G.supplyCount[smithy] = 5;
  int currentPlayer = G.whoseTurn;

  printf("\n-----Testing the smithy card implementation.-----\n");

  gainCard(smithy, &G, 2, currentPlayer);
  int hcount = G.handCount[currentPlayer];

  printf("\nAdding one smithy. \nHandcount: %d\n", hcount);
  printf("Deckcount: %d\n", G.deckCount[currentPlayer]);
  int dcount = G.deckCount[currentPlayer],
      pcount = G.playedCardCount;

  cardEffect(smithy, c1, c2, c3, &G, hcount, &bonus);
  printf("\nAfter playing smithy:\n");
  printf("Handcount: %d  ", G.handCount[currentPlayer]);
  printf("(Expected: %d)\n", hcount + 2);

  printf("Deckcount: %d  ", G.deckCount[currentPlayer]);
  printf("(Expected: %d)\n", dcount);

  printf("\nVerifying 3 cards gained and 1 discarded...\n");
  //Should equal stored hcount plus 3 added card minus played smithy
  if (G.handCount[currentPlayer] == hcount + 2)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Hand count inconsistent.\n");
  }

  printf("\nVerifying card discarded into played card pile...\n");
  if (G.playedCardCount == pcount + 1)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Played card count inconsistent (");
      printf("%d vs. %d expected).\n", G.playedCardCount, pcount+1);
  }

  return 0;

}