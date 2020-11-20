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
#include <Interpreter/Interpreter.hpp>
#include <Interpreter/Read.hpp>
#include <Interpreter/String.hpp>

// Libraries
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>
#include <StringTools.hpp>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// EraseAllSubstring(string["Hello FlaScript!", "ll"])
std::string
FString::EraseAllSubString(std::string arg) {
	FInterpreter inp;
	std::string assign, type;	

	if(inp.FindObject(arg, "EraseAllSubstring") == true) {

		stringtools::GetBtwString(arg, "(", ")", assign);
		
		if(inp.FindObject(assign, "string") == true) {
			stringtools::GetBtwString(assign, "[", "]", assign);
			
			if(assign != "error") {
				stringtools::GetBtwString(assign, "\"", "\",", type);
				
				if(type != "error") {
					stringtools::GetBtwString(assign, ", \"", "\"", assign);
					
					if(assign != "error") {
						assign = stringtools::EraseAllSubString(type, assign);
						
						if(assign != "error") {
							return assign;
						}
					}
				} 
			} 
		}
	}

	return assign;
}
