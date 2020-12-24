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
#include <Interpreter/Variable.hpp>

// Libraries
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>
#include <ExecutePlusPlus.hpp>
#include <StringTools.hpp>

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
		
		stringtools::GetBtwString(arg, "(", ")", assign);
		
		if(inp.FindObject(assign, "system") == true) {
			stringtools::GetBtwString(assign, " -> ", " ->", assign);
			
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
		stringtools::GetBtwString(arg, "execout(-> ", " <-)", assign);
		
		if(assign == "error") {
		    stringtools::GetBtwString(arg, "execout(\"", "\")", assign);
		}

		ExecutePlusPlus ex;
		assign = ex.ExecWithOutput(assign.c_str());

		if(arg.find("var")) {
		    FVariable var;

		    std::string variable = stringtools::GetBetweenString(arg, "->", "<");

		    variable = stringtools::ltrim(variable);
		    variable = stringtools::rtrim(variable);

		    if(variable.length() > 4) { variable.erase(0, 4); variable.pop_back(); }

            /* As FLA_STRING */
            var.Equal(variable, assign);
		} else {
		    std::cout << assign;
	    }
	} else if(inp.FindObject(arg, "executepp") == true) {
		std::string assign, first;
		
		stringtools::GetBtwString(arg, "(", ")", assign);
		stringtools::GetBtwString(assign, "\"", "\",", first);
		
		if(first != "error") {
			std::string second = stringtools::GetBetweenString(assign, ", \"", "\"");
			
			// executepp("Name", var(data))
			if(second == "error") {
				FVariable var;
				second = stringtools::GetBetweenString(arg, ", var(", "))");	
				second = var.GetVariable(second);
			}
			
			ExecutePlusPlus ex;
			ex.ExecuteName(first.c_str());
			ex.RunFunction(second.c_str());
		}
	}
}
