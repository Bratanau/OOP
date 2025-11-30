#include "../include/figures.h"
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cmath>
#include <memory>

template<Number T>
Point<T>::Point() : x(0), y(0) {}

template<Number T>
Point<T>::Point(T x, T y) : x(x), y(y) {}

template<Number T>
Point<T>::Point(const Point& other) : x(other.x), y(other.y) {}

template<Number T>
Point<T>& Point<T>::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<Number T>
Point<T> Point<T>::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

template<Number T>
Point<T> Point<T>::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

template<Number T>
Point<T> Point<T>::operator*(T scalar) const {
    return Point(x * scalar, y * scalar);
}

template<Number T>
Point<T> Point<T>::operator/(T scalar) const {
    if (scalar == 0) throw std::invalid_argument("Division by zero");
    return Point(x / scalar, y / scalar);
}

template<Number T>
bool Point<T>::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

template<Number T>
bool Point<T>::operator!=(const Point& other) const {
    return !(*this == other);
}

template<Number T>
double Point<T>::distance(const Point& other) const {
    T dx = x - other.x;
    T dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

template<Number T>
Triangle<T>::Triangle() {
    for (auto& vertex : vertices) {
        vertex = std::make_shared<Point<T>>(0, 0);
    }
}

template<Number T>
Triangle<T>::Triangle(const std::array<Point<T>, 3>& points) {
    for (size_t i = 0; i < 3; ++i) {
        vertices[i] = std::make_shared<Point<T>>(points[i]);
    }
}

template<Number T>
Triangle<T>::Triangle(const Triangle& other) {
    for (size_t i = 0; i < 3; ++i) {
        vertices[i] = std::make_shared<Point<T>>(*other.vertices[i]);
    }
}

template<Number T>
Triangle<T>& Triangle<T>::operator=(const Triangle& other) {
    if (this != &other) {
        for (size_t i = 0; i < 3; ++i) {
            vertices[i] = std::make_shared<Point<T>>(*other.vertices[i]);
        }
    }
    return *this;
}

template<Number T>
Triangle<T>::Triangle(Triangle&& other) noexcept : vertices(std::move(other.vertices)) {}

template<Number T>
Triangle<T>& Triangle<T>::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

template<Number T>
Point<double> Triangle<T>::geometricCenter() const {
    double centerX = (vertices[0]->x + vertices[1]->x + vertices[2]->x) / 3.0;
    double centerY = (vertices[0]->y + vertices[1]->y + vertices[2]->y) / 3.0;
    return Point<double>(centerX, centerY);
}

template<Number T>
double Triangle<T>::area() const {
    double x1 = vertices[0]->x, y1 = vertices[0]->y;
    double x2 = vertices[1]->x, y2 = vertices[1]->y;
    double x3 = vertices[2]->x, y3 = vertices[2]->y;
    
    return std::abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
}

template<Number T>
void Triangle<T>::printVertices(std::ostream& os) const {
    os << "Triangle vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex->x << ", " << vertex->y << ") ";
    }
}

template<Number T>
void Triangle<T>::readVertices(std::istream& is) {
    for (int i = 0; i < 3; ++i) {
        T x, y;
        is >> x >> y;
        vertices[i] = std::make_shared<Point<T>>(x, y);
    }
}

template<Number T>
bool Triangle<T>::operator==(const Figure<T>& other) const {
    const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
    if (!otherTriangle) return false;
    
    for (size_t i = 0; i < 3; ++i) {
        if (*vertices[i] != *otherTriangle->vertices[i]) return false;
    }
    return true;
}

template<Number T>
Triangle<T>& Triangle<T>::operator=(const Figure<T>& other) {
    const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
    if (otherTriangle) {
        *this = *otherTriangle;
    }
    return *this;
}

template<Number T>
std::shared_ptr<Figure<T>> Triangle<T>::clone() const {
    return std::make_shared<Triangle<T>>(*this);
}

template<Number T>
bool Triangle<T>::isRegular() const {
    const double epsilon = 1e-6;
    
    double side1 = vertices[0]->distance(*vertices[1]);
    double side2 = vertices[1]->distance(*vertices[2]);
    double side3 = vertices[2]->distance(*vertices[0]);
    

    return (std::abs(side1 - side2) < epsilon) ||
           (std::abs(side2 - side3) < epsilon) ||
           (std::abs(side3 - side1) < epsilon);
}


template<Number T>
std::array<Point<T>, 6> Hexagon<T>::calculateVertices() const {
    std::array<Point<T>, 6> vertices;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        vertices[i] = Point<T>(
            center.x + radius * std::cos(angle),
            center.y + radius * std::sin(angle)
        );
    }
    return vertices;
}

template<Number T>
Hexagon<T>::Hexagon() : center(0, 0), radius(0) {}

template<Number T>
Hexagon<T>::Hexagon(const Point<T>& center, T radius) : center(center), radius(radius) {}

template<Number T>
Hexagon<T>::Hexagon(const Hexagon& other) : center(other.center), radius(other.radius) {}

template<Number T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon& other) {
    if (this != &other) {
        center = other.center;
        radius = other.radius;
    }
    return *this;
}

template<Number T>
Point<double> Hexagon<T>::geometricCenter() const {
    return Point<double>(center.x, center.y);
}

template<Number T>
double Hexagon<T>::area() const {
    return (3 * std::sqrt(3.0) / 2.0) * radius * radius;
}

template<Number T>
void Hexagon<T>::printVertices(std::ostream& os) const {
    auto vertices = calculateVertices();
    os << "Hexagon vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    os << "(Center: " << center << ", Radius: " << radius << ")";
}

template<Number T>
void Hexagon<T>::readVertices(std::istream& is) {
    T x, y, r;
    is >> x >> y >> r;
    center = Point<T>(x, y);
    radius = r;
}

template<Number T>
bool Hexagon<T>::operator==(const Figure<T>& other) const {
    const Hexagon* otherHexagon = dynamic_cast<const Hexagon*>(&other);
    if (!otherHexagon) return false;
    
    return center == otherHexagon->center && radius == otherHexagon->radius;
}

template<Number T>
Hexagon<T>& Hexagon<T>::operator=(const Figure<T>& other) {
    const Hexagon* otherHexagon = dynamic_cast<const Hexagon*>(&other);
    if (otherHexagon) {
        *this = *otherHexagon;
    }
    return *this;
}

template<Number T>
std::shared_ptr<Figure<T>> Hexagon<T>::clone() const {
    return std::make_shared<Hexagon<T>>(*this);
}

template<Number T>
bool Hexagon<T>::isRegular() const {
    return true;
}


template<Number T>
std::array<Point<T>, 8> Octagon<T>::calculateVertices() const {
    std::array<Point<T>, 8> vertices;
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * M_PI * i / 8;
        vertices[i] = Point<T>(
            center.x + radius * std::cos(angle),
            center.y + radius * std::sin(angle)
        );
    }
    return vertices;
}

template<Number T>
Octagon<T>::Octagon() : center(0, 0), radius(0) {}

template<Number T>
Octagon<T>::Octagon(const Point<T>& center, T radius) : center(center), radius(radius) {}

template<Number T>
Octagon<T>::Octagon(const Octagon& other) : center(other.center), radius(other.radius) {}

template<Number T>
Octagon<T>& Octagon<T>::operator=(const Octagon& other) {
    if (this != &other) {
        center = other.center;
        radius = other.radius;
    }
    return *this;
}

template<Number T>
Point<double> Octagon<T>::geometricCenter() const {
    return Point<double>(center.x, center.y);
}

template<Number T>
double Octagon<T>::area() const {
    double side = radius * std::sqrt(2 - std::sqrt(2));
    return 2 * (1 + std::sqrt(2)) * side * side;
}

template<Number T>
void Octagon<T>::printVertices(std::ostream& os) const {
    auto vertices = calculateVertices();
    os << "Octagon vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    os << "(Center: " << center << ", Radius: " << radius << ")";
}

template<Number T>
void Octagon<T>::readVertices(std::istream& is) {
    T x, y, r;
    is >> x >> y >> r;
    center = Point<T>(x, y);
    radius = r;
}

template<Number T>
bool Octagon<T>::operator==(const Figure<T>& other) const {
    const Octagon* otherOctagon = dynamic_cast<const Octagon*>(&other);
    if (!otherOctagon) return false;
    
    return center == otherOctagon->center && radius == otherOctagon->radius;
}

template<Number T>
Octagon<T>& Octagon<T>::operator=(const Figure<T>& other) {
    const Octagon* otherOctagon = dynamic_cast<const Octagon*>(&other);
    if (otherOctagon) {
        *this = *otherOctagon;
    }
    return *this;
}

template<Number T>
std::shared_ptr<Figure<T>> Octagon<T>::clone() const {
    return std::make_shared<Octagon<T>>(*this);
}

template<Number T>
bool Octagon<T>::isRegular() const {
    return true;
}

template <class T>
void Array<T>::add(std::shared_ptr<T> elem) {
    data.push_back(std::move(elem));
}

template <class T>
void Array<T>::remove(size_t index) {
    if (index < data.size()) {
        data.erase(data.begin() + index);
    }
}

template <class T>
double Array<T>::totalArea() const {
    double total = 0;
    for (const auto& elem : data) {
        total += static_cast<double>(*elem);
    }
    return total;
}

template <class T>
void Array<T>::printAll() const {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Figure " << i + 1 << ":\n";
        data[i]->printVertices(std::cout);
        std::cout << "\n";
        auto center = data[i]->geometricCenter();
        std::cout << "  Geometric center: (" << center.x << ", " << center.y << ")\n";
        std::cout << "  Area: " << data[i]->area() << "\n";
        std::cout << "  Is regular: " << (data[i]->isRegular() ? "Yes" : "No") << "\n\n";
    }
}

template <class T>
size_t Array<T>::size() const {
    return data.size();
}

template <class T>
std::shared_ptr<T>& Array<T>::get(size_t index) {
    if (index < data.size()) {
        return data[index];
    }
    throw std::out_of_range("Index out of range");
}

template<Number T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    figure.printVertices(os);
    return os;
}

template<Number T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.readVertices(is);
    return is;
}

template class Point<double>;
template class Figure<double>;
template class Triangle<double>;
template class Hexagon<double>;
template class Octagon<double>;
template class Array<Figure<double>>;

template std::ostream& operator<<(std::ostream& os, const Figure<double>& figure);
template std::istream& operator>>(std::istream& is, Figure<double>& figure);
