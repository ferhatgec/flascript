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
#include <Interpreter/Print.hpp>
#include <Interpreter/String.hpp>
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

static int check, intest, load;
static std::string inputted, loadstr, test, alltext, linebyline;
FInterpreter inp;
FFunction func;

void
FPrint::Print(std::string file, std::string arg) {
	Tokenizer token;
	if(inp.FindObject(arg, "print") == true) {
			std::string assign;
			inp.GetBtwString(arg, "(", ")", assign);
			if(assign == "string") {
				inp.GetBtwString(arg, " \"", "\"", assign);
				std::cout << assign;
			} else if(inp.FindObject(assign, "var") == true) {
				inp.GetBtwString(assign, "[", "]", assign);
				if(assign == "int") {
					inp.GetBtwString(arg, " \"", "\"", assign);
					std::cout << atoi(assign.c_str());
				} 
			} else if(assign == "input") {
				std::string input;
				std::cin >> input;
				std::cout << input;
			} else if(assign == "last") {
				std::cout << inputted;
			} else if(inp.FindObject(assign, "get") == true) {
				// print(get[string] -> test ->) ->this
				std::string get;
				inp.GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					inp.GetBtwString(assign, " ->", " ->", get); // var(string) -> test -> abc
					if(get == "error") {
						std::string name;
						inp.GetBtwString(assign,  ": ", " -> ", name); 							
						if(name != "error") {
							inp.Get(file, assign);
						}
					} else {
					// var(string)
					if(inp.ReadFileWithReturn(file, inp.Var + inp.BracketsBegin + inp.Str + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						inp.GetBtwString(test, " -> ", " -> ", test);
						check = 1;
					}
					}
				} else if(get == "int") {
					inp.GetBtwString(assign, " ->", " ->", get);
					if(get == "error") {
						std::string name;
						inp.GetBtwString(assign,  ": ", " -> ", name); 	
						if(name != "error") {
							inp.Get(file, assign);
						}
					} else {
					std::string ret;
					ret = func.FRead(file);
					if(inp.FindObject(ret, inp.Var + inp.BracketsBegin + inp.Int + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 2;
						std::string intest_str;
						inp.GetBtwString(ret, inp.Var + inp.BracketsBegin + inp.Int + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace, " ->", intest_str);
						intest = atoi(intest_str.c_str());
					}
					}
				} else if(get == "string&") {
					inp.GetBtwString(assign, " -> ", " <-", get);
					if(inp.ReadFileWithReturn(file, inp.Var + inp.BracketsBegin + inp.Str + "&" + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 3;
						std::string nil_str;
						inp.GetBtwString(test, " -> ", " <-", nil_str);
					}	
				} else if(get == "int&") {
					inp.GetBtwString(assign, " -> ", " <-", get);
					if(inp.ReadFileWithReturn(file, inp.Var + inp.BracketsBegin + inp.Int + "&" + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 4;
						std::string nil_int;
						inp.GetBtwString(test, " -> ", " <-", nil_int);
					}
				} else if(get == "env") {
					inp.GetBtwString(assign, " -> ", " <-", get);
					check = 5;
					assign = getenv(get.c_str());
					std::cout << assign;
				} 
				inp.GetBtwString(arg, "[t", "s]", assign); 
				if(assign == "hi") {
					if(check == 1) { std::cout << test; } else if(check == 2) { std::cout << intest; } else if(check == 3) { std::cout << "nil"; } else if(check == 4) { std::cout << "0"; }
				} else {
					std::cout << assign;
				}
			} else if(assign == "newline") {
				inp.GetBtwString(arg, " \"", "\"", assign);
				if(assign != "error") {
					std::cout << assign << "\n";
				} else {
					std::cout << "\n";
				}
			} else if(inp.FindObject(assign, "rcolorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				inp.GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						inp.GetBtwString(get, ":", ",", color_type);
					}					
					inp.GetBtwString(get, " ", ":", color);
					inp.GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						inp.GetBtwString(arg, " \"", "\"", assign);
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else {
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
					}
				} else {
					printf("colorized : Brackets error.\n");
				}
			} else if(inp.FindObject(assign, "colorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				inp.GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						inp.GetBtwString(get, ":", ",", color_type);
					}
					inp.GetBtwString(get, " ", ":", color);
					inp.GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						inp.GetBtwString(arg, " \"", "\"", assign);
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else {
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
					}
				} else {
					printf("colorized : Brackets error.\n");
				}
			} else if(assign == "error") {
				inp.GetBtwString(arg, " \"", "\"", assign);
				std::cout << "print : Double quotes missing";
			} else {
				printf("print : Definition Error!\n");
			}
	}
}
