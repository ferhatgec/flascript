#include <iostream>
#include "../include/Interpreter.hpp"
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
				if(arg == "--help") {
					HelpFunction();
					exit(EXIT_SUCCESS);
				} else if(arg == "--h") {
					HelpFunction();
					exit(EXIT_SUCCESS);
				} else if(arg == "--b" || arg == "--build") {
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
}
