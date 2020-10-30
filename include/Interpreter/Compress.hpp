/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <iostream>

class FCompress {
public:
    void Encode(std::string& input, std::string& output);
    void Decompress(std::string& input, std::string& output);    
};


#endif // COMPRESS_HPP
