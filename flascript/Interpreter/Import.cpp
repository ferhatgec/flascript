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
#include <Interpreter/Definitions.hpp>
#include <Interpreter/Function.hpp>
#include <Interpreter/Import.hpp>

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

/* test.flsh:
 defin[BOLD_RED_COLOR] -> print... <-
 
 test.fls
 import("test.flsh") -> test 
 put[test -> BOLD_RED_COLOR <-]
*/

bool check = false;

void
FImport::Import(std::string file, std::string arg) {
	FInterpreter inp;
	FFunction func;
	FTokenizer token;
	std::string assign, type, put;
	if(inp.FindObject(arg, "import") == true) {		
		inp.GetBtwString(arg, "(\"", "\")", assign);
		if(assign != "error") {
			type = func.FRead(assign);
			if(type != "null") {
				check = true;
			} else {
				std::cout << "import(\"" <<
				assign << "\")" << " : File not found.\n"; 
			}			
		}	
	} else if(inp.FindObject(arg, "put") == true) {
		inp.GetBtwString(arg, "[", "]", assign);
		if(assign != "error") {
			if(check == true) {
				inp.GetBtwString(arg, "[", " -> ", assign);
				if(assign != "error") {				
					type = func.FRead(file);
					if(type != "null") {
						inp.GetBtwString(type, "import(\"", "\") -> " + assign, assign);
						if(assign != "error") {
							type = func.FRead(assign);
							inp.GetBtwString(arg, " -> ", " <-", put);
							if(put != "error") {
								inp.GetBtwString(type, "defin[" + put + "] -> ", "<-", type);
								if(type != "error") {
									inp.FlaScriptInterpreterWithArg(assign, type);
								}
							}						
						}
					}
				}
			}
		}
	}
}

