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
#include <Interpreter/Definitions.hpp>
#include <Interpreter/Function.hpp>

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

/*
* if {
   ifdef(__linux__)
      // Code here
* endif}
*/
void
FDefinition::OSDefinition(std::string file, std::string arg) {
	FInterpreter inp;
	FFunction func;
	
	/* [#]if */
	if(arg[0] == '#') {
        std::string assign, type, read;
		read = func.FRead(file);

        /* [#if ] */
        arg = arg.erase(0, 4);

        read = stringtools::GetBetweenString(read, "#if " + arg, "#endif " + arg);

        if(read != "error") {
            #ifdef __linux__
	            if	(arg == "LINUX")   inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __FreeBSD__
	            if(arg == "FREEBSD")   inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __OpenBSD__
	            if(arg == "OPENBSD")   inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __NetBSD__
	            if(arg == "NETBSD")    inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __gnu_hurd__
	            if(arg == "GNU_HURD")  inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __gnu_linux__
	            if(arg == "GNU_LINUX") inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __MORPHOS__
	            if(arg == "MORPHOS")   inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __APPLE__
	            if(arg == "APPLE")     inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __DragonFly__
	            if(arg == "DRAGONFLY") inp.FlaScriptInterpreterWithArg(file, read);
	        #elif __SYLLABLE__
	            if(arg == "SYLLABLE")  inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  __BEOS__
	            if(arg == "BEOS")      inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  OS2
	            if(arg == "OS2")       inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  PLAN9
	            if(arg == "PLAN9")     inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  _WIN64
	            if(arg == "WIN64")     inp.FlaScriptInterpreterWithArg(file, read);
	        #elif  _WIN32
	            if(arg == "WIN32")     inp.FlaScriptInterpreterWithArg(file, read);
	        #endif
        }
	}
}

// defin[arg] -> function <-
// Calling : put[arg]
void
FDefinition::ValueDefinition(std::string file, std::string arg) {
	FInterpreter inp;
	FFunction func;
	FTokenizer token;
	std::string assign, type;
	
	if(inp.FindObject(arg, "defin") == true) {
		stringtools::GetBtwString(arg, "[", "]", assign);
		
		if(assign != "error") {
			stringtools::GetBtwString(arg, "-> ", " <-", type);
			if(type != "error") {}
		}
	} else if(inp.FindObject(arg, "put") == true) {
		stringtools::GetBtwString(arg, "[", "]", assign);
		type = func.FRead(file);
		
		if(assign != "error") { // defin[arg] -> asd <-
			if(inp.FindObject(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign) == true) {
				stringtools::GetBtwString(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign,
				token.LeftArrowSign, assign);
				
				if(assign != "error") {
					inp.FlaScriptInterpreterWithArg(file, assign);
				}
			}
		}
	}
}
