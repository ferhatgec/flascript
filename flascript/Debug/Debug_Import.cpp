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
#include <Debug/Debug_Definitions.hpp>
#include <Debug/Debug_Function.hpp>
#include <Debug/Debug_Import.hpp>

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

/* test.flsh:
 defin[BOLD_RED_COLOR] -> print... <-

 test.fls
 import("test.flsh") -> test
 put[test -> BOLD_RED_COLOR <-]
*/

static bool check = false;

static std::string FReadImport(std::string file) {
	std::string line, text;
    	std::ifstream readfile(("/usr/include/flascript/" + file).c_str());
    	if(readfile.is_open()) {
       		while (std::getline(readfile, line)) {
        		text.append(line + "\n");
        	}
        	readfile.close();
		return text;
    	} else {
        	std::cout << "Warning: import " + file + " : Unable to open file\n"; 
 	}
	return "null";
}

void
Debug_FImport::Debug_Import(std::string file, std::string arg) {
	Debug_FInterpreter inp;
	Debug_FFunction func;
	FTokenizer token;
	std::string assign, type, put, fnc;
	if(inp.Debug_FindObject(arg, "import") == true) {
		inp.Debug_GetBtwString(arg, "(\"", "\")", assign);
		if(assign != "error") {
			type = func.Debug_FRead(assign);
			if(type != "null") {
				check = true;
			} else {
				std::cout << "Error: import(\"" <<
				assign << "\")" << " : File not found.\n";
			}
		} else {
			inp.Debug_GetBtwString(arg, "(<", ">)", assign);
			if(assign != "error") {
				type = FReadImport(assign);
				if(type != "null") { check = true; }
			}
		}
	} else if(inp.Debug_FindObject(arg, "put") == true) {
		inp.Debug_GetBtwString(arg, "[", "]", assign);
		if(assign != "error") {
			if(check == true) {
				inp.Debug_GetBtwString(arg, "[", " -> ", assign);
				if(assign != "error") {
					type = func.Debug_FRead(file);
					if(type != "null") {
						std::string file;
						inp.Debug_GetBtwString(type, "import(\"", "\") -> " + assign, file);
						if(file != "error") {
							type = func.Debug_FRead(file);
						} else {
							inp.Debug_GetBtwString(type, "import(<", ">) -> " + assign, file);
							if(file != "error") type = FReadImport(file);
						}
						if(inp.Debug_FindObject(arg, "func ->") == true) {
							inp.Debug_GetBtwString(arg, "[", " -> ", fnc);
							inp.Debug_GetBtwString(arg, fnc + " -> ", " <-", put);
							if(put != "error") {
								inp.Debug_GetBtwString(type, put + " {", "}", type);
								if(type != "error") inp.Debug_FlaScriptInterpreterWithArg(file, type);
							}
						} else {
							inp.Debug_GetBtwString(arg, " -> ", " <-", put);
							if(put != "error") {
								inp.Debug_GetBtwString(type, "defin[" + put + "] -> ", "<-", type);
								if(type != "error") inp.Debug_FlaScriptInterpreterWithArg(assign, type);
							}
						}

					}
				}
			}
		}
	} else {
		std::cout << "Error: " + arg + " " + "Undefined function.\n";
	}
}