/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <Interpreter/Math.hpp>

int64_t
FMath::Sqrt(int64_t i) {
	union {
		float f;
		int i;
	} v;
	
	v.f = (float)i;
	v.i -= 1 << 23; 
	
	v.i >>= 1;
	v.i += 1 << 29;
	
	return (int64_t)v.f;
}

/* Todo:
	Implement: i^x
*/
int64_t
FMath::Square(int64_t i) {
	return i * i;
}

int64_t
FMath::Factorial(int64_t i) {
	if(i > 1) { 
		i =  i * Factorial(i - 1);
	} else i = 1;
	
	return i;
}
