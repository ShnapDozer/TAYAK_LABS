#include "StringHelper.h"

#include <sstream>

std::string StringHelper::join(const std::vector<std::string>& vec, const char* delim)
{
    std::stringstream ss;
    copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(ss, delim));
    
    std::string res = ss.str();
    res.resize(res.size() - 1);
    
    return res;
}

std::vector<std::string> StringHelper::split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
        splittedStrings.push_back(item);
    }

    return splittedStrings;
}

std::string StringHelper::replaceFirstOccurrence(std::string& s,const std::string& toReplace, const std::string& replaceWith)
{
    std::size_t pos = s.find(toReplace);

    return (pos == std::string::npos) ? s : s.replace(pos, toReplace.length(), replaceWith);
}

std::vector<std::string> StringHelper::tokenize(std::string s, std::string del)
{
    std::vector<std::string> res;
    
    int start = 0;
    int end = s.find(del);
    while (end != -1) 
    {
        std::string tmp = s.substr(start, end - start);
        if (!tmp.empty())
        {
            res.push_back(tmp);
        }
            
        start = end + del.size();
        end = s.find(del, start);
    }

    std::string tmp = s.substr(start, end - start);
    if (!tmp.empty())
    {
        res.push_back(tmp);
    }
        
    return res;
}
