/* See LICENSE file for copyright and license details. */
/* Compile with: gcc -o test test.c emdb.c -Wall -Wextra -Wpedantic -std=c99 */

#include "emdb.h"

/* even though we include stdlib.h after emdb.h, the macros in emdb.h are still in force. */
#include <stdlib.h>

int main(void)
{
	int test_int = 20;
	char *test_str = "Test string!";
	char *test = calloc(10, sizeof(char)); /* not free'ing so we do get a memfile! */

	DEBUG("Basic dumps");
	DUMPINT(test_int, 0);
	DUMPSTR(test_str, 0);
	DEBUG("Extended dumps");
	DUMPINT(test_int, 1);
	DUMPSTR(test_str, 1);
	DEBUGW("This is a warning message");
	DEBUGE("This is an error message");
	DEBUGOK("This is an OK message!");

	DEBUG("Sleeping time");
	DEBUG("2 seconds...");
	SLEEP(2);
	DEBUGOK("Done");
	DEBUG("2 miliseconds...");
	SLEEP_MILI(2);
	DEBUGOK("Done");
	DEBUG("2 nanoseconds...");
	SLEEP_NANO(2);
	DEBUGOK("Done");
	DEBUG("2 microseconds...");
	SLEEP_MICRO(2);
	DEBUGOK("Done");

	return 0;
}
