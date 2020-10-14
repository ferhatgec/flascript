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
	std::string _get_data;
	std::istringstream _get(variable_data);
	
	std::string c_data;
		
	while(std::getline(_get, _get_data)) {
		if(stringtools::GetBetweenString(_get_data, "(name: ", ")") == name)
			_get_data = "(name: " + name + ")" + "[data: " + stringtools::GetBetweenString(_get_data, "[data: ", "]") + data + "]";
			
		c_data.append(_get_data + "\n");
	}
	
	variable_data = c_data;
}

void
FVariable::Between(std::string name, std::string first, std::string second) {
	std::string _get_data;
	std::istringstream _get(variable_data);
	
	std::string c_data;
		
	while(std::getline(_get, _get_data)) {
		if(stringtools::GetBetweenString(_get_data, "(name: ", ")") == name) {
			_get_data = stringtools::GetBetweenString(_get_data, "[data: ", "]");
			_get_data = stringtools::GetBetweenString(_get_data, first, second);
			_get_data = "(name: " + name + ")" + "[data: " + _get_data + "]";
		}
		
		c_data.append(_get_data + "\n");
	}
	
	variable_data = c_data;
}

void
FVariable::Pop_Back(std::string name) {
	std::string _get_data;
	std::istringstream _get(variable_data);
	
	std::string c_data;
		
	while(std::getline(_get, _get_data)) {
		if(stringtools::GetBetweenString(_get_data, "(name: ", ")") == name) {
			_get_data = stringtools::GetBetweenString(_get_data, "[data: ", "]");
			
			if(_get_data.length() <= 1) {
				std::cout << name << ": @pop_back : length <= 1\n";
				return;
			}
			
			_get_data.pop_back();
			_get_data = "(name: " + name + ")" + "[data: " + _get_data + "]";
		}
		
		c_data.append(_get_data + "\n");
	}
	
	variable_data = c_data;
}
