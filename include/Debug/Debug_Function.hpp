/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef DEBUG_FUNCTION_HPP
#define DEBUG_FUNCTION_HPP

#include <iostream>
#include <cstring>

class Debug_FFunction {
public:
	void Debug_Function(std::string, std::string);
	bool Debug_FReadFileWithReturn(std::string, std::string);
	std::string Debug_FRead(std::string);
};

#endif // DEBUG_FUNCTION_HPP
