/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

#include <FlaScriptMain.hpp>
#include <Interpreter/Variable.hpp>
#include <Interpreter/Tools.hpp>

#include <StringTools.hpp>

// (name: asdsa)[data: hi]
void
FVariable::Variable(std::string name, std::string data, Data_Types type) {
	switch(type) {
		case FLA_INT:
		{
			variable_data = variable_data.append("type: 'int' name: '"
				+ name
				+ "'\n"
				+ "start*\n"
				+ data
				+ "\n*end\n"
				+ "type: 'int' name: '"
				+ name
				+ "' end\n");

			break;
		}

		case FLA_STRING:
		{
            /* type: 'string' name: '....'
               start*

               *end
               type: 'string' name: '....' end
            */
            variable_data = variable_data.append("type: 'string' name: '"
				+ name
				+ "'\n"
				+ "start*\n"
				+ data
				+ "\n*end\n"
				+ "type: 'string' name: '"
				+ name
				+ "' end\n");

			break;
		}
	}
}

std::string
FVariable::GetVariable(std::string name) {
    std::string data = stringtools::GetBetweenString(variable_data,
        STR("type: 'string' name: '") + name + STR("'\nstart*\n"),
            STR("\n*end\n") + STR("type: 'string' name: '") + name + STR("' end\n"));

	/* integer found */
	if(data == "error") {
        data = stringtools::GetBetweenString(variable_data,
        STR("type: 'int' name: '") + name + STR("'\nstart*\n"),
            STR("\n*end\n") + STR("type: 'int' name: '") + name + STR("' end\n"));
	}

    return data;
}


void
FVariable::Change(std::string name, std::string data, Data_Types type) {
    std::string _data;

	switch (type) {
		case FLA_INT:
		{
			_data = stringtools::GetBetweenString(variable_data,
                STR("type: 'int' name: '") + name + STR("'\nstart*\n"),
                STR("\n*end\n") + STR("type: 'int' name: '") + name + STR("' end\n"));

			break;
		}

		case FLA_STRING:
		{
			_data = stringtools::GetBetweenString(variable_data,
                STR("type: 'string' name: '") + name + STR("'\nstart*\n"),
                STR("\n*end\n") + STR("type: 'string' name: '") + name + STR("' end\n"));

			break;
		}
	}

    stringtools::replace(variable_data, _data, data);
}

void
FVariable::Append(std::string name, std::string data) {
	std::string data_ = GetVariable(name);
    data_.append(data);

    Change(name, data_, FLA_STRING);
}

void
FVariable::Between(std::string name, std::string first, std::string second) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::GetBetweenString(data_, first, second);

    Change(name, data_, FLA_STRING);
}

void
FVariable::Pop_Back(std::string name) {
	std::string data_ = GetVariable(name);
    data_.pop_back();

    Change(name, data_, FLA_STRING);
}

void
FVariable::Pop_Front(std::string name) {
	std::string data_ = GetVariable(name);

    data_ = data_.erase(0, 1);

    Change(name, data_, FLA_STRING);
}

void
FVariable::Strip(std::string name) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::EraseAllSubString(data_, " ");

    Change(name, data_, FLA_STRING);
}


void
FVariable::Substring(std::string name, std::string substring) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::EraseAllSubString(data_, substring);

    Change(name, data_, FLA_STRING);
}

void
FVariable::Equal(std::string name, std::string data) {
    Change(name, data, FLA_STRING);
}
