
#pragma once 
#include <string>

class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    std::string vin;

public:
    Vehicle(const std::string& make, const std::string& model, int year, const std::string& vin);
    virtual void displayDetails() const;
    virtual ~Vehicle() {}
};

