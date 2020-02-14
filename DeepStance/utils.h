#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utility {
    std::string run_pyscript(std::string path);
    std::string runCmd(const wchar_t* cmd);
    std::vector<std::string> split(const std::string& str, const std::string& delim);
}

#endif
