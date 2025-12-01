#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

namespace pxl {
namespace utils {

// Template helper: append a line to file. Throws on failure.
template<typename T>
inline void appendLineToFile(const std::string &path, const T &value) {
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) throw std::runtime_error("Cannot open file: " + path);
    ofs << value << std::endl;
}

} // namespace utils
} // namespace pxl
