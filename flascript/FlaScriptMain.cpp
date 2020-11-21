/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <FlaScriptMain.hpp>
#include <FlaVersion.hpp>

#include <Interpreter/Interpreter.hpp>
#include <Debug/Debug_Interpreter.hpp>

/* Library */
#include <FileSystemPlusPlus.h>

#define EXIT_SUCCESS 0

void HelpFunction(char** argv) {
	FlaVersion vers;
	std::cout << "Fegeya FlaScript " << vers.VersionAlgorithm() + "\n" <<
	"Usage: fla [Options] file\nOptions:\n" <<
	argv[0] << " --b  || --build  <source> : Build & Run FlaScript code\n" <<
	argv[0] << " --d  || --debug <source> : Debug FlaScript code\n" <<
	argv[0] << " --ba || --buildall <source> : [Under the construction] Debug & Build & Run\n" <<
	argv[0] << " --v  || --version : Show version\n";
}

int main(int argc, char** argv) {
	std::string copy_arg, reg;
	
	if(argc < 2) {
	    HelpFunction(argv);
		return 0;
	}

	std::string argument(argv[1]);
		
	if(argument == "--build" || argument == "--b") {
		FInterpreter interpreter;
		
		if(argc > 2) { 
			std::string file(argv[2]); 
			interpreter.FlaScriptInterpreter(file, argc, argv);
		}
	} else if(argument == "--debug" || argument == "--d") {
		Debug_FInterpreter interpreter;
		
		if(argc > 2) {
			std::string file(argv[2]);
			interpreter.Debug_FlaScriptInterpreter(file);	
		}
	} else if(argument == "--buildall" || argument == "--ba") { /* Under the construction */
		Debug_FInterpreter debug; /* Debug */
		FInterpreter interpreter; /* Build & Run */
		
		if(argc > 2) {
			std::string file(argv[2]);
			debug.Debug_FlaScriptInterpreter(file);		
			interpreter.FlaScriptInterpreter(file, argc, argv);		
		}
	} else if(argument == "--help" || argument == "--h") {
		HelpFunction(argv);
		exit(EXIT_SUCCESS);
	} else if(argument == "--version" || argument == "--v") {
		FlaVersion version;
		std::cout << version.VersionAlgorithm() << "\n";
	} else
		HelpFunction(argv);

	return 0;
}
