#   MIT License
#   Customizable ScriftLang Build File
#   Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
#   Distributed under the terms of the MIT License.
# 
#!/bin/sh

g++ ./flascript/FlaScriptMain.cpp ./flascript/Interpreter.cpp -o fla && ./fla --b
