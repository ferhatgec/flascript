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
#include <Interpreter/Function.hpp>

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

bool
FFunction::FReadFileWithReturn(std::string file, std::string argument) {
	FInterpreter inp;
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	if(inp.FindObject(line, argument) == true) {
        		return true;
        	}
        }
        readfile.close();
    	} else {
        	printf("Unable to open file\n");
    	}
	return false;
}

std::string
FFunction::FRead(std::string file) {
	std::string line, text;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
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

/*
* Function call. Example:
	main() -> main {	
		func() -> PrintHello()
	}

* PrintHello function.
	func -> PrintHello() {
		print(string) -> "Hello!"
		print(newline)
	}.
*/

/*
	int : func -> Test() {
		return 1
	}
*/

void
FFunction::Function(std::string file, std::string arg) {
	std::string assign, type;
	FInterpreter inp;
	FTokenizer token;
	type = FRead(file);
	//if(inp.FindObject(arg, " ") == true) {
	for(int t = 0; t != arg.length(); t++) {
		if(arg[t] == ' ') {
			arg = arg.erase(0, 1);		
		}
	}
        //}
	if(arg[arg.size() - 1] == ' ') {
		printf("func -> ..()   : Whitespace error.\n");
		printf("             ^^^\n");
	}
	
	if(inp.FindObject(type, arg + token.Whitespace + token.CurlyBracketsBegin) == true) {
		inp.GetBtwString(type, arg + token.Whitespace + token.CurlyBracketsBegin, "}", assign);
		if(assign != "error") {
			inp.FlaScriptInterpreterWithArg(file, assign);
		}
	}
}
