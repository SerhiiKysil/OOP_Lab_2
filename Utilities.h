
#include <string>
#include "Vehicle.h"
#include "Mechanic.h"
#include "Malfunction.h"
#include "Part.h"
#include <vector>
#include <string>
#include <numeric> // Для std::accumulate

class Appointment {
    Vehicle* vehicle;
    Mechanic* mechanic;
    Malfunction* malfunction;
    std::string appointmentDate;
    std::vector<Part> usedParts;
    double laborCost;

public:
    Appointment(Vehicle* vehicle, Mechanic* mechanic, Malfunction* malfunction, const std::string& appointmentDate)
        : vehicle(vehicle), mechanic(mechanic), malfunction(malfunction), appointmentDate(appointmentDate), laborCost(0) {}

    void addPart(const Part& part) {
        usedParts.push_back(part);
    }

    void setLaborCost(double cost) {
        laborCost = cost;
    }

    double calculateTotalCost() const {
        double partsCost = std::accumulate(usedParts.begin(), usedParts.end(), 0.0,
                                            [](double sum, const Part& part) { return sum + part.getPrice(); });
        return partsCost + laborCost;
    }

    void displayAppointmentDetails() const {
        vehicle->displayDetails();
        mechanic->displayInfo();
        malfunction->displayInfo();
        std::cout << "Appointment Date: " << appointmentDate << std::endl;
        for (const auto& part : usedParts) {
            part.displayInfo();
        }
        std::cout << "Labor Cost: $" << laborCost << std::endl;
        std::cout << "Total Cost: $" << calculateTotalCost() << std::endl;
    }
};



