/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <cstring>

#include <Interpreter/Variable.hpp>
#include <Interpreter/Input.hpp>

#include <StringTools.hpp>

void
FInput::GetInput(std::string name, Data_Types type) {
	FVariable var;

	std::string input;
	std::getline(std::cin, input);

    if(input.length() <= 2) input.append("  ");

    if(input != "") {
        switch(type) {
            case FLA_INT:
            {
                var.Change(name, input, FLA_INT);
            }

            case FLA_STRING:
            {
                var.Change(name, input, FLA_STRING);
            }
        }
    }
}

void
FInput::GetCharInput(std::string name) {
	FVariable var;

	std::string data;
	char input;

	input = getchar();

	data.push_back(input);
	data.append("  ");

	if(input != ' ') var.Change(name, data, FLA_STRING);
}
