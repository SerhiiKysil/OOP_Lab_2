

#include <iostream>
#include <string>

class Part {
    std::string name;
    double price;

public:
    Part(const std::string& name, double price);
    void displayInfo() const;
    double getPrice() const;
};


