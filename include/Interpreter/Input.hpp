/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <Interpreter/Variable.hpp>

class FInput {
public:
	void GetInput(std::string name, Data_Types type);
	void GetCharInput(std::string name);
};

#endif // INPUT_HPP
