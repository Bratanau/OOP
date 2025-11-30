#include "Rhombus.h"
#include <cmath>
#include <stdexcept>

Rhombus::Rhombus() : vertices{{0,0}, {1,0}, {1.5,1}, {0.5,1}} {}

Rhombus::Rhombus(const std::pair<double, double>& v1,
                   const std::pair<double, double>& v2,
                   const std::pair<double, double>& v3,
                   const std::pair<double, double>& v4) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
}

std::pair<double, double> Rhombus::getVertex(int index) const {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid vertex index");
    return vertices[index];
}

void Rhombus::setVertex(int index, const std::pair<double, double>& v) {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid vertex index");
    vertices[index] = v;
}

std::pair<double, double> Rhombus::getCenter() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; ++i) {
        cx += vertices[i].first;
        cy += vertices[i].second;
    }
    cx /= 4.0;
    cy /= 4.0;
    return {cx, cy};
}

double Rhombus::getArea() const {
    double area = 0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure& Rhombus::operator=(const Figure& other) {
    if (this != &other) {
        const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
        if (otherRhombus) {
            for (int i = 0; i < 4; ++i) {
                vertices[i] = otherRhombus->vertices[i];
            }
        } else {
            throw std::invalid_argument("Cannot assign different figure type");
        }
    }
    return *this;
}

Figure& Rhombus::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Rhombus* otherRhombus = dynamic_cast<Rhombus*>(&other);
        if (otherRhombus) {
            for (int i = 0; i < 4; ++i) {
                vertices[i] = std::move(otherRhombus->vertices[i]);
            }
        }
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) return false;
    for (int i = 0; i < 4; ++i) {
        if (vertices[i] != otherRhombus->vertices[i]) return false;
    }
    return true;
}

void Rhombus::printVertices(std::ostream& os) const {
    os << "Pentagon: ";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")";
        if (i < 4) os << ", ";
    }
}

void Rhombus::readVertices(std::istream& is) {
    std::cout << "Enter 5 vertices of pentagon (x1 y1 x2 y2 x3 y3 x4 y4): ";
    for (int i = 0; i < 4; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}