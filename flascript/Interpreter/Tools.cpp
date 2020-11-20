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
FlaScript::TextBackground(int color) {
	printf("%c[%dm", ESC, 40+color);
}

std::string
FlaScript::EscapeSeq(std::string data) {
	stringtools::replaceAll(data, "\\033[", "\033[");
    stringtools::replaceAll(data, "\\n", "\n");
    stringtools::replaceAll(data, "\\t", "\t");
    stringtools::replaceAll(data, "\\a", "\a");
    stringtools::replaceAll(data, "\\b", "\b");
    stringtools::replaceAll(data, "\\v", "\v");
    stringtools::replaceAll(data, "\\r", "\r");
    
    return data;
}
