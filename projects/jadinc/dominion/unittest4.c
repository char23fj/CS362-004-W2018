#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testDiff(int after, int before, int extra)
{
    if (after == before - extra)
    {
        printf("Passed.\n");
    }

    else if (extra == 0)
    {
        printf("Failed.  No cards should have been removed.\n");
    }

    else
    {
        printf("Failed.  %d card(s) should have been removed.\n", extra);
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

  printf("\n-----Testing the discardCard function implementation.-----\n");

  int hcount = G.handCount[currentPlayer],
      disc = G.discardCount[currentPlayer],
      played = G.playedCardCount,
      last = G.hand[currentPlayer][hcount - 1];

  printf("\nBefore calling discardCard:\n");
  printf("Handcount: %d\n", hcount);
  printf("Discard count: %d\n", disc);
  printf("Played card count: %d\n", played);

  printf("\nCalling discardCard at index 0, with 0 for played cards flag.\n");

  printf("\nVerifying card removed from hand...\n");
  discardCard(0, currentPlayer, &G, 0);
  testDiff(G.handCount[currentPlayer], hcount, 1);

  printf("\nVerifying 1 card has been added to discard pile...\n");
  testDiff(G.discardCount[currentPlayer], disc, 1);

  printf("\nVerifying 1 card has been added to playedCards...\n");
  if (G.playedCardCount == played + 1)
  {
      printf("Passed.\n");
  }
  else
  {
      printf("Failed.  1 card should have been added to played pile.\n");
  }

  printf("\nVerifying last card has been moved to zero index...\n");
  if (G.hand[currentPlayer][0] == last)
  {
      printf("Passed.\n");
  }
  else
  {
      printf("Failed.  0 index card is not the last card from before discarding.\n");
  }
  played = G.playedCardCount;
  hcount = G.handCount[currentPlayer];
  discardCard(G.hand[currentPlayer][hcount-1], currentPlayer, &G, 1);

  printf("\nCalling discardCard at highest index, with 1 for played cards flag.\n");
  printf("\nVerifying card has not been added to playedCards...\n");
  if (G.playedCardCount == played)
  {
      printf("Passed.\n");
  }
  else
  {
      printf("Failed.  No cards should have been added to played pile.\n");
  }

  hcount = G.handCount[currentPlayer];
  printf("\nRemoving all cards from player's hand.\n");
  int removed = 0;
  while (G.handCount[currentPlayer] > 0)
  {
      discardCard(0, currentPlayer, &G, 1);
      removed++;
  }

  printf("Hand count: %d.\n", G.handCount[currentPlayer]);
  printf("Verifying number of cards removed equals number of cards before removal..\n");
  testDiff(0, removed, hcount);
  printf("Attempting to remove an additional card with empty hand...\n");
  discardCard(0, currentPlayer, &G, 1);
  printf("Hand count: %d.\n", G.handCount[currentPlayer]);
  if (G.handCount[currentPlayer] < 0)
  {
      printf("Action succeeded, indicating possible design flaw.\n");
  }
  else
  {
      printf("Action failed; program prevents negative hand count values.\n");
  }

  return 0;

}