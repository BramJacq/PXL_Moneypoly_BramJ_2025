#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

namespace pxl {
namespace utils {   // vraag 27: namespace

template<typename T>
inline void appendLineToFile(const std::string &path, const T &value) {
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) throw std::runtime_error("Cannot open file: " + path);
    ofs << value << std::endl;
}
// vraag 25: useful template function
// vraag 24: inline
// vraag 38: modern file I/O
// vraag 39: exception handling

} // namespace utils
} // namespace pxl
