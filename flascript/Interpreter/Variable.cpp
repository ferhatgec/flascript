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
	variable_data = variable_data.append("{" + name + "};(name: " + name + ");" + "{" + name + "};[data: start:{\n" + data + "\n:end]<" + name + ">;\n");
}

std::string
FVariable::GetVariable(std::string name) {
    std::string data = stringtools::GetBetweenString(variable_data, "{" + name + "};(name: " + name + ");{" + name + "};[data: start:{\n", "\n:end]<" + name + ">;\n");
    
    /* TODO:
    	Create escape sequences function
    	escapeSeq(std::string)
    */
    stringtools::replaceAll(data, "\\033[", "\033[");
    stringtools::replaceAll(data, "\\n", "\n");
    stringtools::replaceAll(data, "\\t", "\t");
    stringtools::replaceAll(data, "\\a", "\a");
    stringtools::replaceAll(data, "\\b", "\b");
    stringtools::replaceAll(data, "\\v", "\v");
    stringtools::replaceAll(data, "\\r", "\r");
    
    return data;
}

// stringtools::GetBetweenString(variable_data, "{" + name + "};(name: " + name + ");{" + name + "};[data: start:{\n", "\n:end]<" + name + ">;\n");

void
FVariable::Change(std::string name, std::string data) {
    std::string _data = stringtools::GetBetweenString(variable_data, "{" + name + "};(name: " + name + ");{" + name + "};[data: start:{\n", 
        "\n:end]<" + name + ">;\n");    
	
	if(data.length() == 0) { data = "  "; }
	
    stringtools::replace(variable_data, _data, data);
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
