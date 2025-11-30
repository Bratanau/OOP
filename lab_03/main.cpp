#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

std::unique_ptr<Figure> createFigure(int type) {
    switch (type) {
        case 1:
            return std::make_unique<Trapezoid>();
        case 2:
            return std::make_unique<Rhombus>();
        case 3:
            return std::make_unique<Pentagon>();
        default:
            throw std::invalid_argument("Unknown figure type");
    }
}

void inputFigure(std::unique_ptr<Figure>& fig) {
    std::cout << "Select figure type:\n";
    std::cout << "1. Trapezoid\n";
    std::cout << "2. Rhombus\n";
    std::cout << "3. Pentagon\n";
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    fig = createFigure(choice);
    std::cin >> *fig;
}

void printFigureInfo(const Figure& fig) {
    std::cout << fig << std::endl;
    auto center = fig.getCenter();
    std::cout << "Geometric center: (" << center.first << ", " << center.second << ")" << std::endl;
    std::cout << "Area: " << static_cast<double>(fig) << std::endl;
    std::cout << "--------------------------" << std::endl;
}

double getTotalArea(const std::vector<std::unique_ptr<Figure>>& figures) {
    double total = 0.0;
    for (const auto& fig : figures) {
        if (fig) {
            total += static_cast<double>(*fig);
        }
    }
    return total;
}

void removeFigure(std::vector<std::unique_ptr<Figure>>& figures, int index) {
    if (index < 0 || index >= static_cast<int>(figures.size())) {
        throw std::out_of_range("Index out of range");
    }
    figures.erase(figures.begin() + index);
    std::cout << "Figure at index " << index << " has been removed." << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Figure>> figures;

    char choice;
    do {
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Add a new figure\n";
        std::cout << "2. Print all figures info\n";
        std::cout << "3. Calculate total area\n";
        std::cout << "4. Remove a figure by index\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1': {
                std::unique_ptr<Figure> newFig;
                try {
                    inputFigure(newFig);
                    figures.push_back(std::move(newFig));
                    std::cout << "Figure added successfully!" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case '2': {
                if (figures.empty()) {
                    std::cout << "No figures to display." << std::endl;
                } else {
                    std::cout << "\n=== All Figures ===\n";
                    for (size_t i = 0; i < figures.size(); ++i) {
                        std::cout << "Figure #" << i + 1 << ": ";
                        printFigureInfo(*figures[i]);
                    }
                }
                break;
            }
            case '3': {
                double totalArea = getTotalArea(figures);
                std::cout << "Total area of all figures: " << totalArea << std::endl;
                break;
            }
            case '4': {
                if (figures.empty()) {
                    std::cout << "No figures to remove." << std::endl;
                } else {
                    int index;
                    std::cout << "Enter index of figure to remove (0-based): ";
                    std::cin >> index;
                    try {
                        removeFigure(figures, index);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
                break;
            }
            case '5':
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != '5');

    return 0;
}