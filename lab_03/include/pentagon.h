#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.hpp"

class Pentagon : public Figure {
private:
    std::pair<double, double> vertices[5];

public:
    Pentagon();
    Pentagon(const std::pair<double, double>& v1,
             const std::pair<double, double>& v2,
             const std::pair<double, double>& v3,
             const std::pair<double, double>& v4,
             const std::pair<double, double>& v5);

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