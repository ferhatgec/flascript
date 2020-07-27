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
#include "../../Library/FileSystemPlusPlus.h"
#include "../../Library/Colorized.hpp"
#include "../../Library/SystemInfo.hpp"

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
			if(assign != "error") {
				system(assign.c_str());
			} else {
				printf("exec(system) : Arrow Error!\n");
			}
		}	
	} 
}
