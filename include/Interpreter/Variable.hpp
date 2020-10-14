/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <iostream>
#include <map>
#include <cstring>

#include <FileSystemPlusPlus.h>
#include <SystemInfo.hpp>

static std::map<std::string, std::string> variables {
        {"__OS_NAME__", fsplusplus::ReadOSName()},
        {"__KERNEL__", systemInfo::getSystem()},
        {"__TIME__",  __TIME__},
        {"__DATE__", __DATE__},
        {"__USERNAME__", systemInfo::getUsername()},
        {"__HOSTNAME__", systemInfo::getHostname()},
        {"__STRING__", "var(string)"},
        {"__INT__", "var(int)"},
        {"__BOOL__", "var(bool)"},
        {"__NEWLINE__", "\n"}
};

static auto var_ = variables;
static std::string variable_data;

class FVariable {
public:
	void Variable(std::string name, std::string data);
	std::string GetVariable(std::string name);
	
	void Change(std::string name, std::string data);
	void Append(std::string name, std::string data);
	void Between(std::string name, std::string first, std::string second);
};

#endif // VARIABLE_HPP
