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
	int player = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: shuffle()\n");

	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	state.deckCount[player] = 0;
	printf("\nDeck count = 0\n");
	assertTrue(shuffle(player,&state),-1);

	printf("\nDeck count = 10 before and after shuffling\n");
	state.deckCount[player] = 10;
	shuffle(player, &state);
	assertTrue(state.deckCount[player],10);

	printf("\nCards are shuffled\n");

	int pre_shuffle = state.deck[player][0];
	shuffle(player,&state);
	int post_shuffle = state.deck[player][0];

	if(pre_shuffle != post_shuffle) {
		assertTrue(1,1);
	}
	else {
		assertTrue(0,1);
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
	int player = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: shuffle()\n");

	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	state.deckCount[player] = 0;
	printf("\nDeck count = 0\n");
	assertTrue(shuffle(player,&state),-1);

	printf("\nDeck count = 10 before and after shuffling\n");
	state.deckCount[player] = 10;
	shuffle(player, &state);
	assertTrue(state.deckCount[player],10);

	printf("\nCards are shuffled\n");

	int pre_shuffle = state.deck[player][0];
	shuffle(player,&state);
	int post_shuffle = state.deck[player][0];

	if(pre_shuffle != post_shuffle) {
		assertTrue(1,1);
	}
	else {
		assertTrue(0,1);
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
