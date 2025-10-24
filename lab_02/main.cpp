#include <iostream>
#include "seven.h"

int main() {
    try {
        Seven num1(3,4); 
        Seven num2({4, 2, 5}); 
        Seven num3(2, 6);  
        
        std::cout << "num1: ";
        num1.print(std::cout) << std::endl;
        
        std::cout << "num2: ";
        num2.print(std::cout) << std::endl;
        
        std::cout << "num3: ";
        num3.print(std::cout) << std::endl;
    
        Seven sum = num1.add(num2);
        std::cout << "num1 + num2: ";
        sum.print(std::cout) << std::endl;
        
        Seven diff = num2.subtract(num3);
        std::cout << "num2 - num3: ";
        diff.print(std::cout) << std::endl;
        
        std::cout << "num1 equals num2: " << num1.equals(num2) << std::endl;
        std::cout << "num1 less than num2: " << num1.less(num2) << std::endl;
        std::cout << "num1 greater than num2: " << num1.greater(num2) << std::endl;
        
        Seven num4 = num1.copy();
        std::cout << "Copy of num1: ";
        num4.print(std::cout) << std::endl;
        
        std::cout << "\n--- Перемещающий конструктор ---" << std::endl;
        
        Seven movedNum(std::move(sum));
        std::cout << "movedNum (после перемещения): ";
        movedNum.print(std::cout) << std::endl;
        
        std::cout << "\n--- Обработка исключений ---" << std::endl;

        try {
            Seven errorResult = num3.subtract(num1);
            std::cout << "Результат вычитания (не должно выполниться): ";
            errorResult.print(std::cout) << std::endl;

        } catch (std::exception& e) {
            std::cerr << "Перехвачено исключение: " << e.what() << std::endl;
        }

        Seven validResult = num1.subtract(num3);
        std::cout << "Результат вычитания (успешно): ";
        validResult.print(std::cout) << std::endl;

        std::cout << "\n--- Выход из main() - вызов деструкторов ---" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}