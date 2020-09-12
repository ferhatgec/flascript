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
#include <Debug/Debug_String.hpp>
#include <Debug/Debug_Statement.hpp>
#include <Debug/Debug_Function.hpp>

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
Debug_FStatement::Debug_IfStatement(std::string file, std::string arg) {
	std::string assign, type, compare, type2;
	Debug_FInterpreter inp;
	inp.Debug_GetBtwString(arg, "if[", "] -> {", assign);
	if(assign != "error") {
		inp.Debug_GetBtwString(assign, "var(", ")", type);
		if(type == "int") {
			inp.Debug_GetBtwString(assign, "var(int) -> ", " <- (", type);
			if(type != "error") {
				/* type : variable name */
				inp.Debug_GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") { /* compare definitions */
					inp.Debug_GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "int") { 
						inp.Debug_GetBtwString(arg, "(==) var(int) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(int) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.Debug_GetBtwString(variable, "var(int) -> ", " -> ", variable); /* For compare */
								if(variable == assign) {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									std::string data;									
									inp.Debug_GetBtwString(read, "if[var(int) -> " + type + " <- (==) var(int) -> " + assign + " <-] -> {",
										"} else -> {", data);
									if(data != "error") {
										inp.Debug_FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.Debug_GetBtwString(read, "if[var(int) -> " + type + " <- (==) var(int) -> " + assign + " <-] -> {",
										"} <-", data);
										if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
										else
											inp.Debug_FlaScriptInterpreterWithArg(file, data);
									}								
								} else {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									inp.Debug_GetBtwString(read, "else -> {", "} <-", read);
									if(read != "error")
										inp.Debug_FlaScriptInterpreterWithArg(file, read);
								}
							}						
						} 
					} else {
						std::cout << "Warning: " + type2 + " : This type not integer, unable to compare with type1\n";
					}
				} else if(compare == "!=") {
					inp.Debug_GetBtwString(assign, "(!=) var(", ") -> ", type2);
					if(type2 == "int") { 
						inp.Debug_GetBtwString(arg, "(!=) var(int) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(int) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.Debug_GetBtwString(variable, "var(int) -> ", " -> ", variable); /* For compare */
								if(variable != assign) {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									std::string data;									
									inp.Debug_GetBtwString(read, "if[var(int) -> " + type + " <- (!=) var(int) -> " + assign + " <-] -> {",
										"} else -> {", data);
									if(data != "error") {
										inp.Debug_FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.Debug_GetBtwString(read, "if[var(int) -> " + type + " <- (!=) var(int) -> " + assign + " <-] -> {",
										"} <-", data);
										if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
										else
											inp.Debug_FlaScriptInterpreterWithArg(file, data);
									}								
								} else {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									inp.Debug_GetBtwString(read, "else -> {", "} <-", read);
									if(read != "error")
										inp.Debug_FlaScriptInterpreterWithArg(file, read);
								}
							}						
						} 
					} else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					}
				} else {}
			}
		} else if(type == "string") {
			inp.Debug_GetBtwString(assign, "var(string) -> ", " <- (", type);
			if(type != "error") {
				/* type : variable name */
				inp.Debug_GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") { /* compare definitions */
					inp.Debug_GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "string") { 
						inp.Debug_GetBtwString(arg, "(==) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(string) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.Debug_GetBtwString(variable, "var(string) -> ", " -> ", variable); /* For compare */
								if(variable == assign) {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									std::string data;									
									inp.Debug_GetBtwString(read, "if[var(string) -> " + type + " <- (==) var(string) -> " + assign + " <-] -> {",
										"} else -> {", data);
									if(data != "error") {
										inp.Debug_FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.Debug_GetBtwString(read, "if[var(string) -> " + type + " <- (==) var(string) -> " + assign + " <-] -> {",
										"} <-", data);
										if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
										else
											inp.Debug_FlaScriptInterpreterWithArg(file, data);
									}								
								} else {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									inp.Debug_GetBtwString(read, "else -> {", "} <-", read);
									if(read != "error")
										inp.Debug_FlaScriptInterpreterWithArg(file, read);
								}
							}						
						} 
					} else {
						std::cout << "Warning: " + type2 + " : This type not string, unable to compare with type1\n";
					}
				} else if(compare == "!=") {
					inp.Debug_GetBtwString(assign, "(!=) var(", ") -> ", type2);
					if(type2 == "string") { 
						inp.Debug_GetBtwString(arg, "(!=) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(string) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.Debug_GetBtwString(variable, "var(string) -> ", " -> ", variable); /* For compare */
								if(variable != assign) {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									std::string data;									
									inp.Debug_GetBtwString(read, "if[var(string) -> " + type + " <- (!=) var(string) -> " + assign + " <-] -> {",
										"} else -> {", data);
									if(data != "error") {
										inp.Debug_FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.Debug_GetBtwString(read, "if[var(string) -> " + type + " <- (!=) var(string) -> " + assign + " <-] -> {",
										"} <-", data);
										if(data == "error")
											std::cout << "if : Parse error. if[] -> {\n....\n} <-";
										else
											inp.Debug_FlaScriptInterpreterWithArg(file, data);
									}								
								} else {
									Debug_FFunction fnc;
									std::string read = fnc.Debug_FRead(file);
									inp.Debug_GetBtwString(read, "else -> {", "} <-", read);
									if(read != "error")
										inp.Debug_FlaScriptInterpreterWithArg(file, read);
								}
							}						
						} 
					} else {
						std::cout << type2 << " : This type not string, unable to compare with type1\n";
					}
				} else {}
			}
		} else if(type == "system") {
			inp.Debug_GetBtwString(assign, "var(system) -> ", " <- (", type);
			if(type != "error") {
				inp.Debug_GetBtwString(type, "check[", "]", type);
				std::string get_type = type;
				ExecutePlusPlus exec;
				type = exec.ExecWithOutput(type);
				type.pop_back();
				inp.Debug_GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") {
					inp.Debug_GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "string") {
						inp.Debug_GetBtwString(arg, "(==) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							if(type == assign) {
								Debug_FFunction fnc;
								std::string read = fnc.Debug_FRead(file);
								std::string data;

								inp.Debug_GetBtwString(read, "if[var(system) -> check[" + get_type + "] <- (==) var(string) -> " + assign + " <-] -> {", 
									"} else -> {", data);

								if(data != "error") {
									inp.Debug_FlaScriptInterpreterWithArg(file, data);
								} else {
									inp.Debug_GetBtwString(read, "if[var(system) -> check[" + get_type + "] <- (==) var(string) -> " + 
										assign + " <-] -> {", "} <-", data);
									
									if(data == "error")
											std::cout << "Error: if : Parse error. if[] -> {\n....\n} <-";
									else
											inp.Debug_FlaScriptInterpreterWithArg(file, data);						
								}
							} else {
								Debug_FFunction fnc;
								std::string read = fnc.Debug_FRead(file);
								inp.Debug_GetBtwString(read, "} else -> {", "} <-", read);
								if(read != "error")
									inp.Debug_FlaScriptInterpreterWithArg(file, read);
							}
						}
					} /* TODO: Add error messages. */
				}
			} else {
				std::cout << "Error: if : var(...) This type undefined!\n";
			}
	    	} else if(type == "nil") {
			inp.Debug_GetBtwString(assign, "var(nil) -> ", " <- (", type);
			if(type != "error") {
				if(stringtools::GetBetweenString(type, "is_exist[", "]") != "error") {
					inp.Debug_GetBtwString(type, "is_exist[", "]", type);
					if(type != "nil") {
						inp.Debug_GetBtwString(assign, "<- (", ") ", compare);
						if(compare != "error") {
							inp.Debug_GetBtwString(assign, "(" + compare + ") " + "var(", 
								") -> ", type2);

							if(type2 == "bool") {
								inp.Debug_GetBtwString(arg, "(" + compare + ") var(bool) -> ",
									" <-] -> {", assign);
								
								if(assign != "error") {
									bool stat;

									if(assign == "true")
										stat = true;
									else if(assign == "false")
										stat = false;

									if(compare == "==") {
										if(fsplusplus::IsExistFile(type) == stat) {
											Debug_FFunction fnc;
											std::string read = fnc.Debug_FRead(file);
											std::string data;
											inp.Debug_GetBtwString(read, "if[var(nil) -> is_exist[" + type + "] <- (==) var(bool) -> " + assign + " <-] -> {",
												"} else -> {", data);
											
											if(data != "error") {
												inp.Debug_FlaScriptInterpreterWithArg(file, data);
											} else {
												inp.Debug_GetBtwString(read, "if[var(nil) -> is_exist[" + type + "] <- (==) var(bool) -> " +
													assign + " <-] -> {", "} <-", data);
												
												if(data != "error")
													inp.Debug_FlaScriptInterpreterWithArg(file, data);
												else
													std::cout << file + ":" << WBOLD_RED_COLOR << " Parse error: " << WBOLD_LIGHT_WHITE_COLOR <<
														"if[..var(nil) ->..is_exist..var(..)] -> {..} <- : Parse error.\n";
											}
										} else {
											Debug_FFunction fnc;
											std::string read = fnc.Debug_FRead(file);
											inp.Debug_GetBtwString(read, "} else -> {", "} <-", read);

											if(read != "error")
												inp.Debug_FlaScriptInterpreterWithArg(file, read);
											else
												std::cout << file + ":" << WBOLD_RED_COLOR << " Parse error: " << WBOLD_LIGHT_WHITE_COLOR <<
													"if[.] .. else -> {..} <- : Parse error. } else -> {...} <-\n";
										}
									}
								}
							} else
								std::cout << file + ":" << WBOLD_RED_COLOR << " Type error: " << WBOLD_LIGHT_WHITE_COLOR <<
									"if[.. var(..)] -> {..} : Use bool type to compare.\n";
						}
					}
				} else
					std::cout << file + ":" << WBOLD_RED_COLOR << " Parse error: " << WBOLD_LIGHT_WHITE_COLOR <<
									"if[..is_exist[error]-> {..} <- : Add is_exist[...]\n";
			}
		}
	}
}


void
Debug_FStatement::Debug_StatementParser(std::string file, std::string arg) {
	std::string assign, type;
	Debug_FInterpreter inp;
	Debug_FFunction fnc;
	type = fnc.Debug_FRead(file);
	inp.Debug_GetBtwString(arg, "statement[", "]", assign);
	if(assign != "error") {
		inp.Debug_GetBtwString(type, assign + " ->", assign + " <-", assign);
		if(assign != "error") {
			Debug_IfStatement(file, assign);
		} else {
			std::cout << "Error: " + arg + " " + "Parse error.\n";
		}
	}
}

/*
	exit(type)
	
	exit(success)
	exit(failure)
*/

void
Debug_FStatement::Debug_ExitStatement(std::string file, std::string arg) {
	std::string assign, type;
	Debug_FInterpreter inp;
	Debug_FFunction fnc;
	inp.Debug_GetBtwString(arg, "exit(", ")", type);
	if(type == "success" || type == "SUCCESS") {}
	else if(type == "failure" || type == "FAILURE") {}
	else
		std::cout << "Warning: exit : Undefined type.\n";
}
