/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>
#include <FlaVersion.hpp>
#include <Tokenizer.hpp>

#include <Debug/Debug_Interpreter.hpp>
#include <Debug/Debug_Read.hpp>

#include <ExecutePlusPlus.hpp>

// Libraries
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// exec(system -> scrift ->[->arg])
void
Debug_FRead::Debug_Read(std::string arg) {
	Debug_FInterpreter inp;
	if(inp.Debug_FindObject(arg, "read") == true) {
		std::string assign;
		inp.Debug_GetBtwString(arg, "(", ")", assign);
		if(assign != "error" && assign == "string&") {
			inp.Debug_GetBtwString(arg, "type[", "]", assign);
			if(assign != "error") {
			}
		}
	}
}
