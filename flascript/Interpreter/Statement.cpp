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
#include <Interpreter/Variable.hpp>

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
		if[get(PI) == 3.14159265359] -> {
			print(string) -> "Passed"
		} else -> {
			print(string) -> "Failed"
		} <-
	#pi <-

	main() -> main {
		statement[#pi]
	}
	
	/> Find test </
	var(int) -> echo -> PI <-

	#pi ->
		if[find(var(PI), "echo ")] -> {
			
		} <-
	#pi <-

	main() -> main {
		statement[#pi]
	}
*/

void
FStatement::IfStatement(std::string file, std::string arg) {
	FInterpreter inp;
	FVariable get;
	
	std::string assign, type, compare, type2;

	
	stringtools::GetBtwString(arg, "if[", "] -> {", assign);
	std::string get_if_data;

	if(assign != "error") {
		if(assign.rfind("find", 0) == 0) {
			std::string get_variable = stringtools::GetBetweenString(assign, "var(", "), ");
			
			if(get_variable != "error") {
				std::string get_data = stringtools::GetBetweenString(assign, ", \"", "\")");
				
				std::string variable_data = get.GetVariable(get_variable); 

				if(strstr(variable_data.c_str(), get_data.c_str())) {
					get_if_data = stringtools::GetBetweenString(arg, ")] -> {", 
						"} <-");
						
					if(get_if_data != "error")
                        get_if_data = stringtools::GetBetweenString(arg, ")] -> {", "} else -> {");
                    				
                } else
                    get_if_data = stringtools::GetBetweenString(arg, "} else -> {", "} <-");
			}
            
            inp.FlaScriptInterpreterWithArg(file, get_if_data);
		} else if(assign.rfind("is_exist", 0) == 0) {
			std::string get_variable = stringtools::GetBetweenString(assign, "var(", "))");
			
			if(get_variable != "error") {
				std::string variable_data = get.GetVariable(get_variable); 

				if(fsplusplus::IsExistFile(variable_data) == true) {
					get_if_data = stringtools::GetBetweenString(arg, ")] -> {", 
						"} <-");
						
					if(get_if_data != "error")
                        get_if_data = stringtools::GetBetweenString(arg, ")] -> {", "} else -> {");
                    				
                } else
                    get_if_data = stringtools::GetBetweenString(arg, "} else -> {", "} <-");
			}
            
            inp.FlaScriptInterpreterWithArg(file, get_if_data);
		} else {
			std::string variable_name = stringtools::GetBetweenString(assign, "var(", ") ");
			std::string variable_data = get.GetVariable(variable_name);
				
			if(variable_name != "error") {
				std::string compare_variable_data = stringtools::GetBetweenString(assign, " \"", "\"");

				if(compare_variable_data != "error") {
					std::string operator_type = stringtools::GetBetweenString(assign, "var(" + variable_name + ") ",
						" \"" + compare_variable_data + "\"");
					
					std::string get_if_data = stringtools::GetBetweenString(arg, "\"" + compare_variable_data + "\"] -> {", 
						"} else -> {");


								
					/* Statement has if.. else */
					if(get_if_data != "error") {
						std::string get_else_data = stringtools::GetBetweenString(arg, "} else -> {", "} <-");
					
					
						if(get_else_data != "error") {
							if(operator_type == "==") {
								if(variable_data == compare_variable_data)
									inp.FlaScriptInterpreterWithArg(file, get_if_data);
								else
									inp.FlaScriptInterpreterWithArg(file, get_else_data);
							} else if(operator_type == "!=") {
								if(variable_data != compare_variable_data)
									inp.FlaScriptInterpreterWithArg(file, get_if_data);
								else
									inp.FlaScriptInterpreterWithArg(file, get_else_data);
							}
						}	
					} 
					/* Statement only if */
					else {
						if(operator_type == "==") {
							if(variable_data == compare_variable_data)
								inp.FlaScriptInterpreterWithArg(file, get_if_data);
						} else if(operator_type == "!=") {
							if(variable_data != compare_variable_data)
								inp.FlaScriptInterpreterWithArg(file, get_if_data);
						}
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
	FLoop loop;

	type = fnc.FRead(file);
	inp.GetBtwString(arg, "statement[", "]", assign);
	if(assign != "error") {
		inp.GetBtwString(type, assign + " ->", assign + " <-", assign);
		if(assign != "error") {
			if(strstr(assign.c_str(), "if"))
				IfStatement(file, assign);
			else if(strstr(assign.c_str(), "while"))
				loop.While(file, assign);
		}
	}
}

/*
	exit(type)

	exit(success)
	exit(failure)
*/

void
FStatement::ExitStatement(std::string file, std::string arg) {
	std::string assign, type;
	FInterpreter inp;
	FFunction fnc;
	inp.GetBtwString(arg, "exit(", ")", type);
	if(type == "success" || type == "SUCCESS")
		exit(EXIT_SUCCESS); /* From cstdlib */
	else if(type == "failure" || type == "FAILURE")
		exit(EXIT_FAILURE); /* From cstdlib */
	/* else
		std::cout << "Warning: exit : Undefined type.\n"; */
}
