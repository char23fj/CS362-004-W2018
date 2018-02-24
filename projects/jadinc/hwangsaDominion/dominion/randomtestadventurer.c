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
int failc_shuffle = 0;
int failc_draw = 0;
int failc_deckhandcount = 0;
int failc_treasure = 0;

// this function will test the adventurer card
void testAdventurer(int x, struct gameState *post) {
	int pre_treasure = 0;
	int post_treasure = 0;
	int temp_hand[MAX_HAND];
	int draw_treasure = 0;

	// manually act on function's actions
	struct gameState pre;
	int card, draw_card;
	int bonus = 0;
	int count = 0;
	int i, fx, shuffle_c, draw;

	// copy to pre
	memcpy(&pre, post, sizeof(struct gameState));

	// call effect function with adventurer card
	fx = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);

	// check if effect function failed
	if (fx) {
		failc_effect++;
	}

	// adventurer card actions
	while (draw_treasure < 2) {
		if (pre.deckCount[x] < 1) {
			// if the deck is empty, shuffle discarded cards and add to deck
			shuffle_c = shuffle(x, &pre);
			
			// check if shuffle failed
			if (shuffle_c == -1 && pre.deckCount[x] >= 1) {
				failc_shuffle++;
			}
		}

		draw = drawCard(x, &pre);

		// check if draw failed
		if (draw == -1 && pre.deckCount[x] != 0) {
			failc_draw++;
		}

		// top card in player's hand is most recently drawn card
		draw_card = pre.hand[x][pre.handCount[x] - 1];

		if (draw_card == copper || draw_card == silver || draw_card == gold) {
			draw_treasure++;
		}
		else {
			temp_hand[count] = draw_card;
			pre.handCount[x]--;	// remove top card
			count++;
		}
	}

	while (count - 1 >= 0) {
		pre.discard[x][pre.discardCount[x]++] = temp_hand[count - 1];	// discard cards in play that were drawn
		count = count - 1;
	}

	// get num of post_treasure
	for (i = 0; i < post->handCount[x]; i++) {
		card = post->hand[x][i];
		if (card == copper || card == silver || card == gold) {
			post_treasure++;
		}
	}
	// get num of pre_treasure
	for (i = 0; i < pre.handCount[x]; i++) {
		card = pre.hand[x][i];
		if (card == copper || card == silver || card == gold) {
			pre_treasure++;
		}
	}

	// check for match
	if (post_treasure != pre_treasure) {
		failc_treasure++;
	}

	// get deck and hand counts
	int post_hand = post->handCount[x];
	int post_deck = post->deckCount[x];
	int post_discard = post->discardCount[x];
	int pre_hand = pre.handCount[x];
	int pre_deck = pre.deckCount[x];
	int pre_discard = pre.discardCount[x];

	// check for match
	if (!(post_hand == pre_hand && post_deck == pre_deck && post_discard == pre_discard)) {
		failc_deckhandcount++;
	}
}

int main() {
	printf("Random Test\n");
	printf("randomtestadventurer.c\n");
	printf("adventurerCard()\n\n");

	int loop = 10000;
	int treasures[] = {copper, silver, gold};
	int treasure_count;
	int i, j, player;
	struct gameState test;

	// min 3 cards in deck and hand
	int min = 3;
	srand(time(NULL));

	// randomly initialize game state
	for (j = 0; j < loop; j++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&test)[i] = floor(Random() * 256);
		}
		// randomly select vals
		player = floor(Random() * MAX_PLAYERS);
		test.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
		treasure_count = floor(Random() * ((test.deckCount[player] - min) + 1) + min);

		// min 3 treasure careds in deck
		for (i = 0; i < treasure_count; i++) {
			test.deck[player][i] = treasures[rand() % 3];
		}
		test.discardCount[player] = 0;
		test.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
		test.whoseTurn = player;

		// call test function
		testAdventurer(player, &test);
	}

	int failc_total = failc_effect + failc_shuffle + failc_draw + failc_deckhandcount + failc_treasure;

	if (loop - failc_total <= 0) {
		printf("\nTest Results:\n");
		printf("Passed Tests: %d\n",0);
		printf("Failed Tests: %d\n",loop);
	}
	else {
		printf("\nTest Results:\n");
		printf("Passed Tests: %d\n",loop - failc_total);
		printf("Failed Tests: %d\n", failc_total);
	}

	if (failc_total == 0) {
		printf("\nRandom Test Successfully Passed\n");
	}
	else {
		printf("\nRandom Test Failed\n");
		printf("cardEffect() failed: %d\n", failc_effect);
		printf("drawCard() failed: %d\n", failc_draw);
		printf("shuffle() failed: %d\n", failc_shuffle);
		printf("Hand/Deck count mismatch: %d\n", failc_deckhandcount);
		printf("Treasure count mismatch: %d\n", failc_treasure);
	}
	printf("Coverage\n");

	return 0;
}
