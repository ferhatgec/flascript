#!/bin/sh

c++ -I./Library/ -I./include/ ./flascript/Debug/Debug_Interpreter.cpp ./flascript/Interpreter/Interpreter.cpp ./flascript/Interpreter/Definitions.cpp \
./flascript/Debug/Debug_Definitions.cpp ./flascript/Interpreter/Exec.cpp ./flascript/Debug/Debug_Exec.cpp \
./flascript/Interpreter/Read.cpp  ./flascript/Debug/Debug_Read.cpp ./flascript/Interpreter/Print.cpp ./flascript/Debug/Debug_Print.cpp \
./flascript/Interpreter/String.cpp  ./flascript/Debug/Debug_String.cpp ./flascript/Interpreter/Function.cpp ./flascript/Debug/Debug_Function.cpp  \
./flascript/Interpreter/Import.cpp ./flascript/Debug/Debug_Import.cpp ./flascript/Interpreter/Tools.cpp  ./flascript/Debug/Debug_Tools.cpp \
./flascript/Interpreter/Statement.cpp ./flascript/Debug/Debug_Statement.cpp ./flascript/Interpreter/Variable.cpp ./flascript/Interpreter/Loop.cpp  ./flascript/FlaVersion.cpp  \
./flascript/FlaScriptMain.cpp -o fla

./fla --b ./init/install.fls

