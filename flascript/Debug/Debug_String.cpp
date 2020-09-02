/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>
#include <Tokenizer.hpp>

#include <Debug/Debug_Interpreter.hpp>
#include <Debug/Debug_Read.hpp>
#include <Debug/Debug_String.hpp>

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

// EraseAllSubstring(string["Hello FlaScript!", "ll"])
std::string
Debug_FString::Debug_EraseAllSubString(std::string arg) {
	Debug_FInterpreter inp;
	if(inp.Debug_FindObject(arg, "EraseAllSubstring") == true) {
		std::string assign, type;
		inp.Debug_GetBtwString(arg, "(", ")", assign);
		if(inp.Debug_FindObject(assign, "string") == true) {
			inp.Debug_GetBtwString(assign, "[", "]", assign);
			if(assign != "error") {
				inp.Debug_GetBtwString(assign, "\"", "\",", type);
				if(type != "error") {
					inp.Debug_GetBtwString(assign, ", \"", "\"", assign);
					if(assign != "error") {
						assign = inp.Debug_EraseAllSubString(type, assign);
						if(assign != "error") {
						}
					}
				} 
			} 
		}
	}
}
