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
#include <Debug/Debug_Exec.hpp>

// Libraries
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>
#include <ExecutePlusPlus.hpp>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// exec(system -> scrift ->[->arg])
void
Debug_FExec::Debug_Exec(std::string arg) {
	Debug_FInterpreter inp;
	if(inp.Debug_FindObject(arg, "exec") == true) {
		std::string assign;
		inp.Debug_GetBtwString(arg, "(", ")", assign);
		if(inp.Debug_FindObject(assign, "system") == true) {
			inp.Debug_GetBtwString(assign, " -> ", " ->", assign);
			if(assign != "error") {}
		        else
				std::cout << "exec(system) : Arrow Error.\n";
		}
	}
}

/* 
	executepp("ExecuteTest", "git")
	execout(-> git <-)
*/
void
Debug_FExec::Debug_ExecutePp(std::string arg) {
	Debug_FInterpreter inp;
	if(inp.Debug_FindObject(arg, "execout") == true) {
		std::string assign;
		inp.Debug_GetBtwString(arg, "execout(-> ", " <-)", assign);
		ExecutePlusPlus ex;
		assign = ex.ExecWithOutput(assign.c_str());		 
	} else if(inp.Debug_FindObject(arg, "executepp") == true) {
		std::string assign, first;
		inp.Debug_GetBtwString(arg, "(", ")", assign);
		inp.Debug_GetBtwString(assign, "\"", "\",", first);
		if(first != "error") {
			inp.Debug_GetBtwString(assign, ", \"", "\"", assign);
			if(assign != "error") {
			}
		}
	}
}
