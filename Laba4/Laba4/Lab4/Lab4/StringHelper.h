#pragma once

#include <string>
#include <vector>

namespace StringHelper
{

    std::string join(const std::vector<std::string>& vec, const char* delim);
    std::string replaceFirstOccurrence(std::string& s, const std::string& toReplace, const std::string& replaceWith);

    std::vector<std::string> split(std::string strToSplit, char delimeter);
    std::vector<std::string> tokenize(std::string s, std::string del = " ");
    
    const char ql[] = { char(-30), char(-128), char(-103) };
    const char qr[] = { char(-30), char(-128), char(-104) };
};
