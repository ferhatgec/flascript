#!/bin/sh

g++ -I./include/ ./flascript/Interpreter.cpp ./flascript/FlaVersion.cpp ./flascript/FlaScriptMain.cpp  -o fla && ./fla --b
