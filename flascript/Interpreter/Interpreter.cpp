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
#include <Interpreter/Print.hpp>
#include <Interpreter/Exec.hpp>
#include <Interpreter/String.hpp>
#include <Interpreter/Function.hpp>
#include <Interpreter/Definitions.hpp>
#include <Interpreter/Import.hpp>
#include <Interpreter/Statement.hpp>
#include <Interpreter/Variable.hpp>

/* Libraries */
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

FInterpreter::FInterpreter() { }
FInterpreter::~FInterpreter() { }

std::string inp, test, alltext, linebyline;

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

/*
	TODO: Use StringTools library.
*/

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
    	} else rStr = "error";
}

/*
	TODO: Use StringTools library.
*/
std::string
FInterpreter::EraseAllSubString(std::string & mainString, const std::string & erase) {
    size_t pos = std::string::npos;
    while((pos = mainString.find(erase)) != std::string::npos)
        mainString.erase(pos, erase.length());

    return mainString;
}

bool
FInterpreter::FindObject(std::string object, std::string find) {
	if(strstr(object.c_str(), find.c_str()))
		return true;
	else
		return false;
}

/*
	TODO: Use FileSystemPlusPlus library.
*/
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
    } /*else std::cout << "Unable to open file\n";*/

	return false;
}


bool
FInterpreter::FCommentLine(std::string file, std::string argument) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    	   	while (std::getline(readfile, line)) {
    	   		test.append(line);
    	   		if(FindObject(line, argument) == true)
    	   			return true;
    	   	}
    	   	readfile.close();
    	} /*else std::cout << "Unable to open file\n";*/

    	return false;
}

void
FInterpreter::Read(std::string file) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
    	    while (std::getline(readfile, line))
    	    	alltext.append(line + "\n");

            readfile.close();
    	} /* else std::cout << "Unable to open file\n"; */
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
				if(type == "string") {
					std::cout << text;
				} else if(type == "int") {
					std::cout << atoi(text.c_str());
				}
			}
		}
	}
}

std::string
FInterpreter::FlaScriptImporter(std::string file, std::string get) {
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
   	if(readfile.is_open()) {
    		while(std::getline(readfile, line)) {
    			if(FindObject(line, get) == true)
    	   			return line;
    		}
    	}
        return "null";
}

/*
	For function, statements etc.
*/
void
FInterpreter::FlaScriptInterpreterWithArg(std::string file, std::string arg) {
	Tokenizer token;
	std::string strarg;
	std::istringstream argline(arg);
    	while (std::getline(argline, strarg)) {

        	/*
			Single Comment Line
		*/
        	if(FindObject(strarg, token.SingleCommentLine) == true)
        		strarg.erase();

        	/*
			Single Comment Line
		*/
        	if(FindObject(strarg, token.CommentLineBegin) == true) {
			std::string assign;
			GetBtwString(strarg, token.CommentLineBegin, token.CommentLineEnd, assign);
			if(assign != "error")
				strarg = EraseAllSubString(file, token.CommentLineBegin + assign + token.CommentLineEnd);
        	}

		/*
			exit[boolean]

			exit[true]
			exit[false]
		*/
		if(FindObject(strarg, "exit") == true) {
			FStatement stat;
			stat.ExitStatement(file, strarg);
		}

		/*
			func -> Test() : sysinfo <
		*/
		if(FindObject(strarg, "func -> ") == true) {
			if(stringtools::GetBetweenString(strarg, ": ", " <") != "error") {
				std::string assign = stringtools::GetBetweenString(strarg, ": ", " <");
				std::string function = stringtools::EraseAllSubString(strarg, " : " + assign + " <");
				strarg = "put[" + assign + " -> " +  function + " <-]";
				if(FindObject(strarg, "->") == true) {
					FImport imp;
					imp.Import(file, strarg);
				} else {
					FDefinition def;
					def.ValueDefinition(file, strarg);
				}
			} else {
				FFunction fnc;
				fnc.Function(file, strarg);
			}
		}

		/*
			if {
				ifdef(linux)
				   // Code here
	   		endif}
		*/
		if(FindObject(strarg, token.If) == true) {
			FDefinition def;
			def.OSDefinition(file, strarg);
		}

		/*
			print(string) -> "Hello world!"
		*/
		if(FindObject(strarg, "print") == true) {
			FPrint pr;
			pr.Print(file, strarg);
		}

		/*
			put[<defin>]
		*/
		if(FindObject(strarg, "put") == true) {
			if(FindObject(strarg, "->") == true) {
				FImport imp;
				imp.Import(file, strarg);
			} else {
				FDefinition def;
				def.ValueDefinition(file, strarg);
			}
		}

		/*
			read(string&) -> type[cpu]
		*/
		if(FindObject(strarg, "read") == true) {
			FRead read;
			read.Read(strarg);
		}

		/*
		   Under the construction.
		   var(string&) -> Hello -> Hello <-
		   input(get[string] ->  ->) [this]
		*/
		if(FindObject(strarg, "input") == true) {
			std::string assign;
			GetBtwString(strarg, "(", ")", assign);
			if(FindObject(assign, "get") == true) {
				std::string get;
				GetBtwString(assign, "[", "]", get);
				if(get == "string") {
					std::cin >> inp;
					GetBtwString(strarg, " -> ", " ->", assign);
					if(ReadFileWithReturn(file, Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace) == true) {
						test = Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace + inp +
							Whitespace + ArrowKey + Whitespace + 	assign + Whitespace + LeftArrowKey;
					}
				}
			} else if(assign == "string") std::cin >> inp;
		}

		/*
			header[string]: Hello -> "test.flsh"
		*/
		if(FindObject(strarg, "header") == true)
			Get(file, strarg);

		/*
			pseudo-random generator. (rand)
			random(:1, 12:) -> print
		*/
		if(FindObject(strarg, "random") == true) {
			std::string assign;
			std::string first, second;
			GetBtwString(strarg, "(", ")", assign);
			if(assign == "error")
				std::cout << "main() : random : Brackets error. random(:, :)\n";

			GetBtwString(assign, ":", ", ", first);
			if(first == "error") {
				srand(time(NULL));
				int number = atoi(assign.c_str());
				std::cout << random(0, number);
			} else {
				GetBtwString(assign, ", ", " :", second);
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
		if(FindObject(strarg, "executepp") == true) {
			FExec execute;
			execute.ExecutePp(strarg);
		}

		/*
			exec(system -> scrift ->[->arg])
		*/
		if(FindObject(strarg, "exec") == true) {
			FExec execute;
			execute.Exec(strarg);
		}

		/*
			EraseAllSubstring(string["Hello FlaScript!", "ll"])
		*/
		if(FindObject(strarg, "EraseAllSubstring") == true) {
			FString st;
			std::cout << st.EraseAllSubString(strarg);
		}
	}
}

/*
	FlaScript's main interpreter.
*/
void
FInterpreter::FlaScriptInterpreter(std::string file) {
	Tokenizer token;
	std::string line;
	std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    	if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
        		Read(file);
        	/*
			Single Comment Line
		*/
        	if(FindObject(line, token.SingleCommentLine) == true)
        		line.erase();


        	/*
			Single Comment Line
		*/
        	if(FindObject(line, token.CommentLineBegin) == true) {
			std::string assign;
			GetBtwString(line, token.CommentLineBegin, token.CommentLineEnd, assign);
			if(assign != "error") {
				 line = EraseAllSubString(line, token.CommentLineBegin + assign + token.CommentLineEnd);
			} else {
				if(FCommentLine(file, "</") == true) {
				}
			}
    		}

		/*
			import(" ") -> name <-
		*/
		if(FindObject(line, "import") == true) {
			FImport imp;
			imp.Import(file, line);
		}

		/*
			if {
				ifdef(linux)
				   // Code here
			   endif}
		*/
		if(FindObject(line, token.If) == true) {
			FDefinition def;
			def.OSDefinition(file, line);
		}

		/*
			Code execution.
		*/
        	if(FindObject(line, "() -> main {") == true) {
        		Read(file);
        		
			/* Get content. */
			if(FindObject(line, "main() -> main {") == true)
				GetBtwString(alltext, "main() -> main {", "} main;", alltext);
			else
				GetBtwString(alltext, "() -> main {", "} main;", alltext);
			
			/* Read line-by-line */
			std::istringstream f(alltext);

			while(std::getline(f, linebyline)) {
				/*
					Single Comment Line
				*/
				if(FindObject(linebyline, token.SingleCommentLine) == true)
        				linebyline.erase();


        			/*
					Single Comment Line
				*/
        			if(FindObject(linebyline, token.CommentLineBegin) == true) {
					std::string assign;
					GetBtwString(line, token.CommentLineBegin, token.CommentLineEnd, assign);
					if(assign != "error") {
						linebyline = EraseAllSubString(line, token.CommentLineBegin + assign + token.CommentLineEnd);

					} else {
						if(FCommentLine(file, "</") == true) {
						}
					}
    				}

				if(FindObject(linebyline, "var") == true) {
					FVariable var;
					
					std::string name, data;
					data = stringtools::GetBetweenString(linebyline, ") -> ", " -> ");
					name = stringtools::GetBetweenString(linebyline, data + " -> ", " <-");
					var.Variable(name, data);
				}
			
				/* @echo asdsad */
				if(FindObject(linebyline, "@echo") == true) {
					FVariable var;
					std::string assin = stringtools::EraseAllSubString(linebyline, "@echo ");
					assin = stringtools::EraseAllSubString(linebyline, " ");
					
					std::cout << var.GetVariable(assin);
				}
				
				/* change -> name : Hello, world < */
				if(FindObject(linebyline, "change") == true) {
					FVariable var;
					std::string get_name = stringtools::GetBetweenString(linebyline, " -> ", " : ");
					if(get_name != "error") {
						std::string get_data = stringtools::GetBetweenString(linebyline, " : ", " <");
						var.Change(get_name, get_data);	
					}
				}
				
				/*
					var(string) -> data -> name <-
				
				if(FindObject(linebyline, "var") == true) {
					FVariable var;
					var.CreateVariable(file, linebyline);
				}*/

				/*
					exit(boolean)

					exit(success)
					exit(failure)
				*/
				if(FindObject(linebyline, "exit") == true) {
					FStatement stat;
					stat.ExitStatement(file, linebyline);
				}


				/*
					statement[#pi]
				*/
				if(FindObject(linebyline, "statement") == true) {
					FStatement stat;
					stat.StatementParser(file, linebyline);
				}

				/*
					func -> Test()
				*/
				if(FindObject(linebyline, "func -> ") == true) {
					if(stringtools::GetBetweenString(linebyline, ": ", " <") != "error") {
						std::string assign = stringtools::GetBetweenString(linebyline, ": ", " <");
						if(assign != "error") {
							std::string function = stringtools::EraseAllSubString(linebyline, " : " + assign + " <");
							linebyline = stringtools::GetBetweenString(function, " -> ", "()");
							linebyline = "put[" + assign + " -> " + "func -> " + linebyline + "()" + " <-]";
							if(FindObject(linebyline, "->") == true) {
								FImport imp;
								imp.Import(file, linebyline);
							} else {
								FDefinition def;
								def.ValueDefinition(file, linebyline);
							}
						}

						linebyline.erase();
					} else {
						FFunction fnc;
						fnc.Function(file, linebyline);
					}
				}

        			/*
					print(string) -> " "
				*/
				if(FindObject(linebyline, "print") == true) {
					FPrint pr;
					pr.Print(file, linebyline);
				}

				/*
					put[<defin>]
				*/
				if(FindObject(linebyline, "put") == true) {
					if(FindObject(linebyline, "-> ") == true) {
						FImport imp;
						imp.Import(file, linebyline);
					} else {
						FDefinition def;
						def.ValueDefinition(file, linebyline);
					}
				}

				/*
					read(string&) -> type[cpu]
				*/
				if(FindObject(linebyline, "read") == true) {
					FRead read;
					read.Read(linebyline);
				}

				/*
					var(string&) -> Hello -> Hello <-
				   	input(get[string] ->  ->) [this]
				*/
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
								test = Var + BracketsBegin + Str + BracketsEnd + Whitespace + ArrowKey + Whitespace + inp +
									Whitespace + ArrowKey + Whitespace + assign + Whitespace + LeftArrowKey;
							}
						}
					} else if(assign == "string") std::cin >> inp;
				}

				/*
					header[string]: Hello -> "test.flsh"
				*/
				if(FindObject(linebyline, "header") == true)
					Get(file, linebyline);

				/*
					pseudo-random generator (rand)
					random(:1, 12:) -> print
				*/
				if(FindObject(linebyline, "random") == true) {
					std::string assign, first, second;
					GetBtwString(linebyline, "(", ")", assign);

					GetBtwString(assign, ":", ", ", first);

					if(first == "error") {
						srand(time(NULL));
						int number = atoi(assign.c_str());
						std::cout << random(0, number);
					} else {
						GetBtwString(assign, ", ", " :", second);

						int first_number = atoi(first.c_str());
						int second_number = atoi(second.c_str());
						srand(time(NULL));
						std::cout << random(first_number, second_number);
					}

				}

				/*
					executepp("TestExec", "fetcheya")
				*/
				if(FindObject(linebyline, "executepp") == true ||
					FindObject(linebyline, "execout") == true) {
						FExec execute;
						execute.ExecutePp(linebyline);
				}

				/*
					exec(system -> scrift ->[->arg])
				*/
				if(FindObject(linebyline, "exec") == true) {
					FExec execute;
					execute.Exec(linebyline);
        			}

				/*
					EraseAllSubstring(string["Hello FlaScript!", "ll"])
				*/
				if(FindObject(linebyline, "EraseAllSubstring") == true) {
					FString st;
					std::cout << st.EraseAllSubString(linebyline);
				}
        		}
       		}
	}
	}
}
