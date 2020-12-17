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

#include <FlaVersion.hpp>
#include <FileSystemPlusPlus.h>
#include <SystemInfo.hpp>


static systemInfo info;

static std::map<std::string, std::string> variables {
        {"__OS_NAME__", fsplusplus::ReadOSName()},
        {"__KERNEL__", systemInfo::getSystem()},
        {"FLASCRIPT_VERSION", FLASCRIPT_VERSION},
        {"FLASCRIPT_STATE", FLASCRIPT_STATE},
        {"__TIME__",  __TIME__},
        {"__DATE__", __DATE__},
        {"__USERNAME__", systemInfo::getUsername()},
        {"__HOSTNAME__", systemInfo::getHostname()},
        {"__STRING__", "var(string)"},
        {"__INT__", "var(int)"},
        {"__BOOL__", "var(bool)"},
        {"__UPTIME__", info.getUptime()},
        {"__NEWLINE__", "\n"}
};

enum Data_Types {
	FLA_INT = 1,
	FLA_STRING = 2
};

static auto var_ = variables;
static std::string variable_data;

class FVariable {
public:
	void Variable(std::string name, std::string data, Data_Types type);
	std::string GetVariable(std::string name);

	void Change(std::string name, std::string data, Data_Types type);
	void Append(std::string name, std::string data);
	void Between(std::string name, std::string first, std::string second);

    void Equal(std::string name, std::string data);
	void Substring(std::string name, std::string substring);
	void Strip(std::string name);
	void Pop_Back(std::string name);
};

#endif // VARIABLE_HPP
