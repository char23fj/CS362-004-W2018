/************************************************************************
Author: Peter Yetti 
Date:  1/28/18
Description: Implementation for cardtest3.c
*************************************************************************/

#include "../dominion.h"
#import "unittest.h"
#include "assert.h"

static const int run(void) {

	return 4;
}

const struct unittest_vtable_ card_unittest3[] = {{run}};