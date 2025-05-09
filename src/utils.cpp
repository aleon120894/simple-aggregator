#include "utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>


namespace utils {

    std::string toLower(const std::string str)
    {
    
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}
