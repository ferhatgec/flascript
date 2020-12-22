/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>

#include <FlaScriptMain.hpp>
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
#include <Interpreter/Input.hpp>
#include <Interpreter/Compress.hpp>
#include <Interpreter/Tools.hpp>
#include <Interpreter/Math.hpp>
#include <Interpreter/Random.hpp>

#include <Interpreter/FileOperations/InputStream.hpp>
#include <Interpreter/FileSystem/Directory.hpp>

/* Libraries */
#include <Colorized.hpp>
#include <SystemInfo.hpp>
#include <StringTools.hpp>
#include <ExecutePlusPlus.hpp>

#include <BrainfuckPlusPlus.h>
#include <FileSystemPlusPlus.h>

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
		std::string assign, name, type;

		stringtools::GetBtwString(arg, "[", "]", type);
		stringtools::GetBtwString(arg, ": ", " -> ", name); // Variable name
		stringtools::GetBtwString(arg, " \"", "\"", assign); // Variable header

		if(ReadFileWithReturn(assign, "var[" + type + "]: ") == true) {
			std::string comp;

			stringtools::GetBtwString(test, " -> ", " <-", comp);

			if(comp == name) {
				std::string text;
				stringtools::GetBtwString(test, ": ", " -> ", text);

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

	while(std::getline(argline, strarg)) {
		/* Single Comment Line */
        if(FindObject(strarg, token.SingleCommentLine) == true)
			strarg.erase();

        /* Single Comment Line */
        if(FindObject(strarg, token.CommentLineBegin) == true) {
			std::string assign;
			stringtools::GetBtwString(strarg, token.CommentLineBegin, token.CommentLineEnd, assign);

			if(assign != "error")
				strarg = stringtools::EraseAllSubString(file, token.CommentLineBegin + assign + token.CommentLineEnd);
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
			error("bla bla bla")
		*/
		if(FindObject(strarg, "error") == true) {
			std::string get_data = stringtools::GetBetweenString(strarg, "error(\"", "\")");

			if(get_data != "error") {
				BOLD_RED_COLOR
				std::cout << "error: ";

				get_data = FlaScript::EscapeSeq(get_data);

				BOLD_LIGHT_WHITE_COLOR
				std::cout << get_data + "\n";

				exit(EXIT_SUCCESS);
			}
		}

		/*
			warning("bla bla bla")
		*/
		if(FindObject(strarg, "warning") == true) {
			std::string get_data = stringtools::GetBetweenString(strarg, "warning(\"", "\")");

			if(get_data != "error") {
				BOLD_YELLOW_COLOR
				std::cout << "warning: ";

				get_data = FlaScript::EscapeSeq(get_data);

				BOLD_LIGHT_WHITE_COLOR
				std::cout << get_data + "\n";
			}
		}

		/*
			success("bla bla bla")
		*/
		if(FindObject(strarg, "success") == true) {
			std::string get_data = stringtools::GetBetweenString(strarg, "success(\"", "\")");

			if(get_data != "error") {
				BOLD_LIGHT_GREEN_COLOR
				std::cout << "success: ";

				get_data = FlaScript::EscapeSeq(get_data);

				BOLD_LIGHT_WHITE_COLOR
				std::cout << get_data + "\n";
			}
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

		/* @between -> name -> first : second < */
		if(FindObject(strarg, "@between") == true) {
			FVariable var;

			std::string get_name = stringtools::GetBetweenString(strarg, "@between -> ", " -> ");
			std::string get_first = stringtools::GetBetweenString(strarg, "@between -> " + get_name + " -> ", " : ");
			std::string get_second = stringtools::GetBetweenString(strarg, "@between -> " + get_name + " -> " + get_first + " : ", " <");

			if(get_name != "error") {
				var.Between(get_name, get_first, get_second);
			}
		}

		/* @substring -> name -> abc < */
		if(FindObject(strarg, "@substring") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, "@substring -> ", " -> ");
			if(get_name != "error") {
				std::string get_data = stringtools::GetBetweenString(strarg, get_name + " -> ", " <");
				var.Substring(get_name, get_data);
			}
		}

        /* @equal -> name -> abc < */
		if(FindObject(strarg, "@equal") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, "@equal -> ", " -> ");

			if(get_name != "error") {
				std::string get_data = stringtools::GetBetweenString(strarg, get_name + " -> ", " <");

				if(ValueDefinition(file, get_data) != "") {
					get_data = ValueDefinition(file, get_data);
				} else if(strstr(get_data.c_str(), "var(")) {
					get_data = stringtools::GetBetweenString(get_data, " var(", ") <");

					get_data = var.GetVariable(get_data);
				}

				var.Equal(get_name, get_data);
			}
		}

		/* @echo -> asdsad <-*/
		if(FindObject(strarg, "@echo") == true) {
			FVariable var;
			std::string assin = stringtools::GetBetweenString(strarg, "@echo -> ", " <-");

			std::cout << var.GetVariable(assin);
		}

		/* @change -> name : Hello, world < */
		if(FindObject(strarg, "@change") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, " -> ", " : ");

			if(get_name != "error") {
				std::string get_data = stringtools::GetBetweenString(strarg, " : ", " <");
				var.Change(get_name, get_data, FLA_STRING);
			}
		}


		/* @append -> name -> Hello, world < */
		if(FindObject(strarg, "@append") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, "@append -> ", " -> ");

			if(get_name != "error") {
				std::string get_data = stringtools::GetBetweenString(strarg, get_name + " -> ", " <");
				var.Append(get_name, get_data);
			}
		}


        /* @readfile -> name -> "abc" < */
        if(FindObject(strarg, "@readfile") == true) {
            FInputStream stream;
            std::string get_name = stringtools::GetBetweenString(strarg, "@readfile -> ", " -> ");

            if(get_name != "error") {
                std::string get_dir = stringtools::GetBetweenString(strarg, get_name + " -> \"", "\" <");

                if(get_dir == "error") {
                    FVariable get;
                    get_dir = stringtools::GetBetweenString(strarg, get_name + " -> var(", ") <");

                    get_dir = get.GetVariable(get_dir);
                }

                stream.ReadFile(get_dir, get_name);
            }
        }

		/* @pop_back -> name < */
		if(FindObject(strarg, "@pop_back") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, "@pop_back -> ", " <");

			if(get_name != "error") {
				var.Pop_Back(get_name);
			}
		}

		/* @escape_seq -> name < */
		if(FindObject(strarg, "@escape_seq") == true) {
			FVariable var;

			std::string get_name = stringtools::GetBetweenString(strarg, "@escape_seq -> ", " <");
			std::string get_data = var.GetVariable(get_name);

			if(get_name != "error") {
				get_data = FlaScript::EscapeSeq(get_data);

				var.Equal(get_name, get_data);
			}
		}

		/* @readdir -> name -> "abc" < */
		if(FindObject(strarg, "@readdir") == true) {
			FInputStream stream;
			std::string get_name = stringtools::GetBetweenString(strarg, "@readdir -> ", " -> ");

			if(get_name != "error") {
				std::string get_dir = stringtools::GetBetweenString(strarg, get_name + " -> \"", "\" <");

				if(get_dir == "error") {
					FVariable get;
					get_dir = stringtools::GetBetweenString(strarg, get_name + " -> var(", ") <");

					get_dir = get.GetVariable(get_dir);
				}

				stream.ReadDir(get_dir, get_name);
			}
		}

		/* @lineof -> name -> "dir" : "val" < */
		if(FindObject(strarg, "@lineof") == true) {
			FInputStream stream;

			std::string get_name = stringtools::GetBetweenString(strarg, "@lineof -> ", " -> ");
			std::string get_dir = stringtools::GetBetweenString(strarg, "@lineof -> " + get_name + " -> \"", "\" : ");
			std::string get_val = stringtools::GetBetweenString(strarg, "@lineof -> " + get_name + " -> " + "\"" + get_dir + "\" : \"",
				"\" <");

			if(get_name != "error" && get_dir != "error" && get_val != "error") {
				stream.LineOf(get_dir, get_val, get_name);
			}
		}


		/* @chdir -> name <- */
		if(FindObject(strarg, "@chdir") == true) {
			FDirectory dir;
			std::string get_name = stringtools::GetBetweenString(strarg, "@chdir -> \"", "\" <-");

			if(get_name == "error") {
				get_name = stringtools::GetBetweenString(strarg, "@chdir -> var(", ") <-");

				FVariable var;
				get_name = var.GetVariable(get_name);
			}

			dir.ChangeDir(get_name);
		}

        /* @replace_all -> name : "abc" -> "xyz" < */
        if(FindObject(strarg, "@replace_all") == true) {
            FVariable get;
			std::string get_name = stringtools::GetBetweenString(strarg, "@replace_all -> ", " : ");

            std::string __get_name = get.GetVariable(get_name);

            if(get_name != "error") {
                std::string get_data = stringtools::GetBetweenString(strarg, get_name + " : \"", "\" -> ");
                std::string get_data_2 = stringtools::GetBetweenString(strarg, " -> \"", "\" <");

                stringtools::replaceAll(__get_name, get_data, get_data_2);

                get.Change(get_name, __get_name, FLA_STRING);
            }
        }

		/* @strip -> name < */
		if(FindObject(strarg, "@strip") == true) {
			FVariable var;
			std::string get_name = stringtools::GetBetweenString(strarg, "@strip -> ", " <");

			if(get_name != "error") {
				var.Strip(get_name);
			}
		}

		/* @ltrim -> name < */
		if(FindObject(strarg, "@ltrim") == true) {
			FVariable var;
			std::string get_variable_name = stringtools::GetBetweenString(strarg, "@ltrim -> ", " <");

			if(get_variable_name != "error") {
				std::string get_variable_data = var.GetVariable(get_variable_name);

				/* exp: get_variable_data = <sof>....test<eof> . = <ws>
					It's will be:
						<sof>test<eof>
				*/
				get_variable_data = stringtools::ltrim(get_variable_data);

				var.Equal(get_variable_name, get_variable_data);
			}
		}

		/*
			statement[#pi]
		*/
		if(FindObject(strarg, "statement") == true) {
			FStatement stat;
			stat.StatementParser(file, strarg);
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


		/* @input -> name < */
        if(FindObject(strarg, "@input") == true) {
            FInput input;

            std::string assign;
            assign = stringtools::GetBetweenString(assign, "@input -> ", " <");

            if(assign == "error") {
                assign = stringtools::GetBetweenString(strarg, "@input(", ") ->");

                if(assign == "int") {
                    input.GetInput(assign, FLA_INT);
                } else if(assign == "string") {
                    input.GetInput(assign, FLA_STRING);
                }
            } else {
                input.GetInput(assign, FLA_STRING);
            }
        }

        /* @compress -> name < */
		if(FindObject(strarg, "@compress") == true) {
			FVariable var;
            FCompress compress;

            std::string get_name = stringtools::GetBetweenString(strarg, "@compress -> ", " <");

    		if(get_name != "error") {
                std::string data = var.GetVariable(get_name);
                std::string compressed_data;

                compress.Encode(data, compressed_data);
                var.Equal(get_name, compressed_data);
            }
        }

        /* inline(brainfuck) -> {"......."} brainfuck; */
		if(FindObject(strarg, "inline") == true) {
			std::string assign = stringtools::GetBetweenString(strarg, "inline(", ")");

			std::string data = stringtools::GetBetweenString(strarg, " -> {\"", "\"}" + assign + ";");

			if(data == "error") {
				FVariable var;

				data = stringtools::GetBetweenString(strarg, " -> {var(", ")}" + assign + ";");

				if(data != "error") {
					data = var.GetVariable(data);
				}
			}

			if(assign == "brainfuck") {
				BfInterpreter(&data[0]);
			} else if(assign == "fla" || assign == "flascript") {
				FlaScriptInterpreterWithArg(file, data);
			}
		}

        /* @decompress -> name < */
		if(FindObject(strarg, "@decompress") == true) {
			FVariable var;
            FCompress compress;

            std::string get_name = stringtools::GetBetweenString(strarg, "@decompress -> ", " <");

    		if(get_name != "error") {
                std::string data = var.GetVariable(get_name);
                std::string compressed_data;

                compress.Decompress(data, compressed_data);
                var.Equal(get_name, compressed_data);
            }
        }

		/*
			header[string]: Hello -> "test.flsh"
		*/
		if(FindObject(strarg, "header") == true) {
			Get(file, strarg);
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

		/* EraseAllSubstring(string["Hello FlaScript!", "ll"]) */
		if(FindObject(strarg, "EraseAllSubstring") == true) {
			FString st;
			std::cout << st.EraseAllSubString(strarg);
		}
	}
}

std::string
FInterpreter::ValueDefinition(std::string file, std::string arg) {
	/* var(string) -> (func) getenv -> "HOME" (end) -> home <- */
	if(FindObject(arg, "getenv") == true) {
		std::string assign = "";
		assign = stringtools::GetBetweenString(arg, "getenv -> \"", "\"");

		if(assign != "error") {
			assign = getenv(assign.c_str());
		} else {
			assign = stringtools::GetBetweenString(arg, "getenv -> var(", ")");

			if(assign != "error") {
				FVariable var;

				assign = getenv(var.GetVariable(assign).c_str());
			}
		}

		return assign;
	} else if(FindObject(arg, "spec") == true) {
		/* var(string) -> (func) spec -> "__UPTIME__" (end) -> uptime <- */
		std::string assign = "";
		assign = stringtools::GetBetweenString(arg, "spec -> \"", "\"");

		if(assign != "error") {
			const auto &t = var_.find(assign);

			if (t != var_.end()) // Found
				assign = t->second;
		}

		return assign;
	} else if(FindObject(arg, "output") == true) {
		/* var(string) -> (func) output -> "fpm --info flascript" (end) -> info <- */
		std::string assign = "";
		assign = stringtools::GetBetweenString(arg, "output -> \"", "\"");

		if(assign != "error") {
			ExecutePlusPlus exec;
			return exec.ExecWithOutput(assign);
		}
	}

	return "";
}

std::string
FInterpreter::CleanComments(std::string data) {
	if(FindObject(data, "/>") == true &&
			FindObject(data, "</") == true) {
		if(stringtools::CountSub(data, "/>") == stringtools::CountSub(data, "</")) {
			unsigned i = stringtools::CountSub(data, "/>");

			for(; i != 0; i--) {
				data = stringtools::EraseSub(data, "/>" + stringtools::Between(data, "/>", "</") + "</");
			}
		}
	} else if(data[0] == '/' && data[1] == '/') data.erase();

	return data;
}

/*
	FlaScript's main interpreter.
*/
void
FInterpreter::FlaScriptInterpreter(flascript_t &data) {
	Tokenizer token;
	std::string line;

	/* Predefined Standards
		TODO: Make parser for standards.
	*/
	std::string standard_main = "main";

	std::ifstream readfile(data.file.c_str());

    if(readfile.is_open()) {
		while (std::getline(readfile, line)) {
        	Read(data.file);

        	line = stringtools::ltrim(line);

		    line = CleanComments(line);

			/* except(version) : 0.3 -> { error("This version is really old?") } version; */
			if(FindObject(line, "except") == true) {
				std::string assign = stringtools::GetBetweenString(line, "except(", ")");

				if(assign == "version") {
					std::string version = stringtools::GetBetweenString(line, " : ", " -> {");

					double version_int = std::stod(version);
					double flascript_version_int = std::stod(FLASCRIPT_VERSION);

					if(version != "error") {
						if(version_int > flascript_version_int) {
							std::string _data = stringtools::GetBetweenString(line, version + " -> {", "} " + assign + ";");
							FlaScriptInterpreterWithArg(data.file, _data);
						}
					}
				}
			}

			/* standard[main] -> "my_main" <- */
			if(FindObject(line, "standard") == true) {
				std::string assign = stringtools::GetBetweenString(line, "standard[", "]");

				if(assign == "main") {
					assign = stringtools::GetBetweenString(line, "standard[" + assign + "] -> \"", "\" <-");

					if(assign != "error") {
						standard_main = assign;
					} else {
						/* Use Embedded FlaScript code in C++ */
						FlaScriptInterpreterWithArg(data.file,
							"error(\"file: " + data.file +
								"\\ndata: " + linebyline + "\\n-> Variable cannot be parsed.\\n" +
								"idea: add '<-' end of manipulation (..[..] -> \"..\" <-) \")");
					}
				}
			}

			/* import(" ") -> name <- */
			if(FindObject(line, "import") == true) {
				FImport imp;
				imp.Import(data.file, line);
			}

			/*
				if {
				ifdef(linux)
				   // Code here
			   endif}
			*/
			if(FindObject(line, token.If) == true) {
				FDefinition def;
				def.OSDefinition(data.file, line);
			}

			/* Code execution. */
        	if(FindObject(line, "() -> " + standard_main + " {") == true) {
        		Read(data.file);

				/* Get content. */
				if(FindObject(line, standard_main + "() -> " + standard_main + " {") == true)
					stringtools::GetBtwString(alltext, standard_main + "() -> " + standard_main + " {", "} " + standard_main + ";", alltext);
				else
					stringtools::GetBtwString(alltext, "() -> " + standard_main + " {", "} " + standard_main + ";", alltext);

				/* Read line-by-line */
				std::istringstream f(alltext);

				while(std::getline(f, linebyline)) {
					linebyline = stringtools::ltrim(linebyline);

		    		linebyline = CleanComments(linebyline);

					if(FindObject(linebyline, "var(") == true) {
						FVariable var;

						std::string name, _data, type;

						type = stringtools::Between(linebyline, "var(", ")");

						/* TODO: Add returnable interpreter for variable definition */
						if(FindObject(linebyline, "(func)") == true) {
							name  = stringtools::GetBetweenString(linebyline,  "(end) -> ", " <-");
							_data = stringtools::GetBetweenString(linebyline, "(func)", "(end)");

							if(_data != "error") {
								_data = ValueDefinition(data.file, _data);

								if(type == "int") var.Variable(name, _data, FLA_INT);
								else if(type == "string") var.Variable(name, _data, FLA_STRING);
								else {
									/* error */
								}
							} else {
								FlaScriptInterpreterWithArg(data.file,
								"error(\"file: " + data.file +
									"\\ndata: " + linebyline + "\\n-> Function cannot be initialized.\\n" +
									"idea: try '(func) .. (end)'\")");
							}
						} else if(FindObject(linebyline, "(__compress__)") == true) {
                        	FCompress compress;
                        	name  = stringtools::GetBetweenString(linebyline,  "(__end__) -> ", " <-");
							_data = stringtools::GetBetweenString(linebyline, "(__compress__)", "(__end__)");


                        	if(_data != "error") {
                        	    std::string compressed_data;
                        	    compress.Encode(_data, compressed_data);

								if(type == "int") var.Variable(name, compressed_data, FLA_INT);
								else if(type == "string") var.Variable(name, compressed_data, FLA_STRING);
								else {
									/* error */
								}
							} else {
								FlaScriptInterpreterWithArg(data.file,
								"error(\"file: " + data.file +
									"\\ndata: " + linebyline + "\\n-> Variable cannot be initialized.\\n" +
									"idea: try '(__compress__) .. (__end__)'\")");
							}
                    	} else if(FindObject(linebyline, "(__decompress__)") == true) {
                        	FCompress compress;
                        	name  = stringtools::GetBetweenString(linebyline,  "(__end__) -> ", " <-");
							_data = stringtools::GetBetweenString(linebyline, "(__decompress__)", "(__end__)");


                        	if(_data != "error") {
                        	    std::string decompressed_data;
                        	    compress.Decompress(_data, decompressed_data);

								if(type == "int") var.Variable(name, decompressed_data, FLA_INT);
								else if(type == "string") var.Variable(name, decompressed_data, FLA_STRING);
								else {
									/* error */
								}
							} else {
								FlaScriptInterpreterWithArg(data.file,
								"error(\"file: " + data.file +
									"\\ndata: " + linebyline + "\\n-> Variable cannot be initialized.\\n" +
									"idea: try '(__decompress__) .. (__end__)'\")");
							}
                    	} else if(FindObject(linebyline, "(__link__)") == true) {
                    		/* var(string) -> (__link__)argv[1] (__end__) -> ... <- */
                    		name  = stringtools::GetBetweenString(linebyline,  "(__end__) -> ", " <-");
							_data = stringtools::GetBetweenString(linebyline, "(__link__)", "(__end__)");

                    		if(_data != "error") {
                    			if(FindObject(_data, "argv") == true) {
                    				int argument_case = atoi(stringtools::EraseAllSubString(_data, "argv[").c_str());

                    				if(argument_case <= data.argc) {
                    					std::string argument_data(data.argv[argument_case]);

										if(type == "string") var.Variable(name, argument_data, FLA_STRING);
										else {
											/* error (argv must be string data type) */
										}
                    				} else {
                    					var.Variable(name, "__err_fla_argv_case_size__", FLA_STRING);
                    				}
                    			} else if(FindObject(_data, "argc") == true) {
									if(type == "int") var.Variable(name, std::to_string(data.argc), FLA_INT);
									else {
										/* error (argc must be integer data type) */
									}
								} else {
									FlaScriptInterpreterWithArg(data.file,
										"error(\"file: " + data.file +
										"\\ndata: " + linebyline + "\\n-> Argument not found in built-ins.\\n" +
										"idea: erase " + _data + " try 'argv' or 'argc'\")");
								}
                    		}
                    	} else {
                    		if(stringtools::GetBetweenString(linebyline, ") -> (", ") {") != "error") {
                    			name = stringtools::GetBetweenString(linebyline, ") -> (", ") {");
                    			_data = stringtools::GetBetweenString(alltext, "-> (" + name + ") {",
									"} -> " + name + " <-");
                    		} else {
								_data = stringtools::GetBetweenString(linebyline, ") -> ", " -> ");
								name  = stringtools::GetBetweenString(linebyline, _data + " -> ", " <-");
							}

							if(stringtools::Find(name, " ")) {
								FlaScriptInterpreterWithArg(data.file,
									"warning(\"file: " + data.file +
									"\\ndata: " + linebyline + "\\n-> Whitespace detected.\\n" +
									"idea: erase whitespace from variable name, use pascal or camel case.\")");
							}

							if(type == "int") var.Variable(name, _data, FLA_INT);
							else if(type == "string") var.Variable(name, _data, FLA_STRING);
							else {
								/* error("....") from FlaScriptInterpreterWithArg */
							}
						}
					}

					/* @echo -> asdsad <-*/
					if(FindObject(linebyline, "@echo") == true) {
						FVariable var;
						std::string assin = stringtools::GetBetweenString(linebyline, "@echo -> ", " <-");

						if(assin != "error") {
							std::cout << var.GetVariable(assin);
						} else {
							FlaScriptInterpreterWithArg(data.file,
								"error(\"file: " + data.file +
								"\\ndata: " + linebyline + "\\n-> Parse error.\\n" +
								"idea: add '->' of front and add '<-' of end\")");
						}
					}

					/* @change -> name : Hello, world < */
					if(FindObject(linebyline, "@change") == true) {
						/* TODO:
							* Change syntax with @change -> name : "for strings" <
							* and                @change -> name : for_integers <
						*/
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, " -> ", " : ");

						if(get_name != "error") {
							std::string get_data = stringtools::GetBetweenString(linebyline, " : ", " <");
							var.Change(get_name, get_data, FLA_STRING);
						}
					}

					/* @append -> name -> Hello, world < */
					if(FindObject(linebyline, "@append") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@append -> ", " -> ");

						if(get_name != "error") {
							std::string get_data = stringtools::GetBetweenString(linebyline, get_name + " -> ", " <");
							var.Append(get_name, get_data);
						}
					}


					/* @between -> name -> first : second < */
					if(FindObject(linebyline, "@between") == true) {
						FVariable var;

						std::string get_name = stringtools::GetBetweenString(linebyline, "@between -> ", " -> ");
						std::string get_first = stringtools::GetBetweenString(linebyline, "@between -> " + get_name + " -> ", " : ");
						std::string get_second = stringtools::GetBetweenString(linebyline, "@between -> " + get_name + " -> " + get_first + " : ", " <");

						if(get_name != "error") {
							var.Between(get_name, get_first, get_second);
						}
					}

                	/* @readfile -> name -> "abc" < */
                	if(FindObject(linebyline, "@readfile") == true) {
						FInputStream stream;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@readfile -> ", " -> ");

						if(get_name != "error") {
							std::string get_dir = stringtools::GetBetweenString(linebyline, get_name + " -> \"", "\" <");

                	        if(get_dir == "error") {
                	            FVariable get;
                	            get_dir = stringtools::GetBetweenString(linebyline, get_name + " -> var(", ") <");

                	            get_dir = get.GetVariable(get_dir);
                	        }

							stream.ReadFile(get_dir, get_name);
						}
					}

					/* @readdir -> name -> "abc" < */
                	if(FindObject(linebyline, "@readdir") == true) {
						FInputStream stream;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@readdir -> ", " -> ");

						if(get_name != "error") {
							std::string get_dir = stringtools::GetBetweenString(linebyline, get_name + " -> \"", "\" <");

                    	    if(get_dir == "error") {
                    	        FVariable get;

                    	        get_dir = stringtools::GetBetweenString(linebyline, get_name + " -> var(", ") <");

                    	        get_dir = get.GetVariable(get_dir);
                    	    }

							stream.ReadDir(get_dir, get_name);
						}
					}

					/* @lineof -> name -> "dir" : "val" < */
					if(FindObject(linebyline, "@lineof") == true) {
						FInputStream stream;

						std::string get_name = stringtools::GetBetweenString(linebyline, "@lineof -> ", " -> ");
						std::string get_dir = stringtools::GetBetweenString(linebyline, "@lineof -> " + get_name + " -> \"", "\" : ");
						std::string get_val = stringtools::GetBetweenString(linebyline, "@lineof -> " + get_name + " -> " + "\"" + get_dir + "\" : \"",
							"\" <");

						if(get_name != "error" && get_dir != "error" && get_val != "error") {
							stream.LineOf(get_dir, get_val, get_name);
						}
					}

                	/* @chdir -> name <- */
					if(FindObject(linebyline, "@chdir") == true) {
						FDirectory dir;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@chdir -> \"", "\" <-");

						if(get_name == "error") {
                    	    get_name = stringtools::GetBetweenString(linebyline, "@chdir -> var(", ") <-");

                    	    FVariable var;
                    	    get_name = var.GetVariable(get_name);
                   	 	}

                    	dir.ChangeDir(get_name);
					}

                	/* @replace_all -> name : "abc" -> "xyz" < */
                	if(FindObject(linebyline, "@replace_all") == true) {
						FVariable get;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@replace_all -> ", " : ");

                    	std::string __get_name = get.GetVariable(get_name);

						if(get_name != "error") {
							std::string get_data = stringtools::GetBetweenString(linebyline, get_name + " : \"", "\" -> ");
                    	    std::string get_data_2 = stringtools::GetBetweenString(linebyline, " -> \"", "\" <");

							stringtools::replaceAll(__get_name, get_data, get_data_2);

                    	    get.Change(get_name, __get_name, FLA_STRING);
						}
					}

	                /* @compress -> name < */
					if(FindObject(linebyline, "@compress") == true) {
						FVariable var;
    	                FCompress compress;

    	                std::string get_name = stringtools::GetBetweenString(linebyline, "@compress -> ", " <");

						if(get_name != "error") {
    	                    std::string data = var.GetVariable(get_name);
    	                    std::string compressed_data;

    	                    compress.Encode(data, compressed_data);
    	                    var.Equal(get_name, compressed_data);
    	                }
					}

    	            /* @decompress -> name < */
    	    		if(FindObject(linebyline, "@decompress") == true) {
    	    			FVariable var;
    	                FCompress compress;

    	                std::string get_name = stringtools::GetBetweenString(linebyline, "@decompress -> ", " <");

    	        		if(get_name != "error") {
    	                    std::string data = var.GetVariable(get_name);
    	                    std::string compressed_data;

    	                    compress.Decompress(data, compressed_data);
    	                    var.Equal(get_name, compressed_data);
    	                }
    	            }

					/* @pop_back -> name < */
					if(FindObject(linebyline, "@pop_back") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@pop_back -> ", " <");

						if(get_name != "error") {
							var.Pop_Back(get_name);
						}
					}

					/* @escape_seq -> name < */
					if(FindObject(linebyline, "@escape_seq") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@escape_seq -> ", " <");
						std::string get_data = var.GetVariable(get_name);

						if(get_name != "error") {
							get_data = FlaScript::EscapeSeq(get_data);

							var.Equal(get_name, get_data);
						}
					}

					/* @strip -> name < */
					if(FindObject(linebyline, "@strip") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@strip -> ", " <");

						if(get_name != "error") {
							var.Strip(get_name);
						}
					}

					/* @substring -> name -> abc < */
					if(FindObject(linebyline, "@substring") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@substring -> ", " -> ");

						if(get_name != "error") {
							std::string get_data = stringtools::GetBetweenString(linebyline, get_name + " -> ", " <");
							var.Substring(get_name, get_data);
						}
					}

    	            /* @equal -> name -> abc < */
    	            if(FindObject(linebyline, "@equal") == true) {
						FVariable var;
						std::string get_name = stringtools::GetBetweenString(linebyline, "@equal -> ", " -> ");

						if(get_name != "error") {
							std::string get_data = stringtools::GetBetweenString(linebyline, get_name + " -> ", " <");

							if(ValueDefinition(data.file, get_data) != "") {
								get_data = ValueDefinition(data.file, get_data);
							} else if(strstr(get_data.c_str(), "var(")) {
								get_data = stringtools::GetBetweenString(get_data, " var(", ") <");

								get_data = var.GetVariable(get_data);
							}

							var.Equal(get_name, get_data);
						}
					}

					/* @trim(type) -> name <

					   type:
					   	left:
					   	right:
					   	null:
					*/
					if(FindObject(linebyline, "@trim") == true) {
						FVariable var;

						/* It must be left, right or null */
						std::string get_pos = stringtools::Between(linebyline, "@trim(", ")");
						std::string get_variable = stringtools::Between(linebyline, "@trim(" + get_pos + ") -> ", " <");

						if(get_variable != "error") {
							std::string get_variable_data = var.GetVariable(get_variable);

							if(get_pos == "left")       get_variable_data = stringtools::ltrim(get_variable_data);
							else if(get_pos == "right") get_variable_data = stringtools::rtrim(get_variable_data);
							else if(get_pos == "null")  {
								get_variable_data = stringtools::ltrim(get_variable_data);
								get_variable_data = stringtools::rtrim(get_variable_data);
							}

							var.Equal(get_variable, get_variable_data);
						}
					}

					/* built-in @sqrt(integer) -> name < */
					if(FindObject(linebyline, "@sqrt") == true) {
						FVariable var;
						FMath sqrt;

						std::string get_integer = stringtools::GetBetweenString(linebyline, "@sqrt(", ") ->");

						if(get_integer != "error") {
							std::string get_variable = stringtools::Between(linebyline, "@sqrt(" + get_integer + ") -> ", " <");

							if(FindObject(get_integer, "var") == true) {
								get_integer = stringtools::Between(get_integer, "var(", ")");

								get_integer = var.GetVariable(get_integer);
							}

							get_integer = std::to_string(sqrt.Sqrt(atoi(get_integer.c_str())));

							get_integer.append(" ");

							var.Equal(get_variable, get_integer);
						}
					}


					/* built-in @square(integer) -> name < */
					if(FindObject(linebyline, "@square") == true) {
						FVariable var;
						FMath sq;

						std::string get_integer = stringtools::GetBetweenString(linebyline, "@square(", ") ->");

						if(get_integer != "error") {
							std::string get_variable = stringtools::Between(linebyline, "@square(" + get_integer + ") -> ", " <");

							if(FindObject(get_integer, "var") == true) {
								get_integer = stringtools::Between(get_integer, "var(", ")");

								get_integer = var.GetVariable(get_integer);
							}

							get_integer = std::to_string(sq.Square(atoi(get_integer.c_str())));

							get_integer.append(" ");

							var.Equal(get_variable, get_integer);
						}
					}

					/* built-in @factorial(integer) -> name < */
					if(FindObject(linebyline, "@factorial") == true) {
						FVariable var;
						FMath factorial;

						std::string get_integer = stringtools::GetBetweenString(linebyline, "@factorial(", ") ->");

						if(get_integer != "error") {
							std::string get_variable = stringtools::Between(linebyline, "@factorial(" + get_integer + ") -> ", " <");


							if(FindObject(get_integer, "var") == true) {
								get_integer = stringtools::Between(get_integer, "var(", ")");

								get_integer = var.GetVariable(get_integer);
							}

							get_integer = std::to_string(factorial.Factorial(atoi(get_integer.c_str())));

							get_integer.append(" ");

							var.Equal(get_variable, get_integer);
						}
					}


					/* inline(brainfuck) -> {"......."} brainfuck; */
					if(FindObject(linebyline, "inline") == true) {
						std::string assign = stringtools::GetBetweenString(linebyline, "inline(", ")");

						std::string _data = stringtools::GetBetweenString(linebyline, " -> {\"", "\"}" + assign + ";");

						if(_data == "error") {
							FVariable var;

							_data = stringtools::GetBetweenString(linebyline, " -> {var(", ")}" + assign + ";");

							if(_data != "error") {
								_data = var.GetVariable(_data);
							}
						}

						if(assign == "brainfuck") {
							BfInterpreter(&_data[0]);
						} else if(assign == "fla" || assign == "flascript") {
							FlaScriptInterpreterWithArg(data.file, _data);
						}
					}

					/* error("bla bla bla") */
    	    		if(FindObject(linebyline, "error") == true) {
    	    			std::string get_data = stringtools::GetBetweenString(linebyline, "error(\"", "\")");

        				if(get_data != "error") {
        					BOLD_RED_COLOR
        					std::cout << "error: ";

        					BOLD_LIGHT_WHITE_COLOR
        					std::cout << get_data + "\n";

        					exit(EXIT_SUCCESS);
        				}
        			}

        			/* warning("bla bla bla") */
        			if(FindObject(linebyline, "warning") == true) {
        				std::string get_data = stringtools::GetBetweenString(linebyline, "warning(\"", "\")");

        				if(get_data != "error") {
        					BOLD_YELLOW_COLOR
        					std::cout << "warning: ";

        					BOLD_LIGHT_WHITE_COLOR
        					std::cout << get_data + "\n";
        				}
        			}

					/* success("bla bla bla") */
					if(FindObject(linebyline, "success") == true) {
						std::string get_data = stringtools::GetBetweenString(linebyline, "success(\"", "\")");

						if(get_data != "error") {
							BOLD_LIGHT_GREEN_COLOR
							std::cout << "success: ";

							BOLD_LIGHT_WHITE_COLOR
							std::cout << get_data + "\n";
						}
					}

					/* exit(boolean)

					   exit(success)
					   exit(failure)
					*/
					if(FindObject(linebyline, "exit") == true) {
						FStatement stat;
						stat.ExitStatement(data.file, linebyline);
					}


					/* statement[#pi] */
					if(FindObject(linebyline, "statement") == true) {
						FStatement stat;
						stat.StatementParser(data.file, linebyline);
					}

					/* func -> Test() */
					if(FindObject(linebyline, "func -> ") == true) {
						if(stringtools::GetBetweenString(linebyline, ": ", " <") != "error") {
							std::string assign = stringtools::GetBetweenString(linebyline, ": ", " <");

							if(assign != "error") {
								std::string function = stringtools::EraseAllSubString(linebyline, " : " + assign + " <");
								linebyline = stringtools::GetBetweenString(function, " -> ", "()");
								linebyline = "put[" + assign + " -> " + "func -> " + linebyline + "()" + " <-]";

								if(FindObject(linebyline, "->") == true) {
									FImport imp;
									imp.Import(data.file, linebyline);
								} else {
									FDefinition def;
									def.ValueDefinition(data.file, linebyline);
								}
							}

							linebyline.erase();
						} else {
							FFunction fnc;
							fnc.Function(data.file, linebyline);
						}
					}

        			/* print(string) -> " " */
					if(FindObject(linebyline, "print") == true) {
						FPrint pr;
						pr.Print(data.file, linebyline);
					}

					/* put[<defin>] */
					if(FindObject(linebyline, "put") == true) {
						if(FindObject(linebyline, "-> ") == true) {
							FImport imp;
							imp.Import(data.file, linebyline);
						} else {
							FDefinition def;
							def.ValueDefinition(data.file, linebyline);
						}
					}

					/* read(string&) -> type[cpu] */
					if(FindObject(linebyline, "read") == true) {
						FRead read;
						read.Read(linebyline);
					}

                    /* remove duplicated functions & link with FlaScriptInterpreterWithArg */
					/* @input -> name < */
					if(FindObject(linebyline, "@input") == true) {
						if(data.dir != "") chdir(data.dir.c_str());
						FInput input;

						std::string assign;
						assign = stringtools::GetBetweenString(linebyline, "@input -> ", " <");

                        if(assign == "error") {
                            assign = stringtools::GetBetweenString(linebyline, "@input(", ") ->");

                            if(assign == "int") {
                                assign = stringtools::GetBetweenString(linebyline,
                                "@input(" + assign + ") -> ",  " <");

                                input.GetInput(assign, FLA_INT);
                            } else if(assign == "string") {
                                assign = stringtools::GetBetweenString(linebyline,
                                "@input(" + assign + ") -> ",  " <");

                                input.GetInput(assign, FLA_STRING);
                            }
                        } else {
                            assign = stringtools::GetBetweenString(linebyline,
                                "@input(" + assign + ") -> ",  " <");

                            input.GetInput(assign, FLA_STRING);
                        }

						if(data.dir != "") chdir(data.dir.c_str());
					}

					/* @getchar -> name < */
					if(FindObject(linebyline, "@getchar") == true) {
						if(data.dir != "" && data.dir.length() != 0) chdir(data.dir.c_str());

						FInput input;

						std::string variable_name;
						variable_name = stringtools::GetBetweenString(linebyline, "@getchar -> ", " <");

						input.GetCharInput(variable_name);

						if(data.dir != "" && data.dir.length() != 0) chdir(data.dir.c_str());
					}


					/* header[string]: Hello -> "test.flsh" */
					if(FindObject(linebyline, "header") == true) {
						Get(data.file, linebyline);
					}



					/* executepp("TestExec", "fetcheya") */
					if(FindObject(linebyline, "executepp") == true ||
						FindObject(linebyline, "execout") == true) {
						FExec execute;
						execute.ExecutePp(linebyline);
					}

					/* exec(system -> scrift ->[->arg]) */
					if(FindObject(linebyline, "exec") == true) {
						FExec execute;
						execute.Exec(linebyline);
        			}

					/* TODO:
						Implement rand() from scratch.

						syntax:
							@random(start) -> variable <
							@random(10) -> test <
					*/
					if(FindObject(linebyline, "@random") == true) {
						std::string get_data, get_start, get_variable;

						get_data = stringtools::Between(linebyline, "@random(", ")");

						if(get_data != "error") {
							FRandom random;
							FVariable var;

							if(get_data.rfind("var", 0) == 0) {
								get_data = stringtools::Between(get_data, "var(", ")");

								get_data = var.GetVariable(get_data);
							}

							get_variable = stringtools::Between(linebyline,
								" -> ", " <");

							get_start = std::to_string(random.Random(atoi(get_data.c_str())));

							get_start.append(" ");

							var.Equal(get_variable, get_start);
						}
					}

					/* @variable = "hello" < */
					if(linebyline[0] == '@') {
						FVariable var;
						std::string variable, token, other;

						std::string new_data = stringtools::GetBetweenString(linebyline, "\"", "\" <");

						for(unsigned i = 0; linebyline[i] != '\0'; i++) {
							if(linebyline[i] == '!'
							    && linebyline[i + 1] == '!'
							    && linebyline[i + 2] == '=') {
                                token = "!!";
                                break;
							} else if(linebyline[i + 1] != '=') {
								variable.push_back(linebyline[i]);
							} else {
								token.push_back(linebyline[i]);
								break;
							}
						}

						variable = stringtools::rtrim(variable);
						variable = stringtools::ltrim(variable);

						variable = variable.erase(0, 1); // erase @ character

                        linebyline = stringtools::EraseAllSubString(linebyline , " ");

						/* get token @<variable> <token>= .... <*/
						if(token == "/"
							|| token == "-"
							|| token == "*"
							|| token == "+"
							|| token == "%"
							|| token == "!!") { /* /= -= *= += %= */
							new_data = stringtools::EraseAllSubString(linebyline, "@" + variable + token + "=");

                            if(stringtools::GetBetweenString(new_data, "->", "<") != "error") {
                                other = stringtools::GetBetweenString(new_data, "->", "<");
                                other = other.erase(0, 4);

                                other.pop_back();

                                new_data = stringtools::EraseAllSubString(new_data, "->var("+ other + ")<");
                            } else new_data.pop_back();

                            if(new_data.rfind("var", 0) == 0) {
                                new_data = new_data.erase(0, 4);

                                new_data.pop_back();

                                new_data = var.GetVariable(new_data);
                            }

							if(token      == "/") new_data = std::to_string(atoi(var.GetVariable(variable).c_str()) / atoi(new_data.c_str()));
							else if(token == "-") new_data = std::to_string(atoi(var.GetVariable(variable).c_str()) - atoi(new_data.c_str()));
							else if(token == "*") new_data = std::to_string(atoi(var.GetVariable(variable).c_str()) * atoi(new_data.c_str()));
							else if(token == "+") new_data = std::to_string(atoi(var.GetVariable(variable).c_str()) + atoi(new_data.c_str()));
							else if(token == "%") new_data = std::to_string(atoi(var.GetVariable(variable).c_str()) % atoi(new_data.c_str()));
							else if(token == "!!") {
							    FMath fact;
							    new_data = std::to_string(fact.Factorial(atoi(new_data.c_str())));
							} else {}
							/* undefined token (error) */

							if(new_data.length() <= 2) {
								new_data.append("  ");
							}

                            if(other.length() != 0)
							    var.Change(other, new_data, FLA_INT);
						    else
						        var.Change(variable, new_data, FLA_INT);
						} else if(token == "=") { /* == */
							var.Change(variable, new_data, FLA_STRING);
						}
					}

					/* EraseAllSubstring(string["Hello FlaScript!", "ll"]) */
					if(FindObject(linebyline, "EraseAllSubstring") == true) {
						FString st;
						std::cout << st.EraseAllSubString(linebyline);
					}
        		}
       		}
		}
	}
}
