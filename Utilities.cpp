

#include <iostream>
#include <string>

class Malfunction {
    std::string description;
    int difficultyLevel;

public:
    Malfunction(const std::string& description, int difficultyLevel);
    void displayInfo() const;
};



