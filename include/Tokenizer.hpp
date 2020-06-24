/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <iostream>
#include "../Library/FileSystemPlusPlus.h"

typedef struct FTokenizer {
public:
	// Comment Lines
	std::string CommentLineBegin = "/>";
	std::string CommentLineEnd = "</";
	std::string SingleCommentLine = "//";
	
	// Variables
	std::string Var = "var";
	std::string Int = "int";
	std::string String = "string";
	
	// Functions 
	std::string Func = "func";
	std::string Get = "get";
	
	// Print
	std::string Print = "print";
	
	// Sign
	std::string RightArrowSign = "->";
	std::string LeftArrowSign = "<-";
	
	// System Integration
	std::string Exec = "exec";
	std::string System = "system";
} Tokenizer;

#endif // TOKENIZER_HPP
