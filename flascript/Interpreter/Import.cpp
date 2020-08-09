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

std::string FReadImport(std::string file) {
	std::string line, text;
    	std::ifstream readfile(("/usr/include/flascript/" + file).c_str());
    	if(readfile.is_open()) {
       		while (std::getline(readfile, line)) {
        		text.append(line + "\n");
        	}	
        	readfile.close();
		return text;
    	} else {
        	printf("Unable to open file\n"); 
 	}
	return "null";
}

void
FImport::Import(std::string file, std::string arg) {
	FInterpreter inp;
	FFunction func;
	FTokenizer token;
	std::string assign, type, put, fnc;
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
		} else {
			inp.GetBtwString(arg, "(<", ">)", assign);
			if(assign != "error") {
				type = FReadImport(assign);
				if(type != "null") { check = true; }
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
						std::string file;
						inp.GetBtwString(type, "import(\"", "\") -> " + assign, file);
						if(file != "error") {
							type = func.FRead(file);					
						} else {
							inp.GetBtwString(type, "import(<", ">) -> " + assign, file);
							if(file != "error") type = FReadImport(file);
						}
						if(inp.FindObject(arg, "func ->") == true) {
							inp.GetBtwString(arg, "[", " -> ", fnc);
							inp.GetBtwString(arg, fnc + " -> ", " <-", put);
							if(put != "error") {
								inp.GetBtwString(type, put + " {", "}", type);									
								if(type != "error") inp.FlaScriptInterpreterWithArg(file, type);
							}
						} else {
							inp.GetBtwString(arg, " -> ", " <-", put);
							if(put != "error") {
								inp.GetBtwString(type, "defin[" + put + "] -> ", "<-", type);
								if(type != "error") inp.FlaScriptInterpreterWithArg(assign, type);
							}
						}
							
					}
				}
			}
		}
	}
}	