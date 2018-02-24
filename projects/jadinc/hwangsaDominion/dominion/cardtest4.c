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
	int i;
	int num_players = 2;
	int player_0 = 0;
	int player_1 = 1;
	int hand_pos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state, og_state;

	printf("Testing: council_roomCard()\n");
	memset(&state,23,sizeof(struct gameState));
	memset(&og_state,23,sizeof(struct gameState));

	initializeGame(num_players, k, seed, &state);
	// copy to preserve
	memcpy(&og_state, &state, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &state, hand_pos, &bonus);

	printf("\nPlayer_0 gains 4 cards\n");
	assertTrue(state.handCount[player_0],og_state.handCount[player_0]+3);

	printf("\nPlayer_0 gains 4 cards from his own pile\n");
	assertTrue(state.deckCount[player_0],og_state.deckCount[player_0]-4);

	printf("\nPlayer_0 number of buys increments\n");
	assertTrue(state.numBuys,og_state.numBuys+1);

	printf("\nNo change to victory card piles\n");
	printf("Province pile\n");
	assertTrue(state.supplyCount[province],og_state.supplyCount[province]);
	printf("Duchy pile\n");
	assertTrue(state.supplyCount[duchy],og_state.supplyCount[duchy]);
	printf("Estate pile\n");
	assertTrue(state.supplyCount[estate],og_state.supplyCount[estate]);

	printf("\nNo change to kingdom card piles\n");
	for (i = 0; i < 10; i++) {
		printf("Checking card piles...\n");
		assertTrue(state.supplyCount[k[i]],og_state.supplyCount[k[i]]);
	}

	printf("\nPlayer_1 gains 1 card\n");
	assertTrue(state.handCount[player_1],og_state.handCount[player_1]+1);
	printf("\nPlayer_1 gains 1 card from his own deck\n");
	assertTrue(state.deckCount[player_1],og_state.deckCount[player_1]-1);

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
	int i;
	int num_players = 2;
	int player_0 = 0;
	int player_1 = 1;
	int hand_pos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state, og_state;

	printf("Testing: council_roomCard()\n");
	memset(&state,23,sizeof(struct gameState));
	memset(&og_state,23,sizeof(struct gameState));

	initializeGame(num_players, k, seed, &state);
	// copy to preserve
	memcpy(&og_state, &state, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &state, hand_pos, &bonus);

	printf("\nPlayer_0 gains 4 cards\n");
	assertTrue(state.handCount[player_0],og_state.handCount[player_0]+3);

	printf("\nPlayer_0 gains 4 cards from his own pile\n");
	assertTrue(state.deckCount[player_0],og_state.deckCount[player_0]-4);

	printf("\nPlayer_0 number of buys increments\n");
	assertTrue(state.numBuys,og_state.numBuys+1);

	printf("\nNo change to victory card piles\n");
	printf("Province pile\n");
	assertTrue(state.supplyCount[province],og_state.supplyCount[province]);
	printf("Duchy pile\n");
	assertTrue(state.supplyCount[duchy],og_state.supplyCount[duchy]);
	printf("Estate pile\n");
	assertTrue(state.supplyCount[estate],og_state.supplyCount[estate]);

	printf("\nNo change to kingdom card piles\n");
	for (i = 0; i < 10; i++) {
		printf("Checking card piles...\n");
		assertTrue(state.supplyCount[k[i]],og_state.supplyCount[k[i]]);
	}

	printf("\nPlayer_1 gains 1 card\n");
	assertTrue(state.handCount[player_1],og_state.handCount[player_1]+1);
	printf("\nPlayer_1 gains 1 card from his own deck\n");
	assertTrue(state.deckCount[player_1],og_state.deckCount[player_1]-1);

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
