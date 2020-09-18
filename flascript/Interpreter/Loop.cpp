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
#include <Interpreter/Loop.hpp>

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
		while[var(int) -> PI <- (==) var(int) -> 3.14159265359 <-] -> {
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
		while[var(system) -> check[whoami] <- (==) var(int) -> 3.14159265359 <-] -> {
			print(string) -> "Passed"
		} else -> {
			print(string) -> "Failed"
		} <-
	#pi <-

	main() -> main {
		statement[#pi]
	}

	/> is exist </
	#is_exist ->
		while[var(nil) -> is_exist[] <- (==) var(bool) -> true <-] -> {

		} <-
	#is_exist <-
*/

void
FLoop::While(std::string file, std::string arg) {
	std::string assign, type, compare, type2;
	FInterpreter inp;

	inp.GetBtwString(arg, "while[", "] -> {", assign);
	if(assign != "error") {
		/* Get type */
		inp.GetBtwString(assign, "var(", ")", type);
		if(type == "int") {
			/* Get data */
			inp.GetBtwString(assign, "var(int) -> ", " <- (", type);
			if(type != "error") {
				/* type : variable name */
				inp.GetBtwString(assign, "<- (", ") ", compare);
				/*
					compare operators:
					==
					!=

					TODO:
						=>
						<=
						>
						<
						<=>
						&& = null, nil
				*/
				if(compare == "==") { /* compare definitions */
					/* Get second compare type */
					inp.GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "int") {
						/* Get second compare data */
						inp.GetBtwString(arg, "(==) var(int) -> ", " <-] -> {", assign);
						if(assign != "error") {
							/* var(int) -> .... */
							std::string variable = stringtools::FindStringWithReturn(file, "var(int) -> " + assign +
								" -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.GetBtwString(variable, "var(int) -> ", " -> ", variable); /* For compare */
								while(1) {
									if(variable == assign) {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										std::string data;
										inp.GetBtwString(read, "while[var(int) -> " + type + " <- (==) var(int) -> " +
											assign + " <-] -> {", "} else -> {", data);

										if(data != "error") {
											inp.FlaScriptInterpreterWithArg(file, data);
										} else {
											inp.GetBtwString(read, "while[var(int) -> " + type +
												" <- (==) var(int) -> " + assign + " <-] -> {", "} <-", data);

											if(data != "error")
												inp.FlaScriptInterpreterWithArg(file, data);
											else
												break;
										}
									} else {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										inp.GetBtwString(read, "else -> {", "} <-", read);
										if(read != "error")
											inp.FlaScriptInterpreterWithArg(file, read);
										else 
											break;
									}
								}
							}
						}
					} /* else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					}*/
				} else if(compare == "!=") {
					inp.GetBtwString(assign, "(!=) var(", ") -> ", type2);
					if(type2 == "int") {
						inp.GetBtwString(arg, "(!=) var(int) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(int) -> " + assign + " -> " + type + " <-");
							if(variable != "null" || variable != "error") {
								inp.GetBtwString(variable, "var(int) -> ", " -> ", variable); /* For compare */
								while(1) {
									if(variable != assign) {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										std::string data;
										
										inp.GetBtwString(read, "while[var(int) -> " + type + " <- (!=) var(int) -> " + assign + " <-] -> {",
											"} else -> {", data);
										
										if(data != "error") {
											inp.FlaScriptInterpreterWithArg(file, data);
										} else {
											inp.GetBtwString(read, "while[var(int) -> " + type + " <- (!=) var(int) -> " + assign + " <-] -> {",
											"} <-", data);
											if(data != "error")
												inp.FlaScriptInterpreterWithArg(file, data);
											else
												break; 
										}
									} else {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										inp.GetBtwString(read, "else -> {", "} <-", read);
										
										if(read != "error")
											inp.FlaScriptInterpreterWithArg(file, read);
										else
											break; 
									}
								}
							}
						}
					} /* else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					} */
				} else {}
			}
		} else if(type == "string") {
			inp.GetBtwString(assign, "var(string) -> ", " <- (", type);
			if(type != "error") {
				/* type : variable name */
				inp.GetBtwString(assign, "<- (", ") ", compare);
				if(compare == "==") { /* compare definitions */
					inp.GetBtwString(assign, "(==) var(", ") -> ", type2);
					if(type2 == "string") {
						inp.GetBtwString(arg, "(==) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(string) -> " + assign +
								" -> " + type + " <-");

							if(variable != "null" || variable != "error") {
								inp.GetBtwString(variable, "var(string) -> ", " -> ", variable); /* For compare */
								while(1) {
									if(variable == assign) {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										std::string data;
										inp.GetBtwString(read, "while[var(string) -> " + type + " <- (==) var(string) -> "
											+ assign + " <-] -> {", "} else -> {", data);

										if(data != "error") {
											inp.FlaScriptInterpreterWithArg(file, data);
										} else {
											inp.GetBtwString(read, "while[var(string) -> " + type + " <- (==) var(string) -> " + assign + " <-] -> {",
											"} <-", data);
											if(data != "error")
												inp.FlaScriptInterpreterWithArg(file, data);
											else
												break; 
										}
									} else {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										inp.GetBtwString(read, "else -> {", "} <-", read);
										
										if(read != "error")
											inp.FlaScriptInterpreterWithArg(file, read);
										else
											break;
									}
								}
							}
						}
					} /* else {
						std::cout << type2 << " : This type not integer, unable to compare with type1\n";
					}*/
				} else if(compare == "!=") {
					inp.GetBtwString(assign, "(!=) var(", ") -> ", type2);
					if(type2 == "string") {
						inp.GetBtwString(arg, "(!=) var(string) -> ", " <-] -> {", assign);
						if(assign != "error") {
							std::string variable = stringtools::FindStringWithReturn(file, "var(string) -> " +
								assign + " -> " + type + " <-");

							if(variable != "null" || variable != "error") {
								inp.GetBtwString(variable, "var(string) -> ", " -> ", variable); /* For compare */
								while(1) {
									if(variable != assign) {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										std::string data;
										inp.GetBtwString(read, "while[var(string) -> " + type + " <- (!=) var(string) -> "
											+ assign + " <-] -> {", "} else -> {", data);
										if(data != "error") {
											inp.FlaScriptInterpreterWithArg(file, data);
										} else {
											inp.GetBtwString(read, "while[var(string) -> " + type + " <- (!=) var(string) -> " + assign + " <-] -> {",
												"} <-", data);
											if(data != "error")
												inp.FlaScriptInterpreterWithArg(file, data);
											else
												break;
										}
									} else {
										FFunction fnc;
										std::string read = fnc.FRead(file);
										inp.GetBtwString(read, "else -> {", "} <-", read);
										if(read != "error")
											inp.FlaScriptInterpreterWithArg(file, read);
										else
											break;
									}
								}
							}
						}
					} /* else {
						std::cout << type2 << " : This type not string, unable to compare with type1\n";
					} */
				} else {}
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
							while(1) {
								if(type == assign) {
									FFunction fnc;
									std::string read = fnc.FRead(file);
									std::string data;

									inp.GetBtwString(read, "while[var(system) -> check[" + get_type + "] <- (==) var(string) -> " + assign + " <-] -> {",
										"} else -> {", data);

									if(data != "error") {
										inp.FlaScriptInterpreterWithArg(file, data);
									} else {
										inp.GetBtwString(read, "while[var(system) -> check[" + get_type + "] <- (==) var(string) -> " +
											assign + " <-] -> {", "} <-", data);

										if(data != "error")
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
						}
					} /* TODO: Add error messages. */
				}
			} /* else {
				std::cout << "if : var(...) This type undefined!\n";
			} */
	    	} else if(type == "nil") {
			inp.GetBtwString(assign, "var(nil) -> ", " <- (", type);
			if(type != "error") {
				if(stringtools::GetBetweenString(type, "is_exist[", "]") != "error") {
					inp.GetBtwString(type, "is_exist[", "]", type);
					if(type != "nil") {
						inp.GetBtwString(assign, "<- (", ") ", compare);
						if(compare != "error") {
							inp.GetBtwString(assign, "(" + compare + ") " + "var(", 
								") -> ", type2);

							if(type2 == "bool") {
								inp.GetBtwString(arg, "(" + compare + ") var(bool) -> ",
									" <-] -> {", assign);
								
								if(assign != "error") {
									bool stat;

									if(assign == "true")
										stat = true;
									else if(assign == "false")
										stat = false;

									if(compare == "==") {
										while(1) {
											if(fsplusplus::IsExistFile(type) == stat) {												FFunction fnc;
												std::string read = fnc.FRead(file);
												std::string data;
												inp.GetBtwString(read, "while[var(nil) -> is_exist[" + type + "] <- (==) var(bool) -> " + assign + " <-] -> {",
													"} else -> {", data);
											
												if(data != "error") {
													inp.FlaScriptInterpreterWithArg(file, data);
												} else {
													inp.GetBtwString(read, "while[var(nil) -> is_exist[" + type + "] <- (==) var(bool) -> " +
														assign + " <-] -> {", "} <-", data);
												
													if(data != "error")
														inp.FlaScriptInterpreterWithArg(file, data);
													else
														break; 
												}
											} else {
												FFunction fnc;
												std::string read = fnc.FRead(file);
												inp.GetBtwString(read, "} else -> {", "} <-", read);
											
												if(read != "error")
													inp.FlaScriptInterpreterWithArg(file, read);
												else
													break;
											} 
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}