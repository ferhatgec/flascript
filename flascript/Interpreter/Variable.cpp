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
#include <Interpreter/Variable.hpp>

#include <StringTools.hpp>

// (name: asdsa)[data: hi]
void
FVariable::Variable(std::string name, std::string data) {
	variable_data = variable_data.append("(name: " + name + ")" + "[data: " + data + "]\n");
}

std::string
FVariable::GetVariable(std::string name) {
	std::string _get_data;
	std::istringstream _get(variable_data);
	
	while(std::getline(_get, _get_data)) {
		if(stringtools::GetBetweenString(_get_data, "(name: ", ")") == name)
			return stringtools::GetBetweenString(_get_data, "[data: ", "]");
	}
	
}

void
FVariable::Change(std::string name, std::string data) {
	std::string _get_data;
	std::istringstream _get(variable_data);
	
	std::string c_data;
		
	while(std::getline(_get, _get_data)) {
		if(stringtools::GetBetweenString(_get_data, "(name: ", ")") == name)
			_get_data = "(name: " + name + ")" + "[data: " + data + "]";
			
		c_data.append(_get_data + "\n");
	}
	
	variable_data = c_data;
}

void
FVariable::Append(std::string name, std::string data) {
	std::string data_ = GetVariable(name);
    data_.append(data);

    Change(name, data_);
}

void
FVariable::Between(std::string name, std::string first, std::string second) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::GetBetweenString(data_, first, second);

    Change(name, data_);
}

void
FVariable::Pop_Back(std::string name) {
	std::string data_ = GetVariable(name);
    data_.pop_back();

    Change(name, data_);
}

void
FVariable::Strip(std::string name) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::EraseAllSubString(data_, " ");
		
    Change(name, data_);	
}


void
FVariable::Substring(std::string name, std::string substring) {
	std::string data_ = GetVariable(name);
    data_ = stringtools::EraseAllSubString(data_, substring);
		
    Change(name, data_);	
}

void
FVariable::Equal(std::string name, std::string data) {
    Change(name, data);
}
