

#include <iostream>
#include <string>

class Mechanic {
    std::string name;
    std::string specialization;

public:
    Mechanic(const std::string& name, const std::string& specialization);
    void displayInfo() const;
};

