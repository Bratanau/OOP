#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <array>
#include <utility>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>
#include <concepts>

template <typename T>
concept Number = std::floating_point<T> || std::integral<T>;

template<Number T>
class Point {
public:
    T x, y;
    
    Point();
    Point(T x, T y);
    
    Point(const Point& other);
    
    Point& operator=(const Point& other);
    
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator*(T scalar) const;
    Point operator/(T scalar) const;
    

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    
    double distance(const Point& other) const;
    
    template<Number U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

template<Number T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<double> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readVertices(std::istream& is) = 0;
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual Figure& operator=(const Figure<T>& other) = 0;
    
    // Паттерн "Прототип" - клонирование объектов
    virtual std::shared_ptr<Figure<T>> clone() const = 0;  
    
    // Проверка на правильность фигуры
    virtual bool isRegular() const = 0; 
    
    operator double() const {
        return area();
    }
};

template<Number T>
class Triangle : public Figure<T> {
private:
    std::array<std::shared_ptr<Point<T>>, 3> vertices; 
    
public:
    Triangle();
    Triangle(const std::array<Point<T>, 3>& points);
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    Triangle& operator=(Triangle&& other) noexcept;
    
    Point<double> geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    
    bool operator==(const Figure<T>& other) const override;
    Triangle& operator=(const Figure<T>& other) override;
    
    std::shared_ptr<Figure<T>> clone() const override;  
    
    bool isRegular() const override;
    
    const std::array<std::shared_ptr<Point<T>>, 3>& getVertices() const { return vertices; } 
};

template<Number T>
class Hexagon : public Figure<T> {
private:
    Point<T> center;
    T radius;
    
    std::array<Point<T>, 6> calculateVertices() const;
    
public:
    Hexagon();
    Hexagon(const Point<T>& center, T radius);
    Hexagon(const Hexagon& other);
    Hexagon& operator=(const Hexagon& other);
    
    Point<double> geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    
    bool operator==(const Figure<T>& other) const override;
    Hexagon& operator=(const Figure<T>& other) override;
    
    std::shared_ptr<Figure<T>> clone() const override;
    
    bool isRegular() const override; 
    
    const Point<T>& getCenter() const { return center; }
    T getRadius() const { return radius; }
};

template<Number T>
class Octagon : public Figure<T> {
private:
    Point<T> center;
    T radius;
    
    std::array<Point<T>, 8> calculateVertices() const;
    
public:
    Octagon();
    Octagon(const Point<T>& center, T radius);
    Octagon(const Octagon& other);
    Octagon& operator=(const Octagon& other);
    
    Point<double> geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    
    bool operator==(const Figure<T>& other) const override;
    Octagon& operator=(const Figure<T>& other) override;
    
    std::shared_ptr<Figure<T>> clone() const override; 
    
    bool isRegular() const override; 
    
    const Point<T>& getCenter() const { return center; }
    T getRadius() const { return radius; }
};

template <class T> 
class Array {
private:
    std::vector<std::shared_ptr<T>> data; // Хранение умными указателями 
public:
    void add(std::shared_ptr<T> elem); 
    void remove(size_t index);
    double totalArea() const;
    void printAll() const;
    size_t size() const;
    std::shared_ptr<T>& get(size_t index);  
};

template<Number T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure);

template<Number T>
std::istream& operator>>(std::istream& is, Figure<T>& figure);

#endif
