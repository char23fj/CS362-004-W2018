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
  struct gameState G;
  int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy };

  printf("\n-----Testing the steward card implementation.-----\n");

  //initializeGame(2, k, 235, &G);

  int currentPlayer = G.whoseTurn;

  int i, j, md, 
      mh, hc,
      fails = 0;
  for (i = 0; i < SAMPLE_SIZE; i++)
  {
      md = rand() % MAX_DECK + 10;

      initializeGame(2, k, 235, &G);

      G.deckCount[currentPlayer] = 0;
      G.handCount[currentPlayer] = 0;

      for (j = 0; j < md; j++)
      {
          gainCard(rand() % 27, &G, 1, currentPlayer);
      }

      mh = rand() % MAX_HAND + 2;
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
  int currentPlayer = G->whoseTurn,
      error = 0,
      choice = rand() % 5 + 1,
      card1,
      card2;

  card1 = rand() % G->handCount[currentPlayer];
  card2 = card1;
  while (card2 == card1 && G->handCount[currentPlayer] > 1)
  {
      card2 = rand() % G->handCount[currentPlayer];
  }

  card1 = G->hand[currentPlayer][card1];
  card2 = G->hand[currentPlayer][card2];

  gainCard(steward, G, 2, currentPlayer);
  int hcount = G->handCount[currentPlayer],
      dcount = G->deckCount[currentPlayer],
      disc = G->discardCount[currentPlayer],
      coins = G->coins;

  cardEffect(steward, choice, card1, card2, G, hcount - 1, 0);

  if (choice == 1 && G->deckCount[currentPlayer] != dcount + 2)
  {
      printf("Error:  2 cards not drawn with choice variable set to 1.\n");
      error = 1;
  }

  if (choice == 2 && G->coins != coins + 2)
  {
      printf("Error:  2 coins not added with choice variable set to 2.\n");
      error = 1;
  }

  if (choice != 1 && choice != 2)
  {
      if (G->discardCount[currentPlayer] < disc + 2)
      {
          printf("Error:  2 cards not discarded with choice variable > 2.\n");
          error = 1;
      }

      disc = G->discardCount[currentPlayer];
      if (G->discard[currentPlayer][disc-1] != card1 ||
          G->discard[currentPlayer][disc-2] != card2)
      {
          printf("Error:  Discarded cards do not match passed arguments.\n");
          error = 1;
      }
  }


  return error;

}