#include "Pentagon.h"
#include <cmath>
#include <stdexcept>

Pentagon::Pentagon() : vertices{{0,0}, {1,0}, {1.5,1}, {0.5,1.5}, {-0.5,0.5}} {}

Pentagon::Pentagon(const std::pair<double, double>& v1,
                   const std::pair<double, double>& v2,
                   const std::pair<double, double>& v3,
                   const std::pair<double, double>& v4,
                   const std::pair<double, double>& v5) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
    vertices[4] = v5;
}

std::pair<double, double> Pentagon::getVertex(int index) const {
    if (index < 0 || index >= 5) throw std::out_of_range("Invalid vertex index");
    return vertices[index];
}

void Pentagon::setVertex(int index, const std::pair<double, double>& v) {
    if (index < 0 || index >= 5) throw std::out_of_range("Invalid vertex index");
    vertices[index] = v;
}

std::pair<double, double> Pentagon::getCenter() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 5; ++i) {
        cx += vertices[i].first;
        cy += vertices[i].second;
    }
    cx /= 5.0;
    cy /= 5.0;
    return {cx, cy};
}

double Pentagon::getArea() const {
    double area = 0;
    for (int i = 0; i < 5; ++i) {
        int j = (i + 1) % 5;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
        if (otherPentagon) {
            for (int i = 0; i < 5; ++i) {
                vertices[i] = otherPentagon->vertices[i];
            }
        } else {
            throw std::invalid_argument("Cannot assign different figure type");
        }
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Pentagon* otherPentagon = dynamic_cast<Pentagon*>(&other);
        if (otherPentagon) {
            for (int i = 0; i < 5; ++i) {
                vertices[i] = std::move(otherPentagon->vertices[i]);
            }
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon) return false;
    for (int i = 0; i < 5; ++i) {
        if (vertices[i] != otherPentagon->vertices[i]) return false;
    }
    return true;
}

void Pentagon::printVertices(std::ostream& os) const {
    os << "Pentagon: ";
    for (int i = 0; i < 5; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")";
        if (i < 4) os << ", ";
    }
}

void Pentagon::readVertices(std::istream& is) {
    std::cout << "Enter 5 vertices of pentagon (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
    for (int i = 0; i < 5; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}