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
int failc_p1_deckhandcount = 0;
int failc_buys = 0;
int failc_p2_deckhandcount = 0;

// function tests council room card
void test_councilroom(int x, struct gameState *post) {
	int i, fx, d1, d2, d3, d4, draw, discard;
	int bonus = 0;

	// manually act on function's actions
	struct gameState pre;

	// copy game state to pre
	memcpy(&pre, post, sizeof(struct gameState));

	// call card effect function with council room card
	fx = cardEffect(council_room, 0, 0, 0, post, 0, &bonus);

	// call drawCard 4x
	d1 = drawCard(x, &pre);
	d2 = drawCard(x, &pre);
	d3 = drawCard(x, &pre);
	d4 = drawCard(x, &pre);

	pre.numBuys++;

	// each player draws a card
	for (i = 0; i < pre.numPlayers; i++) {
		if (i != x) {
			draw = drawCard(i, &pre);

			// check if draw failed
			if (draw == -1 && pre.deckCount[i] != 0) {
				failc_draw++;
			}
		}
	}

	// call discardCard
	discard = discardCard(0, x, &pre, 0);

	// get hand and deck counts
	int post_hand = post->handCount[x];
	int post_deck = post->deckCount[x];
	int pre_hand = pre.handCount[x];
	int pre_deck = pre.deckCount[x];

	// check buys
	if (pre.numBuys != post->numBuys) {
		failc_buys++;
	}

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
	if (d4 == -1 && pre.deckCount[x] != 0) {
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

	// check hand and deck count for player 1
	if (!(post_hand == pre_hand && post_deck == pre_deck)) {
		failc_p1_deckhandcount++;
	}

	// check hand and deck count for player 2
	for (i = 0; i < pre.numPlayers; i++) {
		if (i != x) {
			if (!(post->handCount[i] == pre.handCount[i] && post->deckCount[i] == pre.deckCount[i])) {
				failc_p2_deckhandcount++;
			}
		}
	}
}

int main() {
	printf("Random Test\n");
	printf("randomcardtest1.c\n");
	printf("council_roomCard()\n");

	int loop = 10000;
	int i, j, player, deck_count, hand_count, discard_count;
	int num_players[] = {2, 3, 4};
	struct gameState test;
	srand(time(NULL));

	// randomly initialize game state
	for (j = 0; j < loop; j++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&test)[i] = floor(Random() * 256);
		}

		// randomly select vals
		test.numPlayers = num_players[rand() % 3];
		test.numBuys = 1;
		test.playedCardCount = floor(Random() * (MAX_DECK - 1));
		player = test.numPlayers - 2;
		deck_count = floor(Random() * MAX_DECK);
		hand_count = floor(Random() * MAX_HAND);
		discard_count = floor(Random() * MAX_DECK);
		test.whoseTurn = player;

		// set hand/deck vals
		for (i = 0; i < test.numPlayers; i++) {
			test.deckCount[i] = deck_count;
			test.handCount[i] = hand_count;
			test.discardCount[i] = discard_count;
		}

		// call test function
		test_councilroom(player, &test);
	}

	int failc_total = failc_effect + failc_draw + failc_discard + failc_p1_deckhandcount + failc_buys;

	printf("\nTest Results\n");
	printf("Passed Tests: %d\n", loop - failc_total);
	printf("Failed Tests: %d\n", failc_total);

	if (failc_total == 0) {
		printf("\nRandom Test Successfully Passed\n\n");
	}
	else {
		printf("\nRandom Test Failed\n");
		printf("cardEffect() failed: %d\n", failc_effect);
		printf("drawCard() failed: %d\n", failc_draw);
		printf("discardCard() failed: %d\n", failc_discard);
		printf("Player Hand/Deck count mismatch: %d\n", failc_p1_deckhandcount);
		printf("Other Player Hand/Deck count  mismatch: %d\n", failc_p2_deckhandcount);
		printf("numBuys count mismatch: %d\n", failc_buys);
	}

	printf("Coverage\n");

	return 0;
}
