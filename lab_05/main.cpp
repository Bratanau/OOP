#include "queue_with_pmr.hpp" 
#include <iostream>

struct Point {
    int x;
    double y;

    // Для тестирования сравнения
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" <, p.x << ", " << p.y << ")";
    }
};

int main() {
    FixedBlockMemoryResource resource;
    
    // Создаем очередь с нашим memory resource
    Queue<Point> queue(&resource);
    
    // Добавляем элементы в очередь
    queue.push({1, 2.5});
    queue.push({10, -3.0});
    queue.push({5, 7.2});
    queue.push({8, 1.1});
    
    std::cout << "Queue content (FIFO order):\n";
    for (const auto& point : queue) {
        std::cout << point << "\n";
    }
    
    std::cout << "\nQueue operations:\n";
    std::cout << "Front: " << queue.front() << "\n";
    std::cout << "Back: " << queue.back() << "\n";
    std::cout << "Size: " << queue.size() << "\n";
    
    // Удаляем первый элемент
    queue.pop();
    std::cout << "\nAfter pop - Front: " << queue.front() << "\n";
    
    // Добавляем еще один элемент
    queue.push({15, 3.14});
    std::cout << "After push - Back: " << queue.back() << "\n";
    
    // Показываем состояние памяти
    std::cout << "\n";
    resource.print_memory_state();
    
    return 0;
}