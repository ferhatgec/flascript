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

#include <Debug/Debug_Interpreter.hpp>
#include <Debug/Debug_Read.hpp>
#include <Debug/Debug_Definitions.hpp>
#include <Debug/Debug_Function.hpp>

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
Debug_FDefinition::Debug_OSDefinition(std::string file, std::string arg) {
	Debug_FInterpreter inp;
	Debug_FFunction func;
	if(inp.Debug_FindObject(arg, "if") == true) {
		std::string assign, type, read;
		read = func.Debug_FRead(file);
		inp.Debug_GetBtwString(read, "if {", "endif}", assign);
		if(inp.Debug_FindObject(assign, "ifdef") == true) {
			inp.Debug_GetBtwString(assign, "ifdef(", ")", type);
			inp.Debug_GetBtwString(read, ") ->", "endif}", read);
			if(type != "error") {
				if(type == "linux") {
					#ifdef __linux__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "freebsd") {
					#ifdef __FreeBSD__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "openbsd") {
					#ifdef __OpenBSD__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "netbsd") {
					#ifdef __NetBSD__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "gnuhurd") {
					#ifdef __gnu_hurd__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "gnu_linux") {
					#ifdef __gnu_linux__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "morphos") {
					#ifdef __MORPHOS__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "macos") {
					#ifdef __APPLE__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "dragonfly") {
					#ifdef __DragonFly__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "beos") {
					#ifdef __BEOS__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "syllable") {
					#ifdef __SYLLABLE__
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "os2") {
					#ifdef OS2
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "plan9") {
					#ifdef EPLAN9
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "win64") {
					#ifdef _WIN64
						inp.FlaScriptInterpreterWithArg(file, read);
					#endif
				} else if(type == "win32") {
					#ifdef _WIN32
						inp.Debug_FlaScriptInterpreterWithArg(file, read);
					#endif
				} else {
					std::cout << "Warning: ifdef( ) : Unsupported definition.\n";
					std::cout << "     ^^^\n";
					inp.Debug_FlaScriptInterpreterWithArg(file, read);
				}
			}
		}
	}
}

// defin[arg] -> function <-
// Calling : put[arg]
void
Debug_FDefinition::Debug_ValueDefinition(std::string file, std::string arg) {
	Debug_FInterpreter inp;
	Debug_FFunction func;
	FTokenizer token;
	std::string assign, type;
	if(inp.Debug_FindObject(arg, "defin") == true) {
		inp.Debug_GetBtwString(arg, "[", "]", assign);
		if(assign != "error") {
			inp.Debug_GetBtwString(arg, "-> ", " <-", type);
			if(type != "error") {}
		}
	} else if(inp.Debug_FindObject(arg, "put") == true) {
		inp.Debug_GetBtwString(arg, "[", "]", assign);
		type = func.Debug_FRead(file);
		if(assign != "error") { // defin[arg] -> asd <-
			if(inp.Debug_FindObject(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign) == true) {
				inp.Debug_GetBtwString(type, token.Definition + "[" + assign + "]" + token.Whitespace + token.RightArrowSign,
				token.LeftArrowSign, assign);
				if(assign != "error") {
					inp.Debug_FlaScriptInterpreterWithArg(file, assign);
				} else std::cout << "Error: put[] Parser error..\n";
			}
		}
	}
}
