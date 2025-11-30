#include "Trapezoid.h"
#include <cmath>
#include <stdexcept>

Trapezoid::Trapezoid() : vertices{{0,0}, {1,0}, {0.5,1}, {1,1}} {}

Trapezoid::Trapezoid(const std::pair<double, double>& v1,
                     const std::pair<double, double>& v2,
                     const std::pair<double, double>& v3,
                     const std::pair<double, double>& v4) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
}

std::pair<double, double> Trapezoid::getVertex(int index) const {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid vertex index");
    return vertices[index];
}

void Trapezoid::setVertex(int index, const std::pair<double, double>& v) {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid vertex index");
    vertices[index] = v;
}

std::pair<double, double> Trapezoid::getCenter() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; ++i) {
        cx += vertices[i].first;
        cy += vertices[i].second;
    }
    cx /= 4.0;
    cy /= 4.0;
    return {cx, cy};
}

double Trapezoid::getArea() const {
    double area = 0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure& Trapezoid::operator=(const Figure& other) {
    if (this != &other) {
        const Trapezoid* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
        if (otherTrapezoid) {
            for (int i = 0; i < 4; ++i) {
                vertices[i] = otherTrapezoid->vertices[i];
            }
        } else {
            throw std::invalid_argument("Cannot assign different figure type");
        }
    }
    return *this;
}

Figure& Trapezoid::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Trapezoid* otherTrapezoid = dynamic_cast<Trapezoid*>(&other);
        if (otherTrapezoid) {
            for (int i = 0; i < 4; ++i) {
                vertices[i] = std::move(otherTrapezoid->vertices[i]);
            }
        }
    }
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    if (!otherTrapezoid) return false;
    for (int i = 0; i < 4; ++i) {
        if (vertices[i] != otherTrapezoid->vertices[i]) return false;
    }
    return true;
}

void Trapezoid::printVertices(std::ostream& os) const {
    os << "Trapezoid: ";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")";
        if (i < 3) os << ", ";
    }
}

void Trapezoid::readVertices(std::istream& is) {
    std::cout << "Enter 4 vertices of trapezoid (x1 y1 x2 y2 x3 y3 x4 y4): ";
    for (int i = 0; i < 4; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}