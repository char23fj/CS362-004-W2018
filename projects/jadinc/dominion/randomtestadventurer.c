#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_FAILS 10
#define MAX_HAND 15
#define MAX_DECK 50
#define SAMPLE_SIZE 50

int testCardEffect(struct gameState* G);

int main(int argc, char** argv) {
  printf("\n-----Testing the adventurer card implementation.-----\n");

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  //initializeGame(2, k, 235, &G);

  int fails = 0;

  int currentPlayer = G.whoseTurn;

  int i, j, md, 
      mh, hc;
  for (i = 0; i < SAMPLE_SIZE; i++)
  {
      md = rand() % MAX_DECK;

      initializeGame(2, k, 235, &G);

      G.deckCount[currentPlayer] = 0;
      G.handCount[currentPlayer] = 0;

      for (j = 0; j < md; j++)
      {
          gainCard(rand() % 27, &G, 1, currentPlayer);
      }

      mh = rand() % MAX_HAND;
      for (j = 0; j < mh; j++)
      {
          if (G.deckCount[currentPlayer] > 0)
          {
              drawCard(currentPlayer, &G);
          }
      }

      hc = G.handCount[currentPlayer];

      fails += testCardEffect(&G);

      if (fails >= MAX_FAILS)
      {
          printf("\nMaximum failure count reached.  Exiting.\n");
          break;
      }
  }

  if (fails == 0)
  {
      printf("\nTesting completed; no errors found.\n");
  }

}

int testCardEffect(struct gameState* G)
{
  int currentPlayer = G->whoseTurn;
  gainCard(adventurer, G, 2, currentPlayer);
  int error = 0,
      hcount = G->handCount[currentPlayer],
      dcount = G->deckCount[currentPlayer],
      disc = G->discardCount[currentPlayer];
  

  cardEffect(adventurer, 0, 0, 0, G, hcount-1, 0);

  if (G->handCount[currentPlayer] != hcount + 1)
  {
      printf("Error: Hand count should reflect two additions, minus the discarded ");
      printf("adventurer card.\n");

      error = 1;
  }

  if (G->discardCount[currentPlayer] == disc)
  {
      printf("Error: Nothing was added to the discard pile.\n");
      error = 1;
  }

  if (G->deckCount[currentPlayer] > dcount - 2)
  {
      printf("Error: Deck should have been reduced by at least two.\n");
      error = 1;
  }

  if (dcount - G->deckCount[currentPlayer] != disc - G->discardCount[currentPlayer] + 1)
  {
      printf("Error:  Discard pile should have increased by 1 more than the deck.\n");
      error = 1;
  }
  int i,
      top;

  for (i = 1; i < 3; i++)
  {
    top = G->hand[currentPlayer][G->handCount[currentPlayer] - i];
    if (top < copper || top > gold)
    {
        printf("Error:  Top two (most recently drawn) cards are not coins.\n");
        error = 1;
    }
  }

  return error;
}