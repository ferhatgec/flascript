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
#include <Interpreter/Variable.hpp>
#include <Interpreter/FileOperations/InputStream.hpp>

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

/* @readfile -> name -> "test.md" < */
std::string
FInputStream::ReadFile(std::string directory, std::string variable) {
    FVariable get; 
    std::string data = fsplusplus::ReadFileWithReturn(directory);

    get.Equal(variable, data);
}

/* @readdir -> name -> "test.md" < */
std::string
FInputStream::ReadDir(std::string directory, std::string variable) {
    FVariable get; 
    std::string data = fsplusplus::ReadDirWithReturn(directory);

    get.Equal(variable, data);
}
