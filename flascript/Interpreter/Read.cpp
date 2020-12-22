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
#include <ExecutePlusPlus.hpp>

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

// exec(system -> scrift ->[->arg])
void
FRead::Read(std::string arg) {
	FInterpreter inp;
	
	if(inp.FindObject(arg, "read") == true) {
		std::string assign;
		stringtools::GetBtwString(arg, "(", ")", assign);
	
		if(assign != "error" && assign == "string&") {
			stringtools::GetBtwString(arg, "type[", "]", assign);
			
			if(assign != "error") {
				systemInfo info;
				if(assign == "cpu") {
					fsplusplus::ReadCPU();
				} else if(assign == "osname") {
					std::cout << fsplusplus::ReadOSName();
				} else if(assign == "uptime") {
					std::cout << info.getUptime();
				} else if(assign == "arch") {
					std::cout << info.getArch();
				} else if(assign == "username") {
					std::cout << info.getUsername();
				} else if(assign == "hostname") {
					std::cout << info.getHostname();
				} else if(assign == "shell") {
					std::cout << info.getShell();
				} else if(assign == "kernelname") {
					std::cout << info.getSystem();
				} else if(assign == "kernelrelease") {
					std::cout << info.getKernel();
				} else if(assign == "terminal") {
					std::cout << info.getTerm();
				} else if(assign == "time") {
					std::cout << __TIME__;
				} else if(assign == "date") {
					std::cout << __DATE__;
				} else if(assign == "branch") {
					ExecutePlusPlus ex;
					std::cout << ex.ExecWithOutput("git branch | grep \"^\\*\" | sed 's/^..//'");
				} else if(assign == "version") {
					FlaVersion ver;
					std::cout << ver.VersionAlgorithm() << "\n";
				} else {
					assign = getenv(assign.c_str());
					std::cout << assign;
				}
			}
		}
	}
}
