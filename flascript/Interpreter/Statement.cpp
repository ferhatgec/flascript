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
#include <ExecutePlusPlus.hpp>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/* 
	/> integer test </
	var(int) -> 3.14159265359 -> PI <-

	#pi ->
		if[var(int) -> PI <- (==) var(int) -> 3.14159265359 <-] -> {
			print(string) -> "Passed"
		} else -> {
			print(string) -> "Failed"
		} <-
	#pi <-

	main() -> main {
		statement[#pi]
	}


	/> environment test </
	#pi ->
		if[var(system) -> check[whoami] <- (==) var(int) -> 3.14159265359 <-] -> {
			print(string) -> "Passed"
		} else -> {
			print(string) -> "Failed"
		} <-
	#pi <-

	main() -> main {
		statement[#pi]
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
									std::string data;									
									inp.GetBtwString(read, "if[var(int) -> " + type + " <- (==) var(int) -> " + assign + " <-] -> {",
										"} else -> {", data);
									if(data != "error") {
										inp.FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.GetBtwString(read, "if[var(int) -> " + type + " <- (==) var(int) -> " + assign + " <-] -> {",
										"} <-", data);
										if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
										else
											inp.FlaScriptInterpreterWithArg(file, data);
									}								
								} else {
									FFunction fnc;
									std::string read = fnc.FRead(file);
									inp.GetBtwString(read, "else -> {", "} <-", read);
									if(read != "error")
										inp.FlaScriptInterpreterWithArg(file, read);
								}
							}						
						} 
					} else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					}
				}  
			}
		} else if(type == "system") {
			inp.GetBtwString(assign, "var(system) -> ", " <- (", type);
			if(type != "error") {
				inp.GetBtwString(type, "check[", "]", type);
				std::string get_type = type;
				ExecutePlusPlus exec;
				type = exec.ExecWithOutput(type);
				type.pop_back();
				inp.GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") {
					inp.GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "string") {
						inp.GetBtwString(arg, "(==) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							if(type == assign) {
								FFunction fnc;
								std::string read = fnc.FRead(file);
								std::string data;

								inp.GetBtwString(read, "if[var(system) -> check[" + get_type + "] <- (==) var(string) -> " + assign + " <-] -> {", 
									"} else -> {", data);

								if(data != "error") {
									inp.FlaScriptInterpreterWithArg(file, data);
								} else {
									inp.GetBtwString(read, "if[var(system) -> check[" + get_type + "] <- (==) var(string) -> " + 
										assign + " <-] -> {", "} <-", data);
									
									if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
									else
											inp.FlaScriptInterpreterWithArg(file, data);						
								}
							} else {
								FFunction fnc;
								std::string read = fnc.FRead(file);
								inp.GetBtwString(read, "} else -> {", "} <-", read);
								if(read != "error")
									inp.FlaScriptInterpreterWithArg(file, read);
							}
						}
					} /* TODO: Add error messages. */
				}
			} else {
				std::cout << "if : var(...) This type undefined!\n";
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

