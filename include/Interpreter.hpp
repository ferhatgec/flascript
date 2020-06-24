/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include "../Library/FileSystemPlusPlus.h"


class FInterpreter {
public:
	FInterpreter();
	~FInterpreter();
	std::string Int = "int";
	std::string Var = "var";
	std::string Str = "string";
	std::string BracketsBegin = "(";
	std::string BracketsEnd = ")";
	std::string ArrowKey = "->";
	std::string Whitespace = " ";
	static bool FindObject(std::string, std::string);
	void FlaScriptInterpreter(std::string);
	bool ReadFileWithReturn(std::string, std::string);
	bool FCommentLine(std::string, std::string);
	void Read(std::string);
	void Print(std::string, std::string);	
};

#endif // INTERPRETER_HPP
