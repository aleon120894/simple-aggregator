#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Utils functions
namespace utils {
    std::string toLower(const std::string& str);
    void trim(std::string& str);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
}

#endif // UTILS_H
