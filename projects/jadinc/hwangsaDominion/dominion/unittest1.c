#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testResult(int given, int desired)
{
    if (given == 1 && desired == 1)
    {
        printf("Pass.  Game over.\n");
    }
    else if (desired == 1)
    {
        printf("Fail.  Returned false result in a game-ending case.\n");
    }

    if (given == 0 && desired == 0)
    {
        printf("Pass.  Game continues.\n");
    }
    else if (desired == 0)
    {
        printf("Fail.  Returned true without game-ending condition.\n");
    }
}

int main(int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

  initializeGame(2, k, 235, &G);

  printf("\n-----Testing the isGameOver function implementation.-----\n");

  //Precondition: province supply pile empty
  G.supplyCount[province] = 0;

  int result = isGameOver(&G);
  printf("\nCase 1:  Province supply is empty.  Result:\n");
  testResult(result, 1);

  //Precondition: province supply pile not empty, 3 others empty
  G.supplyCount[province] = 1;
  G.supplyCount[smithy] = 0;
  G.supplyCount[estate] = 0;
  G.supplyCount[gold] = 0;

  result = isGameOver(&G);
  printf("\nCase 2:  3 supply piles empty, province at 1.  Result:\n");
  testResult(result, 1);

  //Precondition: province supply pile empty
  G.supplyCount[province] = 1;
  G.supplyCount[smithy] = 1;
  G.supplyCount[estate] = 1;
  G.supplyCount[gold] = 1;

  result = isGameOver(&G);
  printf("\nCase 1:  No empty supply piles.  Result:\n");
  testResult(result, 0);

  return 0;

}