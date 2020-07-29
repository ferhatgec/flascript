#!/bin/sh

g++ -I./include/ ./flascript/Interpreter/Interpreter.cpp ./flascript/Interpreter/Exec.cpp \
./flascript/Interpreter/Read.cpp ./flascript/Interpreter/Print.cpp ./flascript/Interpreter/String.cpp \
./flascript/Interpreter/Function.cpp ./flascript/FlaVersion.cpp ./flascript/FlaScriptMain.cpp  -o fla && ./fla --b
