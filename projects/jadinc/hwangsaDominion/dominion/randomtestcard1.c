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
#define SAMPLE_SIZE 5000

int testCardEffect(struct gameState* G);

int main(int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  printf("\n-----Testing the treasure map card implementation.-----\n");


  //initializeGame(2, k, 235, &G);

  int currentPlayer = G.whoseTurn;

  int i, j, md, 
      mh, hc,
      fails = 0;
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

  int i = 0,
      error = 0,
      tmcount = 1,
      goldCount = 0;

  int currentPlayer = G->whoseTurn;

  gainCard(treasure_map, G, 2, currentPlayer);
  int hcount = G->handCount[currentPlayer];
  int dcount = G->deckCount[currentPlayer];

  for (i = 0; i < G->handCount[currentPlayer]; i++)
  {
      if (G->hand[currentPlayer][i] == treasure_map)
      {
          tmcount++;
      }
  }

  cardEffect(treasure_map, 0, 0, 0, G, hcount-1, 0);

  for (i = dcount; i < G->deckCount[currentPlayer]; i++)
  {
      if (G->deck[currentPlayer][i] == gold)
      {
          goldCount++;
      }
  }

  if (tmcount > 1 && goldCount < 4)
  {
      printf("Error:  Had multiple treasure maps and did not gain 4 gold.\n");
      error = 1;
  }

  if (tmcount < 2 && goldCount >= 4)
  {
      printf("Possible error:  Found 4 gold in a row without having had two ");
      printf("treasure maps in hand (coincidence possible but improbable).\n");
      error = 1;
  }

  //Should equal stored hcount minus two discarded
  if (tmcount > 1 && G->handCount[currentPlayer] != hcount - 2)
  {
      printf("Error:  Had two treasure maps and did not discard them.\n");
  }

  return error;

}