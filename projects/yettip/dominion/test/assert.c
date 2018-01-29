/************************************************************************
Author: Peter Yetti 
Date:  1/23/18
Description: Implementation for assert.c
*************************************************************************/

#include <stdio.h>
#include "assert.h"

void assertA_Equals_B(const void *expected, const void *actual, const char* testName) {
	if (expected == actual) {
		printf("TEST PASSED: %s\n", testName);
	} else {
		printf("TEST FAILED: %s\n", testName);
	}
}

void assertA_GreaterThan_B(const void *expected, const void *actual, const char* testName) {
	if (expected > actual) {
		printf("TEST PASSED: %s\n", testName);
	} else {
		printf("TEST FAILED: %s\n", testName);
	}
}

void assertTrue(const void *value, const char* testName) {
	if (value) {
		printf("TEST PASSED: %s\n", testName);
	} else {
		printf("TEST FAILED: %s\n", testName);
	}
}