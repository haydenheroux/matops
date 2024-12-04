#pragma once
#include <stdbool.h>

/*
 * Prints a message depending on if the test passes or fails.
 */
void test(const char *pass_message, const char *fail_message, bool passes);
