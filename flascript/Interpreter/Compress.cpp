/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <sstream>
#include <fstream>
#include <iostream>

#include <Interpreter/Compress.hpp>

static bool alpha_or_space(const char c) { return isalpha(c) || c == ' '; }

/* Run-length encoding */
void 
FCompress::Encode(std::string& inputstring, std::string& outputstring) {
    for (unsigned int i = 0; i < inputstring.length(); i++) {
        int count = 1;
        while (inputstring[i] == inputstring[i + 1]) {
            count++;
            i++;
        }

        if (count <= 1)
            outputstring += inputstring[i];
        else {
            outputstring += std::to_string(count);
            outputstring += inputstring[i];
        }
    }
}

void 
FCompress::Decompress(std::string& compressed, std::string& original) {
    size_t i = 0;
    size_t repeat;

    while (i < compressed.length()) {
        // Normal alpha charachers
        while (alpha_or_space(compressed[i]))
            original.push_back(compressed[i++]);

        // Repeat number
        repeat = 0;
        while (isdigit(compressed[i]))
            repeat = 10 * repeat + (compressed[i++] - '0');

        auto char_to_unroll = compressed[i++];
        
        while (repeat--)
            original.push_back(char_to_unroll);
    }
}
