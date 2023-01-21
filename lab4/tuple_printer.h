#ifndef LAB4_TUPLE_PRINTER_H
#define LAB4_TUPLE_PRINTER_H

#include <ostream>
#include <tuple>

template<size_t I, typename Ch, typename Tr, typename... Args>
auto PrintTuple(std::basic_ostream<Ch, Tr> &ostream, std::tuple<Args...> const &tuple) {
    ostream << std::get<I>(tuple);
    if constexpr (I + 1 < sizeof...(Args)) {
        ostream << ", ";
        return PrintTuple<I + 1>(ostream, tuple);
    }
}

template<typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &tuple) {
    os << "(";
    PrintTuple<0>(os, tuple);
    os << ")";
    return os;
}

#endif //LAB4_TUPLE_PRINTER_H
