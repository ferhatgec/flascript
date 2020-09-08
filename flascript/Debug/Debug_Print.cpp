/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <Tokenizer.hpp>

#include <Debug/Debug_Interpreter.hpp>
#include <Debug/Debug_Print.hpp>
#include <Debug/Debug_String.hpp>
#include <Debug/Debug_Function.hpp>

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

static int check, intest, load;
static std::string inputted, loadstr, test, alltext, linebyline;
static Debug_FInterpreter inp;
static Debug_FFunction func;

static int fprintf(const char *format, ...);

static void SetTitle(std::string title);


/*
	Standart:
		print(string) -> Hello World! <-

	C-Like:
		fprintf(<%string>[:"Hello ":, :"World!":])
		fprintln(<%string>[:"Hello ":, :"World!":])
			: print(string) -> Hello  <-
			: print(string) -> World! <-
			: print(newline)
*/
void
Debug_FPrint::Debug_Print(std::string file, std::string arg) {
  Tokenizer token;
  Debug_FFunction fnc;
  if(inp.Debug_FindObject(arg, "fprintf") == true || inp.Debug_FindObject(arg, "fprintln") == true) { // fprintf(<%string>[:"test":, :"hello":])
	 std::string assign, type;
	 inp.Debug_GetBtwString(arg, "(<%", ">[", type);
	 if(type == "string") {
		 inp.Debug_GetBtwString(arg, ">[", "])", type);
		 if(type != "error") {
			 inp.Debug_GetBtwString(type, ":\"", "\":, ", assign);
			 if(assign != "error") {
				 std::string data;
				 data.append(assign);
				 for(;;) {
				 	inp.Debug_GetBtwString(type, ", :\"", "\":", assign);
				   	if(assign != "error") {
						data.append(assign);
						type = inp.Debug_EraseAllSubString(type, ", :\"" + assign + "\":");
				   	} else
						break;
				 }
				 /*
				 	fprintln = fprintf ... + newline
				 */
			 } else {
			 	inp.Debug_GetBtwString(type, ":\"", "\":", assign);
			 	if(assign == "error") {
					BOLD_LIGHT_WHITE_COLOR
 					std::cout << file + ":" << WBOLD_RED_COLOR << " Error: " << WBOLD_LIGHT_WHITE_COLOR <<
 						"print(string) : Double quotes parse error. Add \"....\"\n";
			 }
		}
	 	} else {
			BOLD_LIGHT_WHITE_COLOR
			std::cout << file + ":" << WBOLD_RED_COLOR << " Error: " << WBOLD_LIGHT_WHITE_COLOR <<
				"fprint(f|ln)(<%string>[]) : Data parse error.\n";
	 	}
	 }
 } else if(inp.Debug_FindObject(arg, "print") == true) {
			std::string assign;
			inp.Debug_GetBtwString(arg, "(", ")", assign);
			if(assign == "string") {
				inp.Debug_GetBtwString(arg, " \"", "\"", assign);
				if(assign == "error") {
					BOLD_LIGHT_WHITE_COLOR
					std::cout << file + ":" << WBOLD_RED_COLOR << " Error: " << WBOLD_LIGHT_WHITE_COLOR <<
						"print(string) : Double quotes parse error. Add \"....\"\n";
				}
			} else if(inp.Debug_FindObject(assign, "var") == true) {
				inp.Debug_GetBtwString(assign, "[", "]", assign);
				if(assign == "int") {
					inp.Debug_GetBtwString(arg, " -> ", " <-", assign);
				}
			} else if(assign == "input") {
			} else if(assign == "last") {
			} else if(assign == "func") {
				inp.Debug_GetBtwString(arg, "-> ", " <-", assign);
				if(assign != "error") {
					std::string fn = fnc.Debug_FRead(file);
					inp.Debug_GetBtwString(fn, "func -> " + assign + " {", "}", assign);
					if(assign != "error") {
						if(inp.Debug_FindObject(assign, "return") == true) {
							// var(int) -> 12 <-
							inp.Debug_GetBtwString(assign, "var(", ")", fn);
							if(fn != "error") {
								if(fn == "int") {
									inp.Debug_GetBtwString(assign, " -> ", " <-", fn);
									if(fn != "error") {}
								} else if(fn == "string") {
									inp.Debug_GetBtwString(assign, " -> ", " <-", fn);
									if(fn != "error") {}
								} else if(fn == "int&") {
								} else if(fn == "string&") {
									std::cout << "null";
								} else {
									BOLD_LIGHT_WHITE_COLOR
									std::cout << file + ":" << WBOLD_LIGHT_RED_COLOR << " Warning: " << WBOLD_LIGHT_WHITE_COLOR <<
										"var(" + fn + ") : Variable not defined.\n";
								}
							} else {
								// return get[int] -> abc <-
								inp.Debug_GetBtwString(assign, "get[", "]", fn);
								if(fn != "error") {

								}
							}
						}
					} else {
						BOLD_LIGHT_WHITE_COLOR
						std::cout << file + ":" << WBOLD_RED_COLOR << " Error: " << WBOLD_LIGHT_WHITE_COLOR <<
							"func -> " + assign + " {..} : Curly brackets parse error.\n";
					}
				}
			} else if(assign == "dynamic") {
				/*
					print(dynamic) -> set[title] -> "Hello world!" <-
				*/
				std::string type;
				inp.Debug_GetBtwString(arg, "set[", "]", type);
				if(type == "title") {
					inp.Debug_GetBtwString(arg, "\"", "\"", type);
					if(type == "error") {
						BOLD_LIGHT_WHITE_COLOR
						std::cout << file + ":" << WBOLD_RED_COLOR << " Error: " << WBOLD_LIGHT_WHITE_COLOR <<
							"print(dynamic) : Parse error.\n";
					}
				} else {
					std::cout << "Error: " + type + "  : Undefined type.\n";
				}
			} else if(inp.Debug_FindObject(assign, "get") == true) {
				// print(get[string] -> test ->) ->this
				std::string get;
				inp.Debug_GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					inp.Debug_GetBtwString(assign, " -> ", " <-", get); // var(string) -> test -> abc
					if(get == "error") {
						std::string name;
						inp.Debug_GetBtwString(assign,  ": ", " -> ", name);
						if(name != "error") {
							inp.Debug_Get(file, assign);
						}
					} else {
					// var(string)
					std::string rt;
					rt = func.Debug_FRead(file);
					inp.Debug_GetBtwString(rt, inp.Var + inp.BracketsBegin + inp.Str + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace, " -> ", test);
					if(test != "error") {
							inp.Debug_GetBtwString(rt,  inp.Var + inp.BracketsBegin + inp.Str + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace, " -> ", rt);
							if(rt != "error") {
								inp.Debug_GetBtwString(rt, " -> ", " <-", rt);
								if(rt == get) {}
							}
					}
				}
					check = 1;
				} else if(get == "int") {
					inp.Debug_GetBtwString(assign, " -> ", " ->", get);
					if(get == "error") {
						std::string name;
						inp.Debug_GetBtwString(assign,  ": ", " -> ", name);
						if(name != "error") {
							inp.Debug_Get(file, assign);
						}
					} else {
					std::string ret;
					ret = func.Debug_FRead(file);
					if(inp.Debug_FindObject(ret, inp.Var + inp.BracketsBegin + inp.Int + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 2;
						std::string intest_str;
						inp.Debug_GetBtwString(ret, inp.Var + inp.BracketsBegin + inp.Int + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace, " ->", intest_str);
						intest = atoi(intest_str.c_str());
					}
					}
				} else if(get == "string&") {
					inp.Debug_GetBtwString(assign, " -> ", " <-", get);
					if(inp.Debug_ReadFileWithReturn(file, inp.Var + inp.BracketsBegin + inp.Str + "&" + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 3;
						std::string nil_str;
						inp.Debug_GetBtwString(test, " -> ", " <-", nil_str);
					}
				} else if(get == "int&") {
					inp.Debug_GetBtwString(assign, " -> ", " <-", get);
					if(inp.Debug_ReadFileWithReturn(file, inp.Var + inp.BracketsBegin + inp.Int + "&" + inp.BracketsEnd + inp.Whitespace + inp.ArrowKey + inp.Whitespace) == true) {
						check = 4;
						std::string nil_int;
						inp.Debug_GetBtwString(test, " -> ", " <-", nil_int);
					}
				} else if(get == "env") {
					inp.Debug_GetBtwString(assign, " -> ", " <-", get);
					check = 5;
					assign = getenv(get.c_str());
				}
				inp.Debug_GetBtwString(arg, "[t", "s]", assign);
				if(assign == "hi") {}
			} else if(assign == "newline") {
				inp.Debug_GetBtwString(arg, " \"", "\"", assign);
				if(assign != "error") {
				} else {}
			} else if(inp.Debug_FindObject(assign, "rcolorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				inp.Debug_GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						inp.Debug_GetBtwString(get, ":", ",", color_type);
					}
					inp.Debug_GetBtwString(get, " ", ":", color);
					inp.Debug_GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						inp.Debug_GetBtwString(arg, " \"", "\"", assign);
					} else {}
				} else {
					std::cout << "colorized : Brackets error.\n";
				}
			} else if(inp.Debug_FindObject(assign, "colorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				inp.Debug_GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						inp.Debug_GetBtwString(get, ":", ",", color_type);
					}
					inp.Debug_GetBtwString(get, " ", ":", color);
					inp.Debug_GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						inp.Debug_GetBtwString(arg, " \"", "\"", assign);
					} else {

					}
				} else {
					std::cout << "Error: colorized : Brackets error.\n";
				}
			} else if(assign == "error") {
				inp.Debug_GetBtwString(arg, " \"", "\"", assign);
				std::cout << "Error: print : Double quotes missing\n";
			} else {
				std::cout << "Error: print : Definition Error!\n";
			}
	}
}

/*
	Implementation of GNU LibC Printf
*/
static int fprintf(const char *format, ...) {
  va_list arg;
  int done;

  va_start (arg, format);
  done = vfprintf (stdout, format, arg);
  va_end (arg);
  return done;
}

/*
	Terminal title
*/

static void SetTitle(std::string title) {}
