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

  printf("\n-----Testing the shuffle function implementation.-----\n");

  printf("\nAttempting to shuffle an empty deck ");
  
  G.deckCount[1] = 0;

  printf("(deckCount: %d).\n", G.deckCount[1]);
  printf("Verifying return value of -1...\n");
  if (shuffle(1, &G) == -1)
  {
      printf("Passed.\n");
  }
  else
  {
      printf("Failed.  Unexpected return value.\n");
  }

  printf("\nShuffling the other player's deck ");
  printf("(deckCount: %d).\n", G.deckCount[0]);

  int dcount = G.deckCount[0],
      hi = dcount - 1,
      mid = hi / 2;

  int sample1 = G.deck[0][0],
      sample2 = G.deck[0][mid],
      sample3 = G.deck[0][hi];

  shuffle(0, &G);

  int same = 1,
      count = 0;

  //Give several attempts to shuffle and change 3 sample values
  while (same == 1 && count < 10)
  {
      if (sample1 == G.deck[0][0] && sample2 == G.deck[0][mid] && sample3 == G.deck[0][hi])
      {
          shuffle(0, &G);
          count++;
      }
      else
      {
          same = 0;
          break;
      }
  }

  printf("Verifying deck count has not changed...\n");
  if (dcount == G.deckCount[0])
  {
      printf("Passed.\n");
  }

  else
  {
      printf("Failed.  Deck size has changed.\n");
  }

  printf("Verifying values at 3 fixed indices are not unchanged...\n");

  if (same == 0)
  {
      printf("Passed.\n");
  }
  else
  {
      printf("Failed.  Values unchanged after 10 attempts.\n");
  }

  return 0;

}