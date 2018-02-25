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

  int i = 0,
      c1 = 0,
      c2 = 0,
      c3 = 0,
      bonus = 0,
      goldCount = 0;

  //Precondition: gold and treasure_map in supply pile
  G.supplyCount[gold] = 5;
  G.supplyCount[treasure_map] = 5;
  int currentPlayer = G.whoseTurn;

  printf("\n-----Testing the treasure map card implementation.-----\n");

  printf("\nDiscarding any treasure map cards in hand (start with none).\n");
  for (i = 0; i < G.handCount[currentPlayer]; i++)
  {
      if (G.hand[currentPlayer][i] == treasure_map)
      {
          printf("Found and discarded a treasure map.\n");
          discardCard(i, currentPlayer, &G, 1);
      }
  }

  gainCard(treasure_map, &G, 2, currentPlayer);
  int hcount = G.handCount[currentPlayer];

  printf("\nAdded one treasure map. \nHandcount: %d\n", hcount);
  printf("Deckcount: %d\n", G.deckCount[currentPlayer]);
  int dcount = G.deckCount[currentPlayer];

  cardEffect(treasure_map, c1, c2, c3, &G, hcount-1, &bonus);
  printf("\nAfter playing treasure map (only 1 in hand):\n");
  printf("Handcount: %d  ", G.handCount[currentPlayer]);
  printf("(Expected: %d)\n", hcount);

  printf("Deckcount: %d  ", G.deckCount[currentPlayer]);
  printf("(Expected: %d)\n", dcount);

  printf("\nVerifying no treasure map cards have been played/discarded...\n");
  //Should equal stored hcount
  if (G.handCount[currentPlayer] == hcount)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Hand count has changed.\n");
  }

  printf("\nVerifying no gold added to deck...\n");
  if (G.deckCount[currentPlayer] == dcount)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Deck count has changed.\n");
  }

  gainCard(treasure_map, &G, 2, currentPlayer);
  hcount = G.handCount[currentPlayer];
  printf("\nAdded another treasure map.");
  cardEffect(treasure_map, c1, c2, c3, &G, hcount-1, &bonus);
  printf("\nAfter playing treasure map (with 2nd in hand):\n");
  printf("Handcount: %d  ", G.handCount[currentPlayer]);
  printf("(Expected: %d)\n", hcount - 2);

  printf("Deckcount: %d  ", G.deckCount[currentPlayer]);
  printf("(Expected: %d)\n", dcount + 4);

  printf("\nVerifying two treasure map cards have been discarded...\n");
  //Should equal stored hcount minus two discarded
  if (G.handCount[currentPlayer] == hcount - 2)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Did not discard 2 cards.\n");
  }

  dcount = G.deckCount[currentPlayer] - 4;

  printf("\nVerifying four gold cards added at the end of the deck...\n");
  for (i = dcount; i < G.deckCount[currentPlayer]; i++)
  {
      if (G.deck[currentPlayer][i] == gold)
      {
          goldCount++;
      }
  }

  if (goldCount == 4)
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Did not gain 4 gold.\n");
  }

  return 0;

}