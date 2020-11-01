/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <iostream>
#include <cstring>

class FInputStream {
public:
	std::string ReadFile(std::string directory,
        std::string variable);
};

#endif // INPUTSTREAM_HPP
