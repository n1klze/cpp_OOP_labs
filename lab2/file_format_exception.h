#ifndef LAB2_FILE_FORMAT_EXCEPTION_H
#define LAB2_FILE_FORMAT_EXCEPTION_H

#include <stdexcept>

namespace life {
    class FileFormatException : public std::logic_error {
    public:
        explicit FileFormatException(const std::string &error) : std::logic_error(error) {}
    };
} //namespace life

#endif //LAB2_FILE_FORMAT_EXCEPTION_H
