/* See LICENSE file for copyright and license details. */
/* Compile with: gcc -o test test.c emdb.c -Wall -Wextra -Wpedantic -std=c99 */

#include "emdb.h"

/* even though we include stdlib.h after emdb.h, the macros in emdb.h are still in force. */
#include <stdlib.h>

int main(void)
{
	int test_integer = 20;
	char *test_string = "Test string!";
	char *test = calloc(10, sizeof(char)); /* not free'ing so we do get a memfile! */

	DUMPINT(test_integer);
	DUMPSTR(test_string);

	return 0;
}
