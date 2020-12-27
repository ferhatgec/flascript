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
#include <Interpreter/Interpreter.hpp>
#include <Interpreter/Print.hpp>
#include <Interpreter/String.hpp>
#include <Interpreter/Function.hpp>
#include <Interpreter/Variable.hpp>
#include <Interpreter/Tools.hpp>

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

				
int fprintf(const char *format, ...);

void SetTitle(std::string title);


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

/* TODO:
	- Rewrite Print function
*/
void
FPrint::Print(std::string file, std::string arg) {
  	Tokenizer token;
	FInterpreter inp;
	FFunction func;
	FVariable var;
	FTools    seq;
	
  	if(inp.FindObject(arg, "fprintf") == true || inp.FindObject(arg, "fprintln") == true) { // fprintf(<%string>[:"test":, :"hello":])
		std::string assign, type;
	 	stringtools::GetBtwString(arg, "(<%", ">[", type);
	
	 	if(type == "string") {
			stringtools::GetBtwString(arg, ">[", "])", type);
		 
		 	if(type != "error") {
			 	stringtools::GetBtwString(type, ":\"", "\":, ", assign);
			 
			 if(assign != "error") {
				 std::string data;
				 data.append(assign);
				 
				 for(;;) {
					 stringtools::GetBtwString(type, ", :\"", "\":", assign);
				   if(assign != "error") {
					  	data.append(assign);
						
						type = stringtools::EraseAllSubString(type, ", :\"" + assign + "\":");
				   } else
					break;
				 }
				 fprintf(data.c_str());
				 /*
				 	fprintln = fprintf ... + newline
				 */
				 if(inp.FindObject(arg, "fprintln") == true) std::cout << "\n";
			 } else {
				 stringtools::GetBtwString(type, ":\"", "\":", assign);
				 if(assign != "error")
					 fprintf(assign.c_str());
				 /* } else {
					 std::cout << arg << "\n              ^^^^ : Double quotes missing\n";
				 } */
			 }
		 } else {
			 std::cout << arg;
			 std::cout << "\n                   ^^^^\n";
		 }
	 }
 	} else if(inp.FindObject(arg, "print") == true) {
			std::string assign;
			stringtools::GetBtwString(arg, "(", ")", assign);
			
			if(assign[0] == '"' || assign == "string" || assign == "untyp") {

			    if(assign == "string") {
                    stringtools::GetBtwString(arg, "\"", "\"", assign);
			        assign = seq.EscapeSeq(assign);
                } else if(assign == "untyp") {
                    stringtools::GetBtwString(arg, "\"", "\"", assign);
                    assign = seq.StandardSeq(assign);
                } else {
                    stringtools::GetBtwString(assign, "\"", "\"", assign);
                    assign = seq.EscapeSeq(assign);
                }

				if(assign != "error") std::cout << assign;
			} else if(inp.FindObject(assign, "var") == true) {
				stringtools::GetBtwString(assign, "[", "]", assign);
				
				if(assign == "int") {
					stringtools::GetBtwString(arg, " -> ", " <-", assign);
					std::cout << atoi(assign.c_str());
				}
			} else if(assign == "input") {
				std::string input;
				std::cin >> input;
				
				std::cout << input;
			} else if(assign == "last") {
				std::cout << inputted;
			} else if(assign == "func") {
				stringtools::GetBtwString(arg, "-> ", " <-", assign);
				
				if(assign != "error") {
					std::string fn = func.FRead(file);
					stringtools::GetBtwString(fn, "func -> " + assign + " {", "}", assign);
					
					if(assign != "error") {
						if(inp.FindObject(assign, "return") == true) {
							// var(int) -> 12 <-
							stringtools::GetBtwString(assign, "var(", ")", fn);
							if(fn != "error") {
								if(fn == "int") {
									stringtools::GetBtwString(assign, " -> ", " <-", fn);
									if(fn != "error") std::cout << atoi(fn.c_str());
								} else if(fn == "string") {
									stringtools::GetBtwString(assign, " -> ", " <-", fn);
									
									if(fn != "error") std::cout << fn;
								} else if(fn == "int&") {
									std::cout << 0;
								} else if(fn == "string&") {
									std::cout << "null";
								} /* else {
									std::cout << "var(" + fn + ") This variable not defined:" << fn << "\n";
								} */
							} else {
								// return get[int] -> abc <-
								stringtools::GetBtwString(assign, "get[", "]", fn);
								if(fn != "error") {

								}
							}
						}
					}
				}
			} else if(assign == "dynamic") {
				/*
					print(dynamic) -> set[title] -> "Hello world!" <-
				*/
				std::string type;
				stringtools::GetBtwString(arg, "set[", "]", type);
				
				if(type == "title") {
					stringtools::GetBtwString(arg, "\"", "\"", type);
					
					if(type != "error")
						SetTitle(type);
					else {
                        type = stringtools::GetBetweenString(arg, "var(", ")");
					    if(type != "error") {
                            type = var.GetVariable(type);
                            SetTitle(type);                        
                        }
                            
                    }
				} /*else {
					std::cout << type << "  : Not defined type.\n";
				}*/
			} else if(inp.FindObject(assign, "get") == true) {
				// print(get[string] -> test ->) ->this
				std::string get;
				stringtools::GetBtwString(assign, "[", "]", get);
				
				if(get == "string") {
					stringtools::GetBtwString(assign, " -> ", " <-", get); // var(string) -> test -> abc
					
					if(get == "error") {
						std::string name;
						stringtools::GetBtwString(assign,  ": ", " -> ", name);
						
						if(name != "error")
							inp.Get(file, assign);
					} else {
						// var(string)
						std::string rt;
						rt = func.FRead(file);
						stringtools::GetBtwString(rt, token.Var + token.BracketsBegin + token.Str + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace, " -> ", test);
					if(test != "error") {
							stringtools::GetBtwString(rt,  token.Var + token.BracketsBegin + token.Str + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace, " -> ", rt);
							if(rt != "error") {
								stringtools::GetBtwString(rt, " -> ", " <-", rt);
								if(rt == get) std::cout << test;
							}
					}
				}
					check = 1;
				} else if(get == "int") {
					stringtools::GetBtwString(assign, " -> ", " ->", get);
					
					if(get == "error") {
						std::string name;
						stringtools::GetBtwString(assign,  ": ", " -> ", name);
						
						if(name != "error") {
							inp.Get(file, assign);
						}
					} else {
						std::string ret;
						ret = func.FRead(file);
					
						if(inp.FindObject(ret, token.Var + token.BracketsBegin + token.Int + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace) == true) {
						check = 2;
						std::string intest_str;
						
						stringtools::GetBtwString(ret, token.Var + token.BracketsBegin + token.Int + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace, " ->", intest_str);
						intest = atoi(intest_str.c_str());
					}
					}
				} else if(get == "string&") {
					stringtools::GetBtwString(assign, " -> ", " <-", get);
					
					if(inp.ReadFileWithReturn(file, token.Var + token.BracketsBegin + token.Str + "&" + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace) == true) {
						check = 3;
						std::string nil_str;
					
						stringtools::GetBtwString(test, " -> ", " <-", nil_str);
					}
				} else if(get == "int&") {
					stringtools::GetBtwString(assign, " -> ", " <-", get);
					
					if(inp.ReadFileWithReturn(file, token.Var + token.BracketsBegin + token.Int + "&" + token.BracketsEnd + token.Whitespace + token.ArrowKey + token.Whitespace) == true) {
						check = 4;
						std::string nil_int;
					
						stringtools::GetBtwString(test, " -> ", " <-", nil_int);
					}
				} else if(get == "env") {
					stringtools::GetBtwString(assign, " -> ", " <-", get);
					check = 5;
					
					assign = getenv(get.c_str());
					std::cout << assign;
				}
				
				stringtools::GetBtwString(arg, "[t", "s]", assign);
				
				if(assign == "hi") {
					if(check == 1) { std::cout << test; } else if(check == 2) { std::cout << intest; } else if(check == 3) { std::cout << "nil"; } else if(check == 4) { std::cout << "0"; }
				} else {
					std::cout << assign;
				}
			} else if(assign == "newline") {
				stringtools::GetBtwString(arg, " \"", "\"", assign);
				
				if(assign != "error") {
					assign = seq.EscapeSeq(assign);
					
					std::cout << assign << "\n";
				} else
					std::cout << "\n";
			} else if(inp.FindObject(assign, "rcolorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				stringtools::GetBtwString(assign, "[", "]", get);
				
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						stringtools::GetBtwString(get, ":", ",", color_type);
					}
					
					stringtools::GetBtwString(get, " ", ":", color);
					stringtools::GetBtwString(arg, " \"", "\" <-", assign);
					
					assign = seq.EscapeSeq(assign);
					
					if(assign == "error") {
						stringtools::GetBtwString(arg, " \"", "\"", assign);
			
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
				} /*else {
					std::cout << "colorized : Brackets error.\n";
				}*/
			} else if(inp.FindObject(assign, "colorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				stringtools::GetBtwString(assign, "[", "]", get);
				
				if(get != "error") {
					if(strstr(get.c_str(), ":1,")) {
						color_type = 1;
					} else {
						stringtools::GetBtwString(get, ":", ",", color_type);
					}
					
					stringtools::GetBtwString(get, " ", ":", color);
					stringtools::GetBtwString(arg, " \"", "\" <-", assign);
					
					assign = seq.EscapeSeq(assign);
					
					if(assign == "error") {
						stringtools::GetBtwString(arg, " \"", "\"", assign);
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
				}
			} else if(assign == "spec") {
				stringtools::GetBtwString(arg, "(spec) -> ", " <-", assign);
				
				if(assign != "error") {
					const auto &t = var_.find(assign);
					if (t != var_.end()) // Found
						std::cout << t->second;
				}
			} else {
			    /* error, undefined type */
			}
 	}
}

/*
	Implementation of GNU LibC Printf
*/
int fprintf(const char *format, ...) {
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

void SetTitle(std::string title) {
	std::cout << "\e]2; " + title + " \a";
}
