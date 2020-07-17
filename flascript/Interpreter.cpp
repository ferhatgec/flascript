/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/Tokenizer.hpp"
#include "../include/Interpreter.hpp"

// Libraries
#include "../Library/FileSystemPlusPlus.h"
#include "../Library/Colorized.hpp"
#include "../Library/SystemInfo.hpp"

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

FInterpreter::FInterpreter() { }
FInterpreter::~FInterpreter() { }

int pr_check;
int check;
int intest;
int load;
std::string inp;
std::string loadstr;
std::string test;
std::string alltext;
std::string linebyline;

int random(int min_num, int max_num) {
    int result=0,low_num=0,hi_num=0;
     if(min_num<max_num) {
         low_num=min_num;
         hi_num=max_num+1; // this is done to include max_num in output.
     } else{
         low_num=max_num+1;// this is done to include max_num in output.
         hi_num=min_num;
     }
     srand(time(NULL));
     result = (rand()%(hi_num-low_num-low_num))+low_num; // Unsecure.
     return result;
}

// Get Between String    
void 
FInterpreter::GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {  
    int start = oStr.find(sStr1);   
    if (start >= 0) {       
      std::string tstr = oStr.substr(start + sStr1.length());        
      int stop = tstr.find(sStr2);      
      if (stop >1)          
        rStr = oStr.substr(start + sStr1.length(), stop);
      else
        rStr ="error";  
    }
    else
       rStr = "error"; 
}    

std::string 
FInterpreter::EraseAllSubString(std::string & mainString, const std::string & erase) {
    size_t pos = std::string::npos;
    while((pos = mainString.find(erase)) != std::string::npos) {
        mainString.erase(pos, erase.length());
    }
    return mainString;
} 

bool
FInterpreter::FindObject(std::string object, std::string find) {
	if(object.find(find) == 0) {
		return true;
	} else {
		return false;
	}
}


bool
FInterpreter::ReadFileWithReturn(std::string file, std::string argument) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	if(FindObject(line, argument) == true) {
        		test = line;
        		return true;
        	}
        }
        readfile.close();
    	} else {
        	printf("Unable to open file\n");
    	}
}


bool
FInterpreter::FCommentLine(std::string file, std::string argument) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	test.append(line);
        	if(FindObject(line, argument) == true) {
        		return true;
        	}
        }
        readfile.close();
    	} else {
        	printf("Unable to open file\n");
    	}
}

void
FInterpreter::Read(std::string file) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	alltext.append(line + "\n");
        }
        readfile.close();
    	} else {
        	printf("Unable to open file\n");
    	}
}

void 
FInterpreter::Get(std::string file, std::string arg) {
	if(FindObject(arg, "get") == true) {
		std::string assign;
		std::string name;
		std::string type;
		GetBtwString(arg, "[", "]", type);
		GetBtwString(arg, ": ", " -> ", name); // Variable name
		GetBtwString(arg, " \"", "\"", assign); // Variable header
		if(ReadFileWithReturn(assign, "var[" + type + "]: ") == true) {
			std::string comp;
			GetBtwString(test, " -> ", " <-", comp);
			if(comp == name) {
				std::string text;
				GetBtwString(test, ": ", " -> ", text);
				if(pr_check == 1)  { // print
					if(type == "string") {
						std::cout << text;
					} else if(type == "int") {
						std::cout << atoi(text.c_str());
					}
					pr_check = 0;
				}  else {
				}
			} 
		}
	}
}


void
FInterpreter::Print(std::string file, std::string arg) {
	Tokenizer token;
	if(FindObject(arg, "print") == true) {
			std::string assign;
			GetBtwString(arg, "(", ")", assign);
			if(assign == "string") {
				GetBtwString(arg, " \"", "\"", assign);
				std::cout << assign;
			} else if(FindObject(assign, "var") == true) {
				GetBtwString(assign, "[", "]", assign);
				if(assign == "int") {
					GetBtwString(arg, " \"", "\"", assign);
					std::cout << atoi(assign.c_str());
				} 
			} else if(assign == "input") {
				std::string input;
				std::cin >> input;
				std::cout << input;
			} else if(assign == "last") {
				std::cout << inp;
			} else if(FindObject(assign, "get") == true) {
				// print(get[string] -> test ->) ->this
				std::string get;
				GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					GetBtwString(assign, " ->", " ->", get); // var(string) -> test -> abc
					if(get == "error") {
						std::string name;
						GetBtwString(assign,  ": ", " -> ", name); 	
						if(name != "error") {
							pr_check = 1;
							Get(file, assign);
						}
					} else {
					// var(string)
					if(ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						GetBtwString(test, " -> ", " -> ", test);
						check = 1;
					}
					}
				} else if(get == "int") {
					GetBtwString(assign, " ->", " ->", get);
					if(get == "error") {
						std::string name;
						GetBtwString(assign,  ": ", " -> ", name); 	
						if(name != "error") {
							pr_check = 1;
							Get(file, assign);
						}
					} else {
					if(ReadFileWithReturn(file, Var + BracketsBegin + Int + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						check = 2;
						std::string intest_str;
						GetBtwString(test, " -> ", " ->", intest_str);
						intest = atoi(intest_str.c_str());
					}
					}
				} else if(get == "string&") {
					GetBtwString(assign, " -> ", " <-", get);
					if(ReadFileWithReturn(file, Var + BracketsBegin + Str + "&" + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						check = 3;
						std::string nil_str;
						GetBtwString(test, " -> ", " <-", nil_str);
					}	
				} else if(get == "int&") {
					GetBtwString(assign, " -> ", " <-", get);
					if(ReadFileWithReturn(file, Var + BracketsBegin + Int + "&" + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						check = 4;
						std::string nil_int;
						GetBtwString(test, " -> ", " <-", nil_int);
					}
				} 
				GetBtwString(arg, "[t", "s]", assign); 
				if(assign == "hi") {
					if(check == 1) { std::cout << test; } else if(check == 2) { std::cout << intest; } else if(check == 3) { std::cout << "nil"; } else if(check == 4) { std::cout << "0"; }
				} else {
					std::cout << assign;
				}
			} else if(assign == "newline") {
				GetBtwString(arg, " \"", "\"", assign);
				if(assign != "error") {
					std::cout << assign << "\n";
				} else {
					std::cout << "\n";
				}
			} else if(FindObject(assign, "rcolorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					GetBtwString(get, ":", ",", color_type);
					GetBtwString(get, " ", ":", color);
					GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						GetBtwString(arg, " \"", "\"", assign);
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else {
						colorized::PrintWhReset(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
					}
				} else {
					printf("colorized : Brackets error.\n");
				}
			} else if(FindObject(assign, "colorized") == true) {
				// print(colorized[:1, 32:]) -> "Hello FlaScript!"
				std::string get, color_type, color;
				GetBtwString(assign, "[", "]", get);
				if(get != "error") {
					GetBtwString(get, ":", ",", color_type);
					GetBtwString(get, " ", ":", color);
					GetBtwString(arg, " \"", "\" <-", assign);
					if(assign == "error") {
						GetBtwString(arg, " \"", "\"", assign);
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), "");
					} else {
						colorized::PrintWith(colorized::Colorize(atoi(color_type.c_str()), atoi(color.c_str())).c_str(), assign.c_str());
					}
				} else {
					printf("colorized : Brackets error.\n");
				}
			} else if(assign == "error") {
				GetBtwString(arg, " \"", "\"", assign);
				std::cout << "print : Double quotes missing";
			} else {
				printf("print : Definition Error!\n");
			}
	}
}

std::string
FInterpreter::FlaScriptImporter(std::string file, std::string get) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    		while(std::getline(readfile, line)) {
    			if(FindObject(line, get) == true) {
        			return line;
        		}
    		}
    	}
}

void 
FInterpreter::FlaScriptInterpreter(std::string file) {
	Tokenizer token;
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	Read(file);
        	// Single Comment Line
        	if(FindObject(line, token.SingleCommentLine) == true) {
        		line.erase();
        	}
        	
        	// Single Comment Line
        	if(FindObject(line, token.CommentLineBegin) == true) {
			std::string assign;
			GetBtwString(line, token.CommentLineBegin, token.CommentLineEnd, assign);
			if(assign != "error") {
				 line = EraseAllSubString(line, token.CommentLineBegin + assign + token.CommentLineEnd);
			} else {
				if(FCommentLine(file, "</") == true) {
				} else {
					printf("token.CommentLine Error\n");
				}
			}	       	
        	}
        	        	
		// var[int] -> 100 -> a
		if(FindObject(line, "var") == true) {
			std::string assign;
			GetBtwString(line, "[", "]", assign);
			if(assign == "int") {
				GetBtwString(line, " -> ", " <-", assign);
				load = atoi(assign.c_str());
			} else if(assign == "int&") {
				// var(int&) -> Argc <-
				GetBtwString(line, " -> ", " <-", assign);
				load = NULL;
			} else if(assign == "string") {
				// var(string) -> test -> abc
				GetBtwString(line, " -> ", " <-", assign);
				loadstr = assign;
			} else if(assign == "string&") {
				GetBtwString(line, " -> ", " <-", assign);
				loadstr = assign;
			}		
		} 
		
		// import " " -> name <- 
		if(FindObject(line, "import") == true) {
			std::string assign;
			GetBtwString(line, " \"", "\"", assign);
		}
		
		// func() -> test {
		if(FindObject(line, "func()") == true) {
			std::string assign;
			GetBtwString(line, "func() -> ", " {", assign);
			// Assign = Function name 
			GetBtwString(alltext, "func() -> " + assign + " {", "}", alltext);
			//Print(file, alltext);
		}
		
        	if(FindObject(line, "main() -> main {") == true) {
        		Read(file);
        		GetBtwString(alltext, "main() -> main {", "}", alltext);
        		std::istringstream f(alltext);
        		while(std::getline(f, linebyline)) {
        		// print(var[int]) -> " "
			if(FindObject(linebyline, "print") == true) {
				Print(file, linebyline);
			} 

			// read(string&) -> type[cpu]
			if(FindObject(linebyline, "read") == true) {
				std::string assign;
				GetBtwString(linebyline, "(", ")", assign);
				
				if(assign != "error" && assign == "string&") {
					GetBtwString(linebyline, "type[", "]", assign);
					if(assign != "error") {
						systemInfo info;
						if(assign == "cpu") {
							fsplusplus::ReadCPU();
						} else if(assign == "osname") {
							std::cout << fsplusplus::ReadOSName();
						} else if(assign == "uptime") {
							std::cout << info.getUptime();
						} else if(assign == "arch") {
							std::cout << info.getArch();
						} else if(assign == "username") {
							std::cout << info.getUsername();
						} else if(assign == "hostname") {
							std::cout << info.getHostname();
						} else if(assign == "shell") {
							std::cout << info.getShell();
						} else if(assign == "kernelname") {
							std::cout << info.getSystem();
						} else if(assign == "kernelrelease") {
							std::cout << info.getKernel();
						} else if(assign == "terminal") {
							std::cout << info.getTerm();
						}
					} 
				}
			}
		
			// var(string&) -> Hello -> Hello <-
			// input(get[string] ->  ->) [this]
			if(FindObject(linebyline, "input") == true) {
				std::string assign;
				GetBtwString(linebyline, "(", ")", assign);
				if(FindObject(assign, "get") == true) {
					std::string get;
					GetBtwString(assign, "[", "]", get); 
					if(get == "string") {
						std::cin >> inp;
						GetBtwString(linebyline, " -> ", " ->", assign);
						if(ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
							test = Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace + inp + Whitespace + ArrowKey + Whitespace + assign + Whitespace + LeftArrowKey;
						}			 
					} 
				} else if(assign == "string") {
					std::cin >> inp;
				}
			}
			// get[string]: Hello -> "test.flsh"
			if(FindObject(linebyline, "get") == true) {
				Get(file, linebyline);
			}

			// random(:1, 12:) -> print
			if(FindObject(linebyline, "random") == true) {
				std::string assign;
				std::string first, second;
				GetBtwString(linebyline, "(", ")", assign);
				if(assign == "error") {
					printf("main() : random : brackets error. random(:, :)\n");
				}
				GetBtwString(assign, ":", ", ", first);
				if(first == "error") {
					srand(time(NULL));
					int number = atoi(assign.c_str());
					std::cout << random(0, number);	
				} else {
					GetBtwString(assign, ", ", " :", second);
					if(second == "error") {
						printf("main() : random : second number is not defined. random(..., 2:)\n"); 
					}
					int first_number = atoi(first.c_str());
					int second_number = atoi(second.c_str());
					srand(time(NULL));
					std::cout << random(first_number, second_number);
				}
				
			}
						
			// exec(system -> scrift ->[->arg])
			if(FindObject(linebyline, "exec") == true) {
				std::string assign;
				GetBtwString(linebyline, "(", ")", assign);
				if(FindObject(assign, "system") == true) {
						GetBtwString(assign, " -> ", " ->", assign);
						if(assign != "error") {
							system(assign.c_str());
						} else {
							printf("exec(system) : Arrow Error!\n");
						}
				}	
        		} 
        		}
        	}
	}
	} else {
		printf("Unable to open file\n");
	}
}
