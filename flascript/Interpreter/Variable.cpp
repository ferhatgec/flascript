/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

#include <Interpreter/Variable.hpp>

#include <StringTools.hpp>

/*
void 
FVariable::CreateVariable(std::string file, std::string argument) {
        std::string type, data, name;
        stringtools::GetBtwString(argument, "var(", ")", type);
        if(type != "error") {
                stringtools::GetBtwString(argument, " -> ", " -> ", data);
                if(data != "error") {
                        stringtools::GetBtwString(argument, " -> ", " <-", name);
                        if(name != "error") {
                                if(type == "string") {
                                        var_.insert({name, data});
                                }
                        }
                }
        }
}
*/