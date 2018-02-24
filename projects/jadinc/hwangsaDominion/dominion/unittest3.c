<<<<<<< HEAD
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

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
	int i;
	int num_players = 2;
	int player = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;
	int handCount;
	int bonus = 1;

	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	// arrays of treasures
	for (i = 0; i < MAX_HAND; i++) {
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf("Testing: updateCoins()");

	// test the function updateCoins() to see how it handles treasures, different bonus and hand count
	for(handCount = 0; handCount <= 5; handCount = handCount + 5) {
		printf("\n\nTreasure cards: %d\n", handCount);
		printf("Bonus: %d\n", bonus);

		memset(&state,23,sizeof(struct gameState));
		initializeGame(num_players, k, seed, &state);
		state.handCount[player] = handCount;

		// fill hand with copper
		memcpy(state.hand[player],coppers,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Copper\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*1+bonus);

		assertTrue(state.coins,handCount*1+bonus);

		// fill hand with silver
		memcpy(state.hand[player],silvers,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Silver\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*2+bonus);

		assertTrue(state.coins, handCount*2+bonus);

		// fill hand with gold
		memcpy(state.hand[player],golds,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Gold\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*3+bonus);

		assertTrue(state.coins,handCount*3+bonus);

		bonus = bonus + 2;
	}

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
#include <assert.h>
#include <stdio.h>

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
	int i;
	int num_players = 2;
	int player = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;
	int handCount;
	int bonus = 1;

	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	// arrays of treasures
	for (i = 0; i < MAX_HAND; i++) {
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf("Testing: updateCoins()");

	// test the function updateCoins() to see how it handles treasures, different bonus and hand count
	for(handCount = 0; handCount <= 5; handCount = handCount + 5) {
		printf("\n\nTreasure cards: %d\n", handCount);
		printf("Bonus: %d\n", bonus);

		memset(&state,23,sizeof(struct gameState));
		initializeGame(num_players, k, seed, &state);
		state.handCount[player] = handCount;

		// fill hand with copper
		memcpy(state.hand[player],coppers,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Copper\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*1+bonus);

		assertTrue(state.coins,handCount*1+bonus);

		// fill hand with silver
		memcpy(state.hand[player],silvers,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Silver\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*2+bonus);

		assertTrue(state.coins, handCount*2+bonus);

		// fill hand with gold
		memcpy(state.hand[player],golds,sizeof(int)*handCount);
		updateCoins(player,&state,bonus);

		printf("\nCoin count: Gold\n");
		printf("Actual: %d\n", state.coins);
		printf("Expected: %d\n", handCount*3+bonus);

		assertTrue(state.coins,handCount*3+bonus);

		bonus = bonus + 2;
	}

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
