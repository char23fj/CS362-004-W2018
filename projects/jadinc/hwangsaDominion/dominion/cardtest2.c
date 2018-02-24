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
	int treasure_count = 0;
	int og_treasure_count = 0;
	int num_players = 2;
	int player_0 = 0;
	int player_1 = 1;
	int card;
	int hand_pos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;

	// game states
	struct gameState state, og_state;

	printf("Testing: adventurerCard()\n");
	memset(&state,23,sizeof(struct gameState));
	memset(&og_state,23,sizeof(struct gameState));
	
	initializeGame(num_players, k, seed, &state);
	// copy to preserve
	memcpy(&og_state, &state, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &state, hand_pos, &bonus);

	printf("\nPlayer_0 gains 2 cards\n");
	assertTrue(state.handCount[player_0],og_state.handCount[player_0]+2);

	// check treasure gain
	for (i = 0; i < state.handCount[player_0]; i++) {
		card = state.hand[player_0][i];
		if (card == copper || card == silver || card == gold) {
			treasure_count++;
		}
	}

	// check default treasure count
	for (i = 0; i < og_state.handCount[player_0]; i++) {
		card = og_state.hand[player_0][i];
		if(card == copper || card == silver || card == gold) {
			og_treasure_count++;
		}
	}

	printf("\nPlayer_0 gains 2 treasure cards\n");
	assertTrue(og_treasure_count+2,treasure_count);

	printf("\nNo change to victory card piles\n");
	printf("Province pile\n");
	assertTrue(state.supplyCount[province],og_state.supplyCount[province]);
	printf("Duchy pile\n");
	assertTrue(state.supplyCount[duchy],og_state.supplyCount[duchy]);
	printf("Estate pile\n");
	assertTrue(state.supplyCount[estate],og_state.supplyCount[estate]);

	printf("\nNo changes to kingdom card piles\n");
	for (i = 0; i < 10; i++) {
		printf("Checking card piles...\n");
		assertTrue(state.supplyCount[k[i]], og_state.supplyCount[k[i]]);
	}

	printf("\nPlayer_1 was not affected\n");
	printf("Hand count\n");
	assertTrue(state.handCount[player_1],og_state.handCount[player_1]);
	printf("Deck count\n");
	assertTrue(state.deckCount[player_1],og_state.handCount[player_1]);

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
	int treasure_count = 0;
	int og_treasure_count = 0;
	int num_players = 2;
	int player_0 = 0;
	int player_1 = 1;
	int card;
	int hand_pos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;

	// game states
	struct gameState state, og_state;

	printf("Testing: adventurerCard()\n");
	memset(&state,23,sizeof(struct gameState));
	memset(&og_state,23,sizeof(struct gameState));
	
	initializeGame(num_players, k, seed, &state);
	// copy to preserve
	memcpy(&og_state, &state, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &state, hand_pos, &bonus);

	printf("\nPlayer_0 gains 2 cards\n");
	assertTrue(state.handCount[player_0],og_state.handCount[player_0]+2);

	// check treasure gain
	for (i = 0; i < state.handCount[player_0]; i++) {
		card = state.hand[player_0][i];
		if (card == copper || card == silver || card == gold) {
			treasure_count++;
		}
	}

	// check default treasure count
	for (i = 0; i < og_state.handCount[player_0]; i++) {
		card = og_state.hand[player_0][i];
		if(card == copper || card == silver || card == gold) {
			og_treasure_count++;
		}
	}

	printf("\nPlayer_0 gains 2 treasure cards\n");
	assertTrue(og_treasure_count+2,treasure_count);

	printf("\nNo change to victory card piles\n");
	printf("Province pile\n");
	assertTrue(state.supplyCount[province],og_state.supplyCount[province]);
	printf("Duchy pile\n");
	assertTrue(state.supplyCount[duchy],og_state.supplyCount[duchy]);
	printf("Estate pile\n");
	assertTrue(state.supplyCount[estate],og_state.supplyCount[estate]);

	printf("\nNo changes to kingdom card piles\n");
	for (i = 0; i < 10; i++) {
		printf("Checking card piles...\n");
		assertTrue(state.supplyCount[k[i]], og_state.supplyCount[k[i]]);
	}

	printf("\nPlayer_1 was not affected\n");
	printf("Hand count\n");
	assertTrue(state.handCount[player_1],og_state.handCount[player_1]);
	printf("Deck count\n");
	assertTrue(state.deckCount[player_1],og_state.handCount[player_1]);

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
