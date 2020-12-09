/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <Interpreter/Random.hpp>

/* Libraries */
#include <StringTools.hpp>

/* TODO:
	Implement rand() from scratch.

	syntax:
		@random(start, end) -> variable <
		@random(10, 20) -> test <
*/

int64_t
FRandom::Random(int64_t start) {
	/* reset UNIX time */
	srand(time(NULL));
	
	return rand() % (start + 1);
}
