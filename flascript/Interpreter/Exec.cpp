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
#include <Interpreter/Exec.hpp>

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
FExec::Exec(std::string arg) {
	FInterpreter inp;
	if(inp.FindObject(arg, "exec") == true) {
		std::string assign;
		inp.GetBtwString(arg, "(", ")", assign);
		if(inp.FindObject(assign, "system") == true) {
			inp.GetBtwString(assign, " -> ", " ->", assign);
			if(assign != "error")
				system(assign.c_str());
			/*else {
				std::cout << "exec(system) : Arrow Error.\n";
			}*/
		}
	}
}

/* 
	executepp("ExecuteTest", "git")
	execout(-> git <-)
*/
void
FExec::ExecutePp(std::string arg) {
	FInterpreter inp;
	if(inp.FindObject(arg, "execout") == true) {
		std::string assign;
		inp.GetBtwString(arg, "execout(-> ", " <-)", assign);
		ExecutePlusPlus ex;
		assign = ex.ExecWithOutput(assign.c_str());
		std::cout << assign;		 
	} else if(inp.FindObject(arg, "executepp") == true) {
		std::string assign, first;
		inp.GetBtwString(arg, "(", ")", assign);
		inp.GetBtwString(assign, "\"", "\",", first);
		if(first != "error") {
			inp.GetBtwString(assign, ", \"", "\"", assign);
			if(assign != "error") {
				ExecutePlusPlus ex;
				ex.ExecuteName(first.c_str());
				ex.RunFunction(assign.c_str());
			}
		}
	}
}
