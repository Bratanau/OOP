#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.hpp"

class Trapezoid : public Figure {
private:
    std::pair<double, double> vertices[4];

public:
    Trapezoid();
    Trapezoid(const std::pair<double, double>& v1,
              const std::pair<double, double>& v2,
              const std::pair<double, double>& v3,
              const std::pair<double, double>& v4);

    std::pair<double, double> getVertex(int index) const override;
    void setVertex(int index, const std::pair<double, double>& v) override;

    std::pair<double, double> getCenter() const override;
    double getArea() const override;

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;

    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
};

#endif