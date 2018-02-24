#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// fail counters
int failc_effect = 0;
int failc_draw = 0;
int failc_discard = 0;
int failc_deckhandcount = 0;

// function to test smithy card
void test_smithy(int x, struct gameState *post) {
	int fx, d1, d2, d3, discard;
	int bonus = 0;

	// manually act on function's actions
	struct gameState pre;

	// copy game state to pre
	memcpy(&pre, post, sizeof(struct gameState));
	
	// call card effect function with smithy card
	fx = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);

	// call draw 3x
	d1 = drawCard(x, &pre);
	d2 = drawCard(x, &pre);
	d3 = drawCard(x, &pre);

	// call discard
	discard = discardCard(0, x, &pre, 0);

	// get hand/deck counts
	int post_hand = post->handCount[x];
	int post_deck = post->deckCount[x];
	int pre_hand = pre.handCount[x];
	int pre_deck = pre.deckCount[x];

	// check draws
	if (d1 == -1 && pre.deckCount[x] != 0) {
		failc_draw++;
	}
	if (d2 == -1 && pre.deckCount[x] != 0) {
		failc_draw++;
	}
	if (d3 == -1 && pre.deckCount[x] != 0) {
		failc_draw++;
	}

	// check card effect and discard 
	if (!(fx == 0 && discard == 0)) {
		if (fx) {
			failc_effect++;
		}
		if (discard) {
			failc_discard++;
		}
	}

	// check hand/deck counts
	if (!(post_hand == pre_hand && post_deck == pre_deck)) {
		failc_deckhandcount++;
	}
}

int main() {
	printf("Random Test\n");
	printf("randomcardtest2.c\n");
	printf("smithyCard()\n\n");

	int loop = 10000;
	int i, j, player;
	struct gameState test;
	srand(time(NULL));

	// randomly initialize game state
	for (i = 0; i < loop; i++) {
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&test)[j] = floor(Random() * 256);
		}

		// randomly select vals
		player = floor(Random() * MAX_PLAYERS);
		test.deckCount[player] = floor(Random() * MAX_DECK);
		test.discardCount[player] = floor(Random() * MAX_DECK);
		test.handCount[player] = floor(Random() * MAX_HAND);
		test.playedCardCount = floor(Random() * (MAX_DECK - 1));
		test.whoseTurn = player;

		// call test function
		test_smithy(player, &test);
	}

	int failc_total = failc_effect + failc_draw + failc_discard + failc_deckhandcount;

	printf("\nTest Results:\n");
	printf("Passed Tests: %d\n", loop - failc_total);
	printf("Failed Tests: %d\n", failc_total);

	if (failc_total == 0) {
		printf("Random Test Successfully Passed\n\n");
	}
	else {
		printf("\nRandom Test Failed\n");
		printf("cardEffect() failed: %d\n", failc_effect);
		printf("drawCard() failed: %d\n", failc_draw);
		printf("discardCard() failed %d\n", failc_discard);
		printf("Hand/Deck count mismatch: %d\n\n", failc_deckhandcount);
	}
	
	printf("Coverage\n");

	return 0;
}
