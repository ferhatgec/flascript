/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <iostream>
#include <cstring>

class FStatement {
public:
	void IfStatement(std::string, std::string);
	void StatementParser(std::string, std::string);

	void ExitStatement(std::string, std::string);
};

#endif // STATEMENT_HPP
