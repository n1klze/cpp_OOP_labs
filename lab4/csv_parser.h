#ifndef LAB4_CSV_PARSER_H
#define LAB4_CSV_PARSER_H

#include <sstream>
#include <string>
#include <tuple>

namespace parser {
    class ParsingException : public std::runtime_error {
    public:
        ParsingException(std::string error_message) : std::runtime_error(""), message_(error_message) {}
        const char* what() const noexcept override {
            return message_.c_str();
        }
    private:
        std::string message_;
    };

    template<size_t I, typename... Args>
    auto ParseElements(std::istringstream &is, std::tuple<Args...> &tuple) {
        std::string current_element;
        std::getline(is, current_element, ',');
        std::stringstream ss(current_element);
        try {
            if (!(ss >> std::get<I>(tuple)))
                throw std::invalid_argument("Bad element\n");
            if (!ss.eof())
                throw std::invalid_argument("Bad element\n");
        } catch (const std::invalid_argument &except) {
            throw I + 1;
        }
        if constexpr (I + 1 < sizeof...(Args))
            return ParseElements<I + 1>(is, tuple);
    }

    template<typename... Args> //std::ifstream &operator>>(std::ifstream &is, std::tuple<Args...> &tuple, size_t line) {
    std::ifstream &ParseLine(std::ifstream &is, std::tuple<Args...> &tuple, size_t line) {
        std::string str;
        getline(is, str);
        if (str.empty())
            return is;
        std::istringstream instr(str);
        try {
            ParseElements<0>(instr, tuple);
        } catch (const size_t column) {
            throw ParsingException("Parsing error in: " + std::to_string(line + 1) + " line, " + std::to_string(column) + " column.");
        }
        return is;
    }

    template<typename... Args>
    class CSVParser {
    public:
        class Iterator {
        public:
            explicit Iterator(std::ifstream *in) :
                    input_(in) {
                if (in != nullptr)
                    ParseLine(*in, current_row_, position_); //(*in) >> std::make_pair(current_row_, position_);
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
                ParseLine(*input_, current_row_, position_); //(*input_) >> std::make_pair(current_row_, position_);
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
            if (in.peek() == EOF || in.peek() == '\n')
                throw std::invalid_argument("Empty file");
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

   /* template<size_t I, typename... Args>
    auto ParseElements(std::istringstream &is, std::tuple<Args...> &tuple) {
        std::string current_element;
        std::getline(is, current_element, ',');
        std::stringstream ss(current_element);
        try {
            if (!(ss >> std::get<I>(tuple)))
                throw std::invalid_argument("Bad element\n");
            if (!ss.eof())
                throw std::invalid_argument("Bad element\n");
        } catch (const std::exception &except) {
            throw I + 1;
        }
        if constexpr (I + 1 < sizeof...(Args))
            return ParseElements<I + 1>(is, tuple);
    }

    template<typename... Args>
    //std::ifstream &operator>>(std::ifstream &is, std::tuple<Args...> &tuple, size_t line) {
    std::ifstream &ParseLine(std::ifstream &is, std::tuple<Args...> &tuple, size_t line) {
        std::string str;
        getline(is, str);
        if (str.empty())
            return is;
        std::istringstream instr(str);
        try {
            ParseElements<0>(instr, tuple);
        } catch (const size_t column) {
            throw ParsingException("Parsing error in: " + std::to_string(line + 1) + " line, " + std::to_string(column) + " column.");
        }
        return is;
    }*/
} //namespace parser

#endif //LAB4_CSV_PARSER_H
