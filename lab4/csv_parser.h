#ifndef LAB4_CSV_PARSER_H
#define LAB4_CSV_PARSER_H

#include <sstream>
#include <string>
#include <tuple>

namespace parser {
    template<class... Args>
    class CSVParser {
    public:
        class Iterator {
        public:
            explicit Iterator(std::ifstream *in) :
                    input(in) {
                if (in != nullptr)
                    (*in) >> currentRow;
                else position = -1;
            }

            ~Iterator() = default;

            bool operator==(const Iterator &b) const {
                if (input != b.input)
                    return false;
                return position == b.position;
            }

            bool operator!=(const Iterator &b) const {
                if (input != b.input)
                    return true;
                return position != b.position;
            }

            Iterator &operator++() {
                if (input == nullptr)
                    return *this;
                (*input) >> currentRow;
                if (input->eof()) {
                    input = nullptr;
                    position = -1;
                    return *this;
                }
                position++;
                return *this;
            }

            std::tuple<Args...> &operator*() {
                return currentRow;
            }

        private:
            std::ifstream *input;
            size_t position = 0;
            std::tuple<Args...> currentRow;
        };

        CSVParser(std::ifstream &in, int skipCount) {
            std::tuple<Args ...> row;
            std::string str;
            for (int index = 0; index < skipCount; index++)
                getline(in, str);
            input = &in;
        }

        Iterator begin() {
            return Iterator(input);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

    private:
        std::ifstream *input;
    };
} //namespace parser

template<size_t I, typename... Args>
auto ParseElements(std::istringstream &is, std::tuple<Args...> &tuple) {
    std::string current_element;
    std::getline(is, current_element, ',');
    std::stringstream ss(current_element);
    ss >> std::get<I>(tuple);
    if constexpr (I + 1 < sizeof...(Args))
        return ParseElements<I + 1>(is, tuple);
}

template<typename... Args>
std::ifstream &operator>>(std::ifstream &is, std::tuple<Args...> &tuple) {
    std::string str;
    getline(is, str);
    if (str.empty())
        return is;
    std::istringstream instr(str);
    ParseElements<0>(instr, tuple);
    return is;
}

#endif //LAB4_CSV_PARSER_H
