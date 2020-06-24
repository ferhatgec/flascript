#include <iostream>
#include "../Library/FileSystemPlusPlus.h"

class FInterpreter {
public:
	FInterpreter();
	~FInterpreter();
	static bool FindObject(std::string, std::string);
	void FlassInterpreter(std::string);
	void ReadFileWithReturn(std::string);	
};
