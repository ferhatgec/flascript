/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <cstring>

class FTools {
public:
	void TextBackground(int);
	
	std::string EscapeSeq(std::string data);
	std::string Sequence(std::string data);

	std::string StandardSeq(std::string data) {
		return Sequence(data);
	}
};

#endif // TOOLS_HPP
