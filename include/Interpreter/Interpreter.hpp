/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>


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
	std::string LeftArrowKey = "<-";
	std::string Whitespace = " ";
	void Read(std::string);
	void Print(std::string, std::string);
	void Get(std::string, std::string);
	void GetBtwString(std::string, std::string, std::string, std::string &);
	void FlaScriptInterpreter(std::string);
	void FlaScriptInterpreterWithArg(std::string, std::string);
	bool ReadFileWithReturn(std::string, std::string);
	bool FCommentLine(std::string, std::string);
	static bool FindObject(std::string, std::string);
	std::string FlaScriptImporter(std::string, std::string);
	std::string EraseAllSubString(std::string &, const std::string &);	
};

#endif // INTERPRETER_HPP
