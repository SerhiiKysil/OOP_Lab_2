#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <ctime>


int calculateRepairTime(const std::string& problem) {
    std::map<std::string, int> repairTimes = {{"Engine not working", 5}, {"Brakes damaged", 2}, {"Electrical problems", 8}};
    if (problem == "unknown") {
        return 2; // Для невідомих проблем час діагностики
    }
    return repairTimes[problem];
}

double calculateServiceCost(const std::string& problem) {
    if (problem == "unknown") {
        return 150; // Вартість діагностики
    }
    // Мапа з типами поломок та вартістю ремонту
    std::map<std::string, double> serviceCosts = {{"Engine not working", 100.0}, {"Brakes damaged", 50.0}, {"Electrical problems", 200.0}};
    return serviceCosts[problem];
}


std::string getRandomProblem(std::vector<std::string>& problems) {
    static std::mt19937 gen(time(nullptr)); // Генератор випадкових чисел
    std::uniform_int_distribution<> distr(0, problems.size() - 1); // Рівномірний розподіл
    return problems[distr(gen)]; // Повертає випадкову проблему
}

class Vehicle {
public:
    std::string type;
    std::string registrationNumber;
    std::string problemDescription;
    int repairTime;
    double serviceCost;

    Vehicle(std::string type, std::string registrationNumber, std::string problemDescription, int repairTime, double serviceCost) :
        type(type), registrationNumber(registrationNumber), problemDescription(problemDescription), repairTime(repairTime), serviceCost(serviceCost) {}

    virtual void displayInfo() const = 0;
    virtual ~Vehicle() = default;

    double getServiceCost() const {
        return serviceCost;
    }

    int getRepairTime() const {
        return repairTime;
    }

    // Діагностика невідомих проблем
    void diagnoseUnknownProblem(std::vector<std::string>& problems) {
        if (this->problemDescription == "unknown") {
            std::string diagnosedProblem = getRandomProblem(problems);
            this->problemDescription = diagnosedProblem;
            this->repairTime += calculateRepairTime(diagnosedProblem); // Додаємо час діагностики
            this->serviceCost += calculateServiceCost(diagnosedProblem); // Додаємо вартість діагностованої проблеми
        }
    }
};


class Car : public Vehicle {
public:
    Car(std::string registrationNumber, std::vector<std::string>& problems) :
        Vehicle("Car", registrationNumber, getRandomProblem(problems), calculateRepairTime(getRandomProblem(problems)), calculateServiceCost(getRandomProblem(problems))) {}

    void displayInfo() const override {
        std::cout << "Vehicle Type: Car, Registration Number: " << registrationNumber 
                    << ", Problem: " << problemDescription << ", Repair Time: " << repairTime << " hours, Service Cost: $" << serviceCost << std::endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string registrationNumber, std::vector<std::string>& problems) :
        Vehicle("Motorcycle", registrationNumber, getRandomProblem(problems), calculateRepairTime(getRandomProblem(problems)), calculateServiceCost(getRandomProblem(problems))) {}

    void displayInfo() const override {
        std::cout << "Vehicle Type: Motorcycle, Registration Number: " << registrationNumber 
                    << ", Problem: " << problemDescription << ", Repair Time: " << repairTime << " hours, Service Cost: $" << serviceCost << std::endl;
    }
};

class Truck : public Vehicle {
public:
    Truck(std::string registrationNumber, std::vector<std::string>& problems) :
        Vehicle("Truck", registrationNumber, getRandomProblem(problems), calculateRepairTime(getRandomProblem(problems)), calculateServiceCost(getRandomProblem(problems))) {}

    void displayInfo() const override {
        std::cout << "Vehicle Type: Truck, Registration Number: " << registrationNumber 
                    << ", Problem: " << problemDescription << ", Repair Time: " << repairTime << " hours, Service Cost: $" << serviceCost << std::endl;
    }
};

class Mechanic {
private:
    std::string name;
    std::string specialization;

public:
    Mechanic(std::string name, std::string specialization) : name(name), specialization(specialization) {}

    void repairVehicle(Vehicle* vehicle) const {
        std::cout << "Mechanic " << name << " is repairing the vehicle with specialization in " << specialization << std::endl;
        
    }
};

class AutoService {
public:
    std::vector<Vehicle*> vehicles;
    std::vector<Mechanic*> mechanics;
    int maxVehicles;
    int totalRepairTime;

public:
    AutoService(int vehicles) : maxVehicles(vehicles), totalRepairTime(0) {}

    bool addVehicle(Vehicle* vehicle) {
        if (vehicles.size() < maxVehicles) {
            vehicles.push_back(vehicle);
            totalRepairTime += vehicle->getRepairTime();
            return true;
        } else {
            std::cout << "No free spaces available in the auto service for new vehicles." << std::endl;
            return false;
        }
    }

    void diagnoseAndRepairVehicles(std::vector<std::string>& problems) {
    std::cout << "Diagnosing and repairing vehicles..." << std::endl;
    for (auto& vehicle : vehicles) {
        vehicle->diagnoseUnknownProblem(problems); // Діагностика невідомих проблем
        // Тут можна додати виклик для механіка, щоб він почав ремонт
    }
}


    bool addMechanic(Mechanic* mechanic) {
        mechanics.push_back(mechanic);
        return true;
    }

    void diagnoseVehicle() const {
        std::cout << "Starting vehicle diagnosis:" << std::endl;
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
        }
    }

    void assignMechanicToRepair(Mechanic* mechanic, Vehicle* vehicle) {
        mechanic->repairVehicle(vehicle);
    }

    double calculateTotalServiceCost() const {
        double totalCost = 0.0;
        for (const auto& vehicle : vehicles) {
            totalCost += vehicle->getServiceCost();
        }
        return totalCost;
    }

    int getTotalRepairTime() const {
        return totalRepairTime;
    }

    void repairVehicles() {
        std::cout << "Repairing vehicles..." << std::endl;
        vehicles.clear();
        totalRepairTime = 0;
    }

    void calculateTotalRepairTime() {
    std::map<std::string, int> repairTimeBySpecialization;

    for (const auto& vehicle : vehicles) {
        // Припустимо, що спеціалізація механіка відповідає типу транспортного засобу
        std::string specialization = vehicle->type;
        if (repairTimeBySpecialization.find(specialization) == repairTimeBySpecialization.end()) {
            repairTimeBySpecialization[specialization] = 0;
        }
        repairTimeBySpecialization[specialization] += vehicle->getRepairTime();
    }

    int totalRepairTime = 0;
    for (const auto& pair : repairTimeBySpecialization) {
        // Обчислення максимального часу ремонту для кожної спеціалізації
        if (pair.second > totalRepairTime) {
            totalRepairTime = pair.second;
        }
    }

    this->totalRepairTime = totalRepairTime;
}
    void displayVehiclesOnService() const {
        if (vehicles.empty()) {
            std::cout << "There are no vehicles on the auto service right now." << std::endl;
        } else {
            std::cout << "Vehicles currently on the auto service:" << std::endl;
            for (const auto& vehicle : vehicles) {
                vehicle->displayInfo();
            }
        }
    }

    ~AutoService() {
        for (auto& vehicle : vehicles) {
            delete vehicle;
        }
        for (auto& mechanic : mechanics) {
            delete mechanic;
        }
    }
};



int main() {

    std::vector<std::string> problems = {"Engine not working", "Brakes damaged", "Electrical problems", "unknown"};
    
    AutoService myService(10);

    // Add mechanics with specializations
    Mechanic* carMechanic = new Mechanic("John", "Car Repair");
    Mechanic* motorcycleMechanic = new Mechanic("Alice", "Motorcycle Repair");
    Mechanic* truckMechanic = new Mechanic("Bob", "Truck Repair");

    myService.addMechanic(carMechanic);
    myService.addMechanic(motorcycleMechanic);
    myService.addMechanic(truckMechanic);

    // Add vehicles to the service with random problems
    myService.addVehicle(new Car("AA1111BB", problems));
    myService.addVehicle(new Motorcycle("AA2222BB", problems));
    myService.addVehicle(new Truck("AA3333BB", problems));

    myService.displayVehiclesOnService();

    // Diagnose vehicles, includes diagnosing unknown problems
    myService.diagnoseAndRepairVehicles(problems);

    // Assign mechanics to repair vehicles
    myService.assignMechanicToRepair(carMechanic, myService.vehicles[0]);
    myService.assignMechanicToRepair(motorcycleMechanic, myService.vehicles[1]);
    myService.assignMechanicToRepair(truckMechanic, myService.vehicles[2]);

    // Calculate and display total service cost
    std::cout << "Total service cost: $" << myService.calculateTotalServiceCost() << std::endl;

    // Calculate and display total repair time
    myService.calculateTotalRepairTime();
    std::cout << "Total repair time: " << myService.getTotalRepairTime() << " hours" << std::endl;

    // Repair vehicles and clear the service
    myService.repairVehicles();

    std::cout << "All vehicles repaired. Auto service is empty." << std::endl;

    return 0;
}
