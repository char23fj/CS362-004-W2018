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
		printf("Test: Faile\n");
		failure_count++;
	}
}

int main() {
	int num_players = 2;
	
	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: isGameOver()\n");

	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	state.supplyCount[province] = 0;

	printf("\nProvince cards empty\n");
	assertTrue(isGameOver(&state),1);

	state.supplyCount[province] = 1;

	state.supplyCount[0] = 0;
	state.supplyCount[1] = 0;
	state.supplyCount[2] = 0;

	printf("\n3 supply piles empty\n");
	assertTrue(isGameOver(&state),1);

	state.supplyCount[0] = 1;
	state.supplyCount[1] = 1;
	state.supplyCount[2] = 1;

	printf("\nProvince cards not empty\n");
	printf("\n3 supply piles not empty\n");
	assertTrue(isGameOver(&state),0);

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
		printf("Test: Faile\n");
		failure_count++;
	}
}

int main() {
	int num_players = 2;
	
	// kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 2000;
	struct gameState state;

	printf("Testing: isGameOver()\n");

	memset(&state,23,sizeof(struct gameState));
	initializeGame(num_players, k, seed, &state);

	state.supplyCount[province] = 0;

	printf("\nProvince cards empty\n");
	assertTrue(isGameOver(&state),1);

	state.supplyCount[province] = 1;

	state.supplyCount[0] = 0;
	state.supplyCount[1] = 0;
	state.supplyCount[2] = 0;

	printf("\n3 supply piles empty\n");
	assertTrue(isGameOver(&state),1);

	state.supplyCount[0] = 1;
	state.supplyCount[1] = 1;
	state.supplyCount[2] = 1;

	printf("\nProvince cards not empty\n");
	printf("\n3 supply piles not empty\n");
	assertTrue(isGameOver(&state),0);

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
