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

  int currentPlayer = G.whoseTurn;

  printf("\n-----Testing the adventurer card implementation.-----\n");

  G.supplyCount[gold] = 5;
  G.supplyCount[silver] = 5;
  G.supplyCount[copper] = 5;
  G.supplyCount[baron] = 5;
  G.supplyCount[minion] = 5;
  gainCard(gold, &G, 1, currentPlayer);
  gainCard(silver, &G, 1, currentPlayer);
  gainCard(minion, &G, 1, currentPlayer);
  gainCard(baron, &G, 1, currentPlayer);
  gainCard(copper, &G, 1, currentPlayer);

  int hcount = G.handCount[currentPlayer],
      dcount = G.deckCount[currentPlayer],
      disc = G.discardCount[currentPlayer];
  printf("\nBefore playing adventurer:\n");
  printf("Handcount: %d\n", hcount);
  printf("Deckcount: %d\n", dcount);
  printf("Discardcount: %d\n", disc);

  printf("Top 5 cards in deck (most recently added first) are ");
  printf("copper, baron, minion, silver, gold.\n");
  
  cardEffect(adventurer, c1, c2, c3, &G, hcount-1, &bonus);
  printf("\nAfter playing adventurer:\n");
  printf("Handcount: %d  ", G.handCount[currentPlayer]);
  printf("(Expected: %d)\n", hcount + 1);

  printf("Discardcount: %d  ", G.discardCount[currentPlayer]);
  printf("(Expected: %d)\n", disc + 2);

  printf("Deckcount: %d  ", G.deckCount[currentPlayer]);
  printf("(Expected: %d)\n", dcount - 4);

  if (G.handCount[currentPlayer] != hcount + 1)
  {
      printf("Error: Hand count should reflect two additions, minus the discarded ");
      printf("adventurer card.\n");
  }

  if (G.discardCount[currentPlayer] != disc + 2)
  {
      printf("Error: Nothing was added to the discard pile.\n");
  }

  if (G.deckCount[currentPlayer] != dcount - 4)
  {
      printf("Error: Deck should have been reduced by four from drawing four cards.\n");
  }

  int i,
      top,
      hasSilver = 0,
      hasCopper = 0;

  for (i = 1; i < 3; i++)
  {
    top = G.hand[currentPlayer][G.handCount[currentPlayer] - i];
    if (top == copper) {
        hasCopper++;
    }
    if (top == silver) {
        hasSilver++;
    }
  }


  printf("\nVerifying top two cards of hand are a copper and a silver...\n");
  if (hasSilver == 1 && hasCopper == 1)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Top two are not 1 copper and 1 silver.\n");
  }

  int hasMinion = 0,
      hasBaron = 0;

  top = G.discard[currentPlayer][0];
  if (G.discardCount[currentPlayer] > 0)
  {
      top = G.discard[currentPlayer][G.discardCount[currentPlayer] - 1];
  }
  if (top == minion) {
      hasMinion++;
  }

  if (G.discardCount[currentPlayer] > 1)
  {
  top = G.discard[currentPlayer][G.discardCount[currentPlayer] - 2];
  }
  if (top == baron)
  {
      hasBaron++;
  }

  printf("\nVerifying baron and minion discarded into discard pile...\n");
  if (hasMinion == 1 && hasBaron == 1)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Discard does not show 1 baron and 1 minion.\n");
  }

  return 0;

}