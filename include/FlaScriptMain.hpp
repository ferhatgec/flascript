/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef FLA_SCRIPT_MAIN_HPP
#define FLA_SCRIPT_MAIN_HPP

#include <iostream>
#include <string>

typedef struct {
	std::string file;
	int32_t argc;
	char** argv;	
} flascript_t;

#endif // FLA_SCRIPT_MAIN_HPP
