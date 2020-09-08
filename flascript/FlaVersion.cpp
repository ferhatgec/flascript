/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <Interpreter/Interpreter.hpp>
#include <FlaVersion.hpp>
#include <iostream>
#include <cstring>

std::string
FlaVersion::Time() {
	FInterpreter intp;
	std::string ftime(__TIME__); // Convert
	return intp.EraseAllSubString(ftime, ":");
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
