#include "Car.h"
#include "Mechanic.h"
#include "Malfunction.h"
#include "Appointment.h"
#include "Part.h"
#include <iostream>
#include <string>
int main() {
    // Створення об'єктів
    Car car1("Toyota", "Corolla", 2020, "VIN123456789");
    Mechanic mechanic1("John Doe", "General");
    Malfunction malfunction1("Brake failure", 3);
    Appointment appointment1(&car1, &mechanic1, &malfunction1, "2024-03-15");

    // Додавання частин та вартості роботи
    Part part1("Brake Pad", 120.50);
    Part part2("Brake Disc", 89.99);
    appointment1.addPart(part1);
    appointment1.addPart(part2);
    appointment1.setLaborCost(200);

    // Відображення деталей призначення
    appointment1.displayAppointmentDetails();

    return 0;
}
