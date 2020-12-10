#!/bin/sh

c++ -I./Library/ -I./include/                          \
./flascript/Interpreter/Interpreter.cpp                \
./flascript/Interpreter/Definitions.cpp                \
./flascript/Interpreter/Exec.cpp                       \
./flascript/Interpreter/Read.cpp                       \
./flascript/Interpreter/Print.cpp                      \
./flascript/Interpreter/String.cpp                     \
./flascript/Interpreter/Function.cpp                   \
./flascript/Interpreter/Import.cpp                     \
./flascript/Interpreter/Statement.cpp                  \
./flascript/Interpreter/Tools.cpp                      \
./flascript/Interpreter/Variable.cpp                   \
./flascript/Interpreter/Loop.cpp                       \
./flascript/Interpreter/Input.cpp                      \
./flascript/Interpreter/Compress.cpp                   \
./flascript/Interpreter/FileOperations/InputStream.cpp \
./flascript/Interpreter/FileSystem/Directory.cpp       \
./flascript/Interpreter/Math.cpp                       \
./flascript/Interpreter/Random.cpp                     \
./flascript/FlaVersion.cpp                             \
./flascript/FlaScriptMain.cpp -o fla && ./fla --b test.fls
