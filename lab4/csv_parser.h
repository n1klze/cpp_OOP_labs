#ifndef LAB4_CSV_PARSER_H
#define LAB4_CSV_PARSER_H

#include <sstream>
#include <string>
#include <tuple>

namespace parser {
    template<typename... Args>
    class CSVParser {
    public:
        class Iterator {
        public:
            explicit Iterator(std::ifstream *in) :
                    input_(in) {
                if (in != nullptr)
                    (*in) >> current_row_;
                else position_ = -1;
            }

            ~Iterator() = default;

            bool operator==(const Iterator &b) const {
                if (input_ != b.input_)
                    return false;
                return position_ == b.position_;
            }

            bool operator!=(const Iterator &b) const {
                if (input_ != b.input_)
                    return true;
                return position_ != b.position_;
            }

            Iterator &operator++() {
                if (input_ == nullptr)
                    return *this;
                (*input_) >> current_row_;
                if (input_->eof()) {
                    input_ = nullptr;
                    position_ = -1;
                    return *this;
                }
                position_++;
                return *this;
            }

            std::tuple<Args...> &operator*() {
                return current_row_;
            }

        private:
            std::ifstream *input_;
            size_t position_ = 0;
            std::tuple<Args...> current_row_;
        };

        CSVParser(std::ifstream &in, int skipCount) {
            std::tuple<Args ...> row;
            std::string str;
            for (int index = 0; index < skipCount; index++)
                getline(in, str);
            input_ = &in;
        }

        Iterator begin() {
            return Iterator(input_);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

    private:
        std::ifstream *input_;
    };

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
} //namespace parser

#endif //LAB4_CSV_PARSER_H
