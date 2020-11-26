/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <FlaScriptMain.hpp>

class FInterpreter {
public:
	FInterpreter();
	~FInterpreter();
		
	void Read(std::string);
	void Print(std::string, std::string);
	void Get(std::string, std::string);
	
	void FlaScriptInterpreter(flascript_t &data);
	void FlaScriptInterpreterWithArg(std::string, std::string);
	
	bool ReadFileWithReturn(std::string, std::string);
	bool FCommentLine(std::string, std::string);
	bool FindObject(std::string, std::string);
	
	std::string FlaScriptImporter(std::string, std::string);
	std::string ValueDefinition(std::string, std::string);
};

#endif // INTERPRETER_HPP
