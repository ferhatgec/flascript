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
#include <Debug/Debug_Print.hpp>
#include <Debug/Debug_Exec.hpp>
#include <Debug/Debug_String.hpp>
#include <Debug/Debug_Function.hpp>
#include <Debug/Debug_Definitions.hpp>
#include <Debug/Debug_Import.hpp>
#include <Debug/Debug_Statement.hpp>

/* Libraries */
#include <FileSystemPlusPlus.h>
#include <Colorized.hpp>
#include <SystemInfo.hpp>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

Debug_FInterpreter::Debug_FInterpreter() { }
Debug_FInterpreter::~Debug_FInterpreter() { }

static std::string inp, test, alltext, linebyline;

static int random(int min_num, int max_num) {
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

/* 
	TODO: Use StringTools library.
*/

void
Debug_FInterpreter::Debug_GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {
    	int start = oStr.find(sStr1);
    	if (start >= 0) {
    		std::string tstr = oStr.substr(start + sStr1.length());
      		int stop = tstr.find(sStr2);
      		if (stop >1)
        		rStr = oStr.substr(start + sStr1.length(), stop);
      		else
        		rStr ="error";
    	} else rStr = "error";
}

/*
	TODO: Use StringTools library.
*/
std::string
Debug_FInterpreter::Debug_EraseAllSubString(std::string & mainString, const std::string & erase) {
    size_t pos = std::string::npos;
    while((pos = mainString.find(erase)) != std::string::npos) {
        mainString.erase(pos, erase.length());
    }
    return mainString;
}

bool
Debug_FInterpreter::Debug_FindObject(std::string object, std::string find) {
	if(strstr(object.c_str(), find.c_str()))
		return true;
	else
		return false;
}

/*
	TODO: Use FileSystemPlusPlus library.
*/
bool
Debug_FInterpreter::Debug_ReadFileWithReturn(std::string file, std::string argument) {
	std::string line;
    	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    	    while (std::getline(readfile, line)) {
    	    	if(Debug_FindObject(line, argument) == true) {
        		test = line;
    	    		return true;
        	}
    	    }
    	    readfile.close();
    	} else std::cout << "Unable to open file\n";
	
	return false;
}


bool
Debug_FInterpreter::Debug_FCommentLine(std::string file, std::string argument) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    	   	while (std::getline(readfile, line)) {
    	   		test.append(line);
    	   		if(Debug_FindObject(line, argument) == true)
    	   			return true;
    	   	}
    	   	readfile.close();
    	} else std::cout << "Unable to open file\n";

    	return false;
}

void
Debug_FInterpreter::Debug_Read(std::string file) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    	    while (std::getline(readfile, line)) {
    	    	alltext.append(line + "\n");
            }
            readfile.close();
    	} else std::cout << "Unable to open file\n";
}

void
Debug_FInterpreter::Debug_Get(std::string file, std::string arg) {
	if(Debug_FindObject(arg, "get") == true) {
		std::string assign;
		std::string name;
		std::string type;
		Debug_GetBtwString(arg, "[", "]", type);
		Debug_GetBtwString(arg, ": ", " -> ", name); // Variable name
		Debug_GetBtwString(arg, " \"", "\"", assign); // Variable header
		if(Debug_ReadFileWithReturn(assign, "var[" + type + "]: ") == true) {
			std::string comp;
			Debug_GetBtwString(test, " -> ", " <-", comp);
			if(comp == name) {
				std::string text;
				Debug_GetBtwString(test, ": ", " -> ", text);
				if(type == "string") {
					
				} else if(type == "int") {
					
				} else {
				}
			}
		}
	}
}

std::string
Debug_FInterpreter::Debug_FlaScriptImporter(std::string file, std::string get) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
   	if(readfile.is_open()) {
    		while(std::getline(readfile, line)) {
    			if(Debug_FindObject(line, get) == true)
    	   			return line;
    		}
    	}
        return "null";
}

/*
	For function, statements etc.
*/
void
Debug_FInterpreter::Debug_FlaScriptInterpreterWithArg(std::string file, std::string arg) {
	Tokenizer token;
	std::string strarg;
	std::istringstream argline(arg);
    	while (std::getline(argline, strarg)) {

        	/* 
			Single Comment Line 
		*/
        	if(Debug_FindObject(strarg, token.SingleCommentLine) == true)
        		strarg.erase();

        	/* 
			Single Comment Line 
		*/
        	if(Debug_FindObject(strarg, token.CommentLineBegin) == true) {
			std::string assign;
			Debug_GetBtwString(strarg, token.CommentLineBegin, token.CommentLineEnd, assign);
			if(assign != "error") {
				strarg = Debug_EraseAllSubString(file, token.CommentLineBegin + assign + token.CommentLineEnd);
			} else {
				/*if(FCommentLine(file, "</") == true) {
				} else {
					printf("token.CommentLine Error\n");
				}*/
			}
        	}

		/*
			exit[boolean]

			exit[true]
			exit[false]
		*/
		if(Debug_FindObject(strarg, "exit") == true) {
			Debug_FStatement stat;
			stat.Debug_ExitStatement(file, strarg);
		}		

		/* 
			func -> Test()
		*/
		if(Debug_FindObject(strarg, "func -> ") == true) {
			Debug_FFunction fnc;
			fnc.Debug_Function(file, strarg);
		}

		/* 
			if {
				ifdef(linux)
				   // Code here
	   		endif}
		*/
		if(Debug_FindObject(strarg, token.If) == true) {
			Debug_FDefinition def;
			def.Debug_OSDefinition(file, strarg);
		}
		
		/* 
			print(string) -> "Hello world!" 
		*/
		if(Debug_FindObject(strarg, "print") == true) {
			Debug_FPrint pr;
			pr.Debug_Print(file, strarg);
		}		
	
		/* 
			put[<defin>] 
		*/
		if(Debug_FindObject(strarg, "put") == true) {
			if(Debug_FindObject(strarg, "->") == true) {
				Debug_FImport imp;
				imp.Debug_Import(file, strarg);
			} else {
				Debug_FDefinition def;
				def.Debug_ValueDefinition(file, strarg);
			}
		}
	
		/* 
			read(string&) -> type[cpu] 
		*/
		if(Debug_FindObject(strarg, "read") == true) {
			Debug_FRead read;
			read.Debug_Read(strarg);
		}
	
		/* 
		   Under the construction.
		   var(string&) -> Hello -> Hello <-
		   input(get[string] ->  ->) [this] 
		*/
		if(Debug_FindObject(strarg, "input") == true) {
			std::string assign;
			Debug_GetBtwString(strarg, "(", ")", assign);
			if(Debug_FindObject(assign, "get") == true) {
				std::string get;
				Debug_GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					std::cin >> inp;
					Debug_GetBtwString(strarg, " -> ", " ->", assign);
					if(Debug_ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						test = Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace + inp + 
							Whitespace + ArrowKey + Whitespace + 	assign + Whitespace + LeftArrowKey;
					}
				}
			} else if(assign == "string") std::cin >> inp;
		}

		/* 
			header[string]: Hello -> "test.flsh" 
		*/
		if(Debug_FindObject(strarg, "header") == true)
			Debug_Get(file, strarg);

		/* 
			pseudo-random generator. (rand)
			random(:1, 12:) -> print
		*/
		if(Debug_FindObject(strarg, "random") == true) {
			std::string assign;
			std::string first, second;
			Debug_GetBtwString(strarg, "(", ")", assign);
			if(assign == "error")
				std::cout << "main() : random : Brackets error. random(:, :)\n";
		
			Debug_GetBtwString(assign, ":", ", ", first);
			if(first == "error") {
				srand(time(NULL));
				int number = atoi(assign.c_str());
				std::cout << random(0, number);
			} else {
				Debug_GetBtwString(assign, ", ", " :", second);
				if(second == "error")
					  std::cout << "main() : random : Second number is not defined. random(..., 2:)\n";
		
				int first_number = atoi(first.c_str());
				int second_number = atoi(second.c_str());
				srand(time(NULL));
				std::cout << random(first_number, second_number);
			}	
		}
	
		/* 
			executepp("TestExec", "fetcheya")
		*/		
		if(Debug_FindObject(strarg, "executepp") == true) {
			Debug_FExec execute;
			execute.Debug_ExecutePp(strarg);
		}
	
		/* 
			exec(system -> scrift ->[->arg])
		*/
		if(Debug_FindObject(strarg, "exec") == true) {
			Debug_FExec execute;
			execute.Debug_Exec(strarg);
		}

		/* 
			EraseAllSubstring(string["Hello FlaScript!", "ll"])
		*/		
		if(Debug_FindObject(strarg, "EraseAllSubstring") == true) {
			Debug_FString st;
			std::cout << st.Debug_EraseAllSubString(strarg);
		}	
	}
}

/*
	FlaScript's main interpreter.
*/
void
Debug_FInterpreter::Debug_FlaScriptInterpreter(std::string file) {
	Tokenizer token;
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
        		Debug_Read(file);
        	/* 
			Single Comment Line 
		*/
        	if(Debug_FindObject(line, token.SingleCommentLine) == true)
        		line.erase();


        	/* 
			Single Comment Line 
		*/
        	if(Debug_FindObject(line, token.CommentLineBegin) == true) {
			std::string assign;
			Debug_GetBtwString(line, token.CommentLineBegin, token.CommentLineEnd, assign);
			if(assign != "error") {
				 line = Debug_EraseAllSubString(line, token.CommentLineBegin + assign + token.CommentLineEnd);
			} else {
				if(Debug_FCommentLine(file, "</") == true) {
				} else {
					std::cout << "token.CommentLine Error\n";
				}
			}
    		}

		/* 
			import(" ") -> name <- 
		*/
		if(Debug_FindObject(line, "import") == true) {
			Debug_FImport imp;
			imp.Debug_Import(file, line);
		}

		/* 
			if {
				ifdef(linux)
				   // Code here
			   endif}
		*/
		if(Debug_FindObject(line, token.If) == true) {
			Debug_FDefinition def;
			def.Debug_OSDefinition(file, line);
		}

		/*
			Code execution.
		*/
        	if(Debug_FindObject(line, "main() -> main {") == true) {
        		Debug_Read(file);
			/* Get content. */        		
			Debug_GetBtwString(alltext, "main() -> main {", "}", alltext);
        	
			/* Read line-by-line */
			std::istringstream f(alltext);     		
				
			while(std::getline(f, linebyline)) {
				/*
					Single Comment Line
				*/
				if(Debug_FindObject(linebyline, token.SingleCommentLine) == true)
        				linebyline.erase();


        			/* 
					Single Comment Line 
				*/
        			if(Debug_FindObject(linebyline, token.CommentLineBegin) == true) {
					std::string assign;
					Debug_GetBtwString(line, token.CommentLineBegin, token.CommentLineEnd, assign);
					if(assign != "error") {
						linebyline = Debug_EraseAllSubString(line, token.CommentLineBegin + assign + token.CommentLineEnd);
						
					} else {
						if(Debug_FCommentLine(file, "</") == true) {						
						} else std::cout << "token.CommentLine Error\n";
					}
    				}

				/*
					exit(boolean)

					exit(success)
					exit(failure)
				*/
				if(Debug_FindObject(linebyline, "exit") == true) {
					Debug_FStatement stat;
					stat.Debug_ExitStatement(file, linebyline);
				}		

				
				/* 
					statement[#pi] 
				*/
				if(Debug_FindObject(linebyline, "statement") == true) {
					Debug_FStatement stat;
					stat.Debug_StatementParser(file, linebyline);
				}
			
				/* 
					func -> Test() 
				*/
				if(Debug_FindObject(linebyline, "func -> ") == true) {
					Debug_FFunction fnc;
					fnc.Debug_Function(file, linebyline);
				}
			
        			/* 
					print(string) -> " " 
				*/
				if(Debug_FindObject(linebyline, "print") == true) {
					Debug_FPrint pr;
					pr.Debug_Print(file, linebyline);
				}
			
				/* 
					put[<defin>] 
				*/
				if(Debug_FindObject(linebyline, "put") == true) {
					if(Debug_FindObject(linebyline, "-> ") == true) {
						Debug_FImport imp;
						imp.Debug_Import(file, linebyline);
					} else {
						Debug_FDefinition def;
						def.Debug_ValueDefinition(file, linebyline);
					}
				}

				/* 
					read(string&) -> type[cpu] 
				*/
				if(Debug_FindObject(linebyline, "read") == true) {
					Debug_FRead read;
					read.Debug_Read(linebyline);
				}

				/* 
					var(string&) -> Hello -> Hello <-
				   	input(get[string] ->  ->) [this]
				*/			
				if(Debug_FindObject(linebyline, "input") == true) {
					std::string assign;
					Debug_GetBtwString(linebyline, "(", ")", assign);
					if(Debug_FindObject(assign, "get") == true) {
						std::string get;
						Debug_GetBtwString(assign, "[", "]", get);
						if(get == "string") {
							Debug_GetBtwString(linebyline, " -> ", " ->", assign);
							if(Debug_ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
								test = Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace + inp + 
									Whitespace + ArrowKey + Whitespace + assign + Whitespace + LeftArrowKey;
							}
						}
					} else if(assign == "string") {}
				}

				/* 
					header[string]: Hello -> "test.flsh" 
				*/
				if(Debug_FindObject(linebyline, "header") == true)
					Debug_Get(file, linebyline);

				/* 
					pseudo-random generator (rand)
					random(:1, 12:) -> print 
				*/
				if(Debug_FindObject(linebyline, "random") == true) {
					std::string assign, first, second;
					Debug_GetBtwString(linebyline, "(", ")", assign);

					if(assign == "error")
						std::cout << "main() : random : brackets error. random(:, :)\n";

					Debug_GetBtwString(assign, ":", ", ", first);

					if(first == "error") {
						srand(time(NULL));
						int number = atoi(assign.c_str());
					} else {
						Debug_GetBtwString(assign, ", ", " :", second);

						if(second == "error") 
							std::cout << "main() : random : second number is not defined. random(..., 2:)\n";
					
						int first_number = atoi(first.c_str());
						int second_number = atoi(second.c_str());
						srand(time(NULL));
					}

				}

				/* 
					executepp("TestExec", "fetcheya") 
				*/
				if(Debug_FindObject(linebyline, "executepp") == true || 
					Debug_FindObject(linebyline, "execout") == true) {
						Debug_FExec execute;
						execute.Debug_ExecutePp(linebyline);
				}

				/* 
					exec(system -> scrift ->[->arg]) 
				*/
				if(Debug_FindObject(linebyline, "exec") == true) {
					Debug_FExec execute;
					execute.Debug_Exec(linebyline);
        			}
			
				/* 
					EraseAllSubstring(string["Hello FlaScript!", "ll"]) 
				*/
				if(Debug_FindObject(linebyline, "EraseAllSubstring") == true) {
					Debug_FString st;
					st.Debug_EraseAllSubString(linebyline);
				}
        		}
       		}
	}
	} else {
		std::cout << "Unable to open file\n";
	}
}
