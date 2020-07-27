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
	printf("Fegeya FlaScript\nflascript --b : Interprets your FlaScript code\nflascript -v : Shows version\n");
}

int main(int argc, char** argv) {
	if(argc > 1) {
		for(int i = 1; i < argc; i++) {
			std::string arg(argv[i]);
			if(arg.substr(0, 2) == "--") {
				if(arg == "--help" || arg == "--h") {
					HelpFunction();
					exit(EXIT_SUCCESS);
				} else if(arg == "--version" || arg == "--v") {
					FlaVersion vers;
					std::cout << vers.VersionAlgorithm() << "\n";
				} else if(arg == "--build" || arg == "--b") {
					FInterpreter interp;
					std::getline(std::cin, arg);
					interp.FlaScriptInterpreter(arg);
				}
			} else {
				HelpFunction();
			}
		}
        } else {
        	HelpFunction();
        }
	return 0;
}
