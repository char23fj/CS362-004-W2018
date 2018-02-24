<<<<<<< HEAD
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int failure_count = 0;

void assertTrue(int a, int b) {
	if (a == b) {
		printf("Test: Pass\n");
	}
	else {
		printf("Test: Fail\n");
		failure_count++;
	}
}

int main() {
	int num_players = 2;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: gainCard()\n");
	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	printf("\nGold supply pile is empty\n");
	state.supplyCount[gold] = 0;
	assertTrue(gainCard(gold,&state,0,0),-1);
	state.supplyCount[gold] = 30;

	printf("\nAdd card to deck\n");
	int deckCount = state.deckCount[0];
	gainCard(gold,&state,1,0);
	assertTrue(deckCount+1, state.deckCount[0]);

	printf("\nAdd card to hand\n");
	int handCount = state.handCount[0];
	gainCard(gold,&state,2,0);
	assertTrue(handCount+1, state.handCount[0]);

	printf("\nAdd card to discarded pile\n");
	int discardCount = state.discardCount[0];
	gainCard(gold,&state,0,0);
	assertTrue(discardCount+1, state.discardCount[0]);

	printf("\nDecrease gold supply\n");
	int goldSupply = state.supplyCount[gold];
	gainCard(gold,&state,0,0);
	assertTrue(goldSupply-1,state.supplyCount[gold]);

	if(failure_count) {
		printf("\nTest: Fail\n");
		printf("Failures: %d\n", failure_count);
	}
	else {
		printf("\nTest: Passed and Completed\n\n");
	}

	return 0;
}
=======
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int failure_count = 0;

void assertTrue(int a, int b) {
	if (a == b) {
		printf("Test: Pass\n");
	}
	else {
		printf("Test: Fail\n");
		failure_count++;
	}
}

int main() {
	int num_players = 2;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: gainCard()\n");
	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	printf("\nGold supply pile is empty\n");
	state.supplyCount[gold] = 0;
	assertTrue(gainCard(gold,&state,0,0),-1);
	state.supplyCount[gold] = 30;

	printf("\nAdd card to deck\n");
	int deckCount = state.deckCount[0];
	gainCard(gold,&state,1,0);
	assertTrue(deckCount+1, state.deckCount[0]);

	printf("\nAdd card to hand\n");
	int handCount = state.handCount[0];
	gainCard(gold,&state,2,0);
	assertTrue(handCount+1, state.handCount[0]);

	printf("\nAdd card to discarded pile\n");
	int discardCount = state.discardCount[0];
	gainCard(gold,&state,0,0);
	assertTrue(discardCount+1, state.discardCount[0]);

	printf("\nDecrease gold supply\n");
	int goldSupply = state.supplyCount[gold];
	gainCard(gold,&state,0,0);
	assertTrue(goldSupply-1,state.supplyCount[gold]);

	if(failure_count) {
		printf("\nTest: Fail\n");
		printf("Failures: %d\n", failure_count);
	}
	else {
		printf("\nTest: Passed and Completed\n\n");
	}

	return 0;
}
>>>>>>> 969d8ce8573046a341b0c60fe0fd421a65085b95
