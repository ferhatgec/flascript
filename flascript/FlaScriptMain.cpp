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
	if(argc > 1) {
        	for(int i = 1; i < argc; i++) {
			std::string arg(argv[i]);
			reg = argv[1];
			copy_arg = arg;
		}

        } else {
        	HelpFunction(argv);
	}

	if(reg.substr(0, 2) == "--") {
		if(reg == "--build" || reg == "--b") {
			FInterpreter interp;
			interp.FlaScriptInterpreter(copy_arg);
		} else if(reg == "--debug" || reg == "--d") {
			Debug_FInterpreter interp;
			interp.Debug_FlaScriptInterpreter(copy_arg);
		} else if(reg == "--buildall" || reg == "--ba") { /* Under the construction */
			Debug_FInterpreter debug; /* Debug */
			FInterpreter interp; /* Build & Run */
			debug.Debug_FlaScriptInterpreter(copy_arg);
			interp.FlaScriptInterpreter(copy_arg);
		} else if(reg == "--help" || reg == "--h") {
			HelpFunction(argv);
			exit(EXIT_SUCCESS);
		} else if(reg == "--version" || reg == "--v") {
			FlaVersion vers;
			std::cout << vers.VersionAlgorithm() << "\n";
		} else
			HelpFunction(argv);
	}
	return 0;
}
