#include "../include/figures.h"
#include <iostream>

using namespace std;

int main() {
    Array<Figure<double>> figures;
    int choice;
    
    do {
        cout << "1. Add Triangle\n";
        cout << "2. Add Hexagon\n";
        cout << "3. Add Octagon\n";
        cout << "4. Print all figures info\n";
        cout << "5. Calculate total area\n";
        cout << "6. Remove figure by index\n";
        cout << "7. Exit\n";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                auto triangle = make_unique<Triangle<double>>();
                cout << "Enter 3 vertices for triangle (x y):\n";
                cin >> *triangle;
                
                if (triangle->isRegular()) {
                    figures.add(move(triangle));
                    cout << "Triangle added!\n";
                } else {
                    cout << "Error: Triangle is not isosceles! Figure not added.\n";
                }
                break;
            }
            case 2: {
                auto hexagon = make_unique<Hexagon<double>>();
                cout << "Enter center coordinates (x y) and radius for hexagon:\n";
                cin >> *hexagon;
                figures.add(move(hexagon));
                cout << "Hexagon added!\n";
                break;
            }
            case 3: {
                auto octagon = make_unique<Octagon<double>>();
                cout << "Enter center coordinates (x y) and radius for octagon:\n";
                cin >> *octagon;
                figures.add(move(octagon));
                cout << "Octagon added!\n";
                break;
            }
            case 4:
                if (figures.size() == 0) {
                    cout << "Array is clean.\n";
                } else {
                    figures.printAll();
                }
                break;
            case 5:
                if (figures.size() == 0) {
                    cout << "No figures in the array.\n";
                } else {
                    double totalArea = figures.totalArea();
                    cout << "Total area of all figures: " << totalArea << "\n";
                }
                break;
            case 6: {
                if (figures.size() == 0) {
                    cout << "No figures to remove.\n";
                } else {
                    size_t index;
                    cout << "Enter index to remove (0-" << figures.size()-1 << "): ";
                    cin >> index;
                    figures.remove(index);
                    cout << "Figure removed!\n";
                }
                break;
            }
            case 7:
                cout << "bye bye.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);
    
    return 0;
}
