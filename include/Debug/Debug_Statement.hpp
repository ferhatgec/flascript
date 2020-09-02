/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef DEBUG_STATEMENT_HPP
#define DEBUG_STATEMENT_HPP

#include <iostream>
#include <cstring>

class Debug_FStatement {
public:
	static void Debug_IfStatement(std::string, std::string);
	static void Debug_StatementParser(std::string, std::string);

	static void Debug_ExitStatement(std::string, std::string);
};

#endif // DEBUG_STATEMENT_HPP
