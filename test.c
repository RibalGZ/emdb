/* See LICENSE file for copyright and license details. */

/* Compile with: 
 * gcc -o test test.c emdb.c -Wall -Wextra -Wpedantic -std=c99
 */

#include "emdb.h"

/* Even though we include stdlib.h after emdb.h, the macros in emdb.h are still
 * in force. */
#include <stdlib.h>

int main(void)
{
    char *test = calloc(10, sizeof(char));

    /* Not free'ing so we do get a memfile!  */
    return 0;
}
