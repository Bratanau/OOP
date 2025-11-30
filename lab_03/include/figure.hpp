#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <utility>
#include <memory>

class Figure {
public:
    virtual ~Figure() = default;

    virtual std::pair<double, double> getVertex(int index) const = 0;
    virtual void setVertex(int index, const std::pair<double, double>& v) = 0;

    virtual std::pair<double, double> getCenter() const = 0;
    virtual double getArea() const = 0;

    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) noexcept = 0;
    virtual bool operator==(const Figure& other) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual operator double() const {
        return getArea();
    }

protected:
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readVertices(std::istream& is) = 0;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif