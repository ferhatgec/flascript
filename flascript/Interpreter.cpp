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

void 
FInterpreter::ReadFileWithReturn(std::string file) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        while (std::getline(readfile, line)) {
        	FlassInterpreter(line);
        }
        readfile.close();
    	} else {
        	printf("Unable to open file\n");
    	}
}

void 
FInterpreter::FlassInterpreter(std::string input) {
	// var[int] -> 100 -> a
	if(FindObject(input, "var") == true) {
		std::string assign;
		GetBtwString(input, "[", "]", assign);
		if(assign == "int") {
			GetBtwString(input, " -> ", " -> ", assign);
			load = atoi(assign.c_str()); 
		} 			
	} 
	
	// func -> test {
	if(FindObject(input, "func") == true) {
		std::string assign;
		GetBtwString(input, " ->", " {", assign);
	}
	
	// print(var[int]) -> " "
	if(FindObject(input, "print") == true) {
		std::string assign;
		GetBtwString(input, "(", ")", assign);
		if(assign == "string") {
			GetBtwString(input, " \"", "\"", assign);
			std::cout << assign;
		} else if(FindObject(assign, "var") == true) {
			GetBtwString(assign, "[", "]", assign);
			if(assign == "int") {
				GetBtwString(input, " \"", "\"", assign);
				std::cout << atoi(assign.c_str());
			} 
		} 
	}
	
	// exec(system ->scrift ->[->arg])
	if(FindObject(input, "exec") == true) {
		std::string assign;
		GetBtwString(input, "(", ")", assign);
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


