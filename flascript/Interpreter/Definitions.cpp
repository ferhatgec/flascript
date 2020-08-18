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
				} else if(type == "gnuhurd") {
					#ifdef __gnu_hurd__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "gnu_linux") {
					#ifdef __gnu_linux__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "morphos") {
					#ifdef __MORPHOS__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "macos") {
					#ifdef __APPLE__ && __MACH__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "dragonfly") {
					#ifdef __DragonFly__
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "beos") {
					#ifdef __BEOS__
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
					std::cout << "ifdef( ) : Unsupported definition.\n";
					std::cout << "     ^^^\n";
					inp.FlaScriptInterpreterWithArg(file, read);
				}
			}
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
		inp.GetBtwString(arg, "[", "]", assign);
		if(assign != "error") {
			inp.GetBtwString(arg, "-> ", " <-", type);
			if(type != "error") {}
		}
	} else if(inp.FindObject(arg, "put") == true) {
		inp.GetBtwString(arg, "[", "]", assign);
		type = func.FRead(file);
		if(assign != "error") { // defin[arg] -> asd <-
			if(inp.FindObject(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign) == true) {
				inp.GetBtwString(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign,
				token.LeftArrowSign, assign);
				if(assign != "error") {
					inp.FlaScriptInterpreterWithArg(file, assign);
				}
			}
		}
	}
}
