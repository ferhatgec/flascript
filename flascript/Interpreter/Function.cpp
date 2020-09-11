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

bool
FFunction::FReadFileWithReturn(std::string file, std::string argument) {
	FInterpreter inp;
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	if(inp.FindObject(line, argument) == true)
        		return true;

        }
        readfile.close();
    	} /*else {
        	printf("Unable to open file\n");
    	}*/
	return false;
}

std::string
FFunction::FRead(std::string file) {
	std::string line, text;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
       		while (std::getline(readfile, line))
        		text.append(line + "\n");

        	readfile.close();
		return text;
    	} /*else {
        	printf("Unable to open file\n");
 	}*/
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
	} PrintHello;
*/

/*
	int : func -> Test() {
		return 1
	} Test;
*/

void
FFunction::Function(std::string file, std::string arg) {
	std::string assign, type, name;
	FInterpreter inp;
	FTokenizer token;
	type = FRead(file);
	//if(inp.FindObject(arg, " ") == true) {
	for(int t = 1; t != arg.length(); t++) {
		if(arg[t] == ' ') {
			arg = arg.erase(0, 1); 
		}
	}

        /*}
	if(arg[arg.size() - 1] == ' ') {
		printf("func -> ..()   : Whitespace error.\n");
		printf("             ^^^\n");
	}*/

	if(strstr(arg.c_str(), "func ->")) {}
	else
		arg = "f" + arg;
	

	name = stringtools::GetBetweenString(arg, " -> ", "()");
	
	if(inp.FindObject(type, arg + token.Whitespace + token.CurlyBracketsBegin) == true) {
		inp.GetBtwString(type, arg + token.Whitespace + token.CurlyBracketsBegin, "} " + name + ";", assign);
		if(assign != "error")
			inp.FlaScriptInterpreterWithArg(file, assign);
	}
}


/*
  func -> printc(:string str, color& cl:) {
	print(...)
  } printc;

  main() -> main {
	func -> printc("Hello world!", [:11, 33:])
  }
*/
