/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef DEBUG_INTERPRETER_HPP
#define DEBUG_INTERPRETER_HPP

#include <iostream>
#include "../Library/FileSystemPlusPlus.h"


class Debug_FInterpreter {
public:
	Debug_FInterpreter();
	~Debug_FInterpreter();
	std::string Int = "int";
	std::string Var = "var";
	std::string Str = "string";
	std::string BracketsBegin = "(";
	std::string BracketsEnd = ")";
	std::string ArrowKey = "->";
	std::string LeftArrowKey = "<-";
	std::string Whitespace = " ";
	void Debug_Read(std::string);
	void Debug_Print(std::string, std::string);
	void Debug_Get(std::string, std::string);
	void Debug_GetBtwString(std::string, std::string, std::string, std::string &);
	void Debug_FlaScriptInterpreter(std::string);
	void Debug_FlaScriptInterpreterWithArg(std::string, std::string);
	bool Debug_ReadFileWithReturn(std::string, std::string);
	bool Debug_FCommentLine(std::string, std::string);
	static bool Debug_FindObject(std::string, std::string);
	std::string Debug_FlaScriptImporter(std::string, std::string);
	std::string Debug_EraseAllSubString(std::string &, const std::string &);	
};

#endif // DEBUG_INTERPRETER_HPP
