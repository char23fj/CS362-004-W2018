#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testGain(int after, int before, int extra)
{
    if (after == before + extra)
    {
        printf("Passed.\n");
    }

    else if (extra == 0)
    {
        printf("Failed.  No cards should have been added.\n");
    }

    else
    {
        printf("Failed.  %d card(s) should have been added.\n", extra);
    }
}

int main(int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  initializeGame(2, k, 235, &G);

  //Precondition: no gold in supply pile
  G.supplyCount[gold] = 0;

  int currentPlayer = G.whoseTurn;

  printf("\n-----Testing the gainCard function implementation.-----\n");

  int hcount = G.handCount[currentPlayer],
      dcount = G.deckCount[currentPlayer],
      disc = G.discardCount[currentPlayer];

  printf("\nBefore calling gainCard:\n");
  printf("Handcount: %d\n", G.handCount[currentPlayer]);
  printf("Deckcount: %d\n", G.deckCount[currentPlayer]);
  printf("Discard count: %d\n", G.deckCount[currentPlayer]);

  printf("\nNow calling gainCard (gold) once each for hand/deck/discard ");
  printf("with no gold \nin supply pile...\n");

  printf("\nVerifying no cards have been added to hand...\n");
  gainCard(gold, &G, 2, currentPlayer);
  testGain(G.handCount[currentPlayer], hcount, 0);

  printf("\nVerifying no cards have been added to deck...\n");
  gainCard(gold, &G, 1, currentPlayer);
  testGain(G.deckCount[currentPlayer], dcount, 0);

  printf("\nVerifying no cards have been discarded...\n");
  gainCard(gold, &G, 0, currentPlayer);
  testGain(G.discardCount[currentPlayer], disc, 0);

  printf("\nIncreasing gold supply to 3 and calling once each ");
  printf("for hand/deck/discard...\n");
  G.supplyCount[gold] = 3;

  printf("\nVerifying 1 card has been added to hand...\n");
  gainCard(gold, &G, 2, currentPlayer);
  testGain(G.handCount[currentPlayer], hcount, 1);

  printf("\nVerifying 1 card has been added to deck...\n");
  gainCard(gold, &G, 1, currentPlayer);
  testGain(G.deckCount[currentPlayer], dcount, 1);

  printf("\nVerifying 1 card has been discarded...\n");
  gainCard(gold, &G, 0, currentPlayer);
  testGain(G.discardCount[currentPlayer], disc, 1);

  return 0;

}