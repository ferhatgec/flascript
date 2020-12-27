/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>
#include <FlaVersion.hpp>
#include <Tokenizer.hpp>
#include <Interpreter/Interpreter.hpp>
#include <Interpreter/Read.hpp>
#include <Interpreter/Variable.hpp>
#include <Interpreter/Tools.hpp>

// Libraries
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

void 
FTools::TextBackground(int color) {
	printf("%c[%dm", ESC, 40+color);
}

std::string
FTools::EscapeSeq(std::string data) {
    data = Sequence(data);
    
    if(stringtools::Count(data, '{') == stringtools::Count(data, '}')) {
        unsigned i = stringtools::Count(data, '{');
        FVariable var;

		std::string variable, variable_data;
		
        for(; i != 0; i--) {
            variable      = stringtools::Between(data, "{", "}");
        	variable_data = var.GetVariable(variable);

            if(variable_data != "error") {
                stringtools::replaceAll(data, "{" + variable + "}", variable_data);
            }
        }
    }
    
    return data;
}

std::string
FTools::Sequence(std::string data) {
    stringtools::replaceAll(data, "\\033", "\033");
	stringtools::replaceAll(data, "\\x1", "\x1");
	stringtools::replaceAll(data, "\\x2", "\x2");
	stringtools::replaceAll(data, "\\x3", "\x3");

    stringtools::replaceAll(data, "\\n", "\n");
    stringtools::replaceAll(data, "\\t", "\t");
    stringtools::replaceAll(data, "\\a", "\a");
    stringtools::replaceAll(data, "\\b", "\b");
    stringtools::replaceAll(data, "\\v", "\v");
    stringtools::replaceAll(data, "\\r", "\r");

    return data;
}
