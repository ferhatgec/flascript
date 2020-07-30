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
#include "../../Library/FileSystemPlusPlus.h"
#include "../../Library/Colorized.hpp"
#include "../../Library/SystemInfo.hpp"

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
	if(inp.FindObject(arg, "if") == true) {
		std::string assign, type, read;
		read = func.FRead(file);
		inp.GetBtwString(read, "if {", "endif}", assign);
		if(inp.FindObject(assign, "ifdef") == true) {
			inp.GetBtwString(assign, "ifdef(", ")", type);
			inp.GetBtwString(read, ") ->", "endif}", read);
			if(type != "error") {
				if(type == "linux") {
					#ifdef __linux__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif				
				} else if(type == "freebsd") {
					#ifdef __FreeBSD__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif				
				} else if(type == "openbsd") {
					#ifdef __OpenBSD__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "netbsd") {
					#ifdef __NetBSD__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "morphos") {
					#ifdef __MORPHOS__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "syllable") {
					#ifdef __SYLLABLE__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "os2") {
					#ifdef OS2
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "plan9") {
					#ifdef EPLAN9
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "win64") {
					#ifdef _WIN64
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "win32") {
					#ifdef _WIN32
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else {
					printf("ifdef( ) : Unsupported definition.\n");
					printf("     ^^^\n");
					inp.FlaScriptInterpreterWithArg(file, read);
				}
			} 
		}
	}
}
