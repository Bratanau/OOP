#include "figure.hpp"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.printVertices(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.readVertices(is);
    return is;
}