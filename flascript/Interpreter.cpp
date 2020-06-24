#include <iostream>
#include "../include/Interpreter.hpp"
#include "../Library/FileSystemPlusPlus.h"
#include <fstream>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

FInterpreter::FInterpreter() { }
FInterpreter::~FInterpreter() { }

int load;
std::string loadstr;
std::string test;

// Get Between String    
void GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {  
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

void 
FInterpreter::FlaScriptInterpreter(std::string file) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
		// var[int] -> 100 -> a
		if(FindObject(line, "var") == true) {
			std::string assign;
			GetBtwString(line, "[", "]", assign);
			if(assign == "int") {
				GetBtwString(line, " -> ", " <-", assign);
				load = atoi(assign.c_str());
			} else if(assign == "string") {
				// var(string) -> test -> abc
				GetBtwString(line, " -> ", " <-", assign);
				loadstr = assign;
			} 			
		} 
	
		// func -> test {
		if(FindObject(line, "func") == true) {
			std::string assign;
			GetBtwString(line, " ->", " {", assign);
		}
	
		// print(var[int]) -> " "
		if(FindObject(line, "print") == true) {
			std::string assign;
			GetBtwString(line, "(", ")", assign);
			if(assign == "string") {
				GetBtwString(line, " \"", "\"", assign);
				std::cout << assign;
			} else if(FindObject(assign, "var") == true) {
				GetBtwString(assign, "[", "]", assign);
				if(assign == "int") {
					GetBtwString(line, " \"", "\"", assign);
					std::cout << atoi(assign.c_str());
				} 
			} else if(FindObject(assign, "get") == true) {
				// print(get[string] -> test ->) ->this
				std::string get;
				GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					GetBtwString(assign, " ->", " ->", get); // var(string) -> test -> abc
					// var(string)
					if(ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						GetBtwString(test, " -> ", " -> ", test);
					}
				}
				
				GetBtwString(line, "[t", "s]", assign); 
				if(assign == "hi") {
					std::cout << test;
				} else {
					std::cout << assign;
				}
			} else if(assign == "error") {
				GetBtwString(line, " \"", "\"", assign);
				std::cout << assign;
			} else {
				printf("FlaScript Definition Error!\n");
			}
		}
	
		// exec(system ->scrift ->[->arg])
		if(FindObject(line, "exec") == true) {
			std::string assign;
			GetBtwString(line, "(", ")", assign);
			if(FindObject(assign, "system") == true) {
					GetBtwString(assign, " ->", " ->", assign);
					if(assign != "error") {
						system(assign.c_str());
					} else {
						printf("FlaScript Arrow Error!\n");
					}
			}
		}	
	}
	} else {
		printf("Unable to open file\n");
	}
}


