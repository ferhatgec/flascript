#include <iostream>
#include "../Library/FileSystemPlusPlus.h"


class FInterpreter {
public:
	FInterpreter();
	~FInterpreter();
	std::string Var = "var";
	std::string Str = "string";
	std::string BracketsBegin = "(";
	std::string BracketsEnd = ")";
	std::string ArrowKey = "->";
	std::string Whitespace = " ";
	static bool FindObject(std::string, std::string);
	void FlaScriptInterpreter(std::string);
	bool ReadFileWithReturn(std::string, std::string);	
};
