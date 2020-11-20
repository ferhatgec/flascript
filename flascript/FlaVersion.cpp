/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <cstring>

#include <FlaVersion.hpp>
#include <Interpreter/Interpreter.hpp>

#include <StringTools.hpp>

std::string
FlaVersion::Time() {
	FInterpreter intp;
	std::string ftime(__TIME__); // Convert

	return stringtools::EraseAllSubString(ftime, ":");
}

std::string
FlaVersion::VersionAlgorithm() {
	std::string version;
	version.append(FLASCRIPT_VERSION);
	version.append(Hyphen);
	version.append(FLASCRIPT_STATE);
	version.append(Hyphen);
	version.append(Time());
	
	return version;
}
