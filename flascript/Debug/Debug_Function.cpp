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
#include <Debug/Debug_Function.hpp>

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

bool
Debug_FFunction::Debug_FReadFileWithReturn(std::string file, std::string argument) {
	Debug_FInterpreter inp;
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	if(inp.Debug_FindObject(line, argument) == true) {
        		return true;
        	}
        }
        readfile.close();
    	} else {
        	std::cout << "Warning: " + argument + " " + "Unable to open file\n";
    	}
	return false;
}

std::string
Debug_FFunction::Debug_FRead(std::string file) {
	std::string line, text;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
       		while (std::getline(readfile, line)) {
        		text.append(line + "\n");
        	}
        	readfile.close();
		return text;
    	} else {
        	std::cout << "Warning: " + file + " " + "Unable to open file\n";
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
Debug_FFunction::Debug_Function(std::string file, std::string arg) {
	std::string assign, type;
	Debug_FInterpreter inp;
	FTokenizer token;
	type = Debug_FRead(file);
	//if(inp.FindObject(arg, " ") == true) {
	for(int t = 0; t != arg.length(); t++) {
		if(arg[t] == ' ') {
			arg = arg.erase(0, 1);
		}
	}
        //}
	if(arg[arg.size() - 1] == ' ') {
		std::cout << "Error" + arg + " " +  "Whitespace error.\n";
		std::cout << "             ^^^\n";
	}

	if(inp.Debug_FindObject(type, arg + token.Whitespace + token.CurlyBracketsBegin) == true) {
		inp.Debug_GetBtwString(type, arg + token.Whitespace + token.CurlyBracketsBegin, "}", assign);
		if(assign != "error") {
			inp.Debug_FlaScriptInterpreterWithArg(file, assign);
		} else {
			std::cout << "Error: " + arg + " " + "Tokenizer parse error.\n";
		}
	}
}


/*
  func -> printc(:string str, color& cl:) {
	print(...)
  }

  main() -> main {
	func -> printc("Hello world!", [:11, 33:])
  }
*/
