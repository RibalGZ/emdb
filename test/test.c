/* See LICENSE file for copyright and license details. */
#include <emdb.h>
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

	if (emdb_var_is_dyn(test))
		DEBUGOK("Detected dynamic variable");

	if (!emdb_var_is_dyn(&test_int))
		DEBUGOK("Detected static variable");

	DEBUG("Sleeping time");
	DEBUG("2 seconds...");
	SLEEP(2);
	DEBUGOK("Done");
	DEBUG("1000 miliseconds...");
	SLEEP_MILI(1000);
	DEBUGOK("Done");
	DEBUG("1000000 microseconds...");
	SLEEP_MICRO(1000000L);
	DEBUGOK("Done");
	DEBUG("1000000000 nanoseconds...");
	SLEEP_NANO(1000000000L);
	DEBUGOK("Done");

	return 0;
}
