/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <Interpreter/Interpreter.hpp>
#include <FlaScriptMain.hpp>
#include <FlaVersion.hpp>

#include "../Library/FileSystemPlusPlus.h"

#define EXIT_SUCCESS 0

void HelpFunction() {
	printf("Fegeya FlaScript\nflascript --b  <source> : Interprets your FlaScript code\nflascript --v || --version : Shows version\n");
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
        	HelpFunction();
	}
	
	if(reg.substr(0, 2) == "--") {
		if(reg == "--build" || reg == "--b") {
			FInterpreter interp;
			interp.FlaScriptInterpreter(copy_arg);
		} else if(reg == "--help" || reg == "--h") {
			HelpFunction();
			exit(EXIT_SUCCESS);
		} else if(reg == "--version" || reg == "--v") {
			FlaVersion vers;
			std::cout << vers.VersionAlgorithm() << "\n";
		} else {
			HelpFunction();
		}
	}
	return 0;
}
