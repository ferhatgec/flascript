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
#include <Interpreter/String.hpp>
#include <Interpreter/Statement.hpp>
#include <Interpreter/Function.hpp>

// Libraries
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>
#include <StringTools.hpp> /* for FindStringWithReturn etc. */

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/*
	main() -> main {
		var(int) -> 3.14159265359 -> PI <-

		if[var(int) -> PI <- (==) var(int) -> 3.14159265359 <-] -> {
			print(string) -> "Passed"
		} <-
	}
*/

void 
FStatement::IfStatement(std::string file, std::string arg) {
	std::string assign, type, compare, type2;
	FInterpreter inp;
	inp.GetBtwString(arg, "if[", "] -> {", assign);
	if(assign != "error") {
		inp.GetBtwString(assign, "var(", ")", type);
		if(type == "int") {
			inp.GetBtwString(assign, "var(int) -> ", " <- (", type);
			if(type != "error") {
				/* type : variable name */
				inp.GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") { /* compare definitions */
					inp.GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "int") { 
						inp.GetBtwString(arg, "(==) var(int) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(int) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.GetBtwString(variable, "var(int) -> ", " -> ", variable); /* For compare */
								if(variable == assign) {
									FFunction fnc;
									std::string read = fnc.FRead(file);									
									inp.GetBtwString(read, "if[var(int) -> " + type + " <- (==) var(int) -> " + assign + " <-] -> {",
										"} <-", read);
									if(read != "error")
										inp.FlaScriptInterpreterWithArg(file, read);
									else
										std::cout << "if : Parse error. if[] -> {\n....\n} <-";
								}
							}						
						} 
					} else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					}
				}  
			}
		}
	}
}


void
FStatement::StatementParser(std::string file, std::string arg) {
	std::string assign, type;
	FInterpreter inp;
	FFunction fnc;
	type = fnc.FRead(file);
	inp.GetBtwString(arg, "statement[", "]", assign);
	if(assign != "error") {
		inp.GetBtwString(type, assign + " ->", assign + " <-", assign);
		if(assign != "error") {
			IfStatement(file, assign);
		}
	}
}

