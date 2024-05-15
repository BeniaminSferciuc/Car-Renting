#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>

using namespace std;

class Vehicle {
private:
    string id;
    string brand;
    string model;
    string color;
    string transmission;
    string category;
    int year;
    int capacity;
    int kilometraj;
    double rentalPricePerDay;
public:
    // Constructor
    Vehicle();
    Vehicle(string id, const string &brand, const string &model, const string& category, const string &color, const string &transmission, int year,
            int capacity, int kilometraj, double rentalPricePerDay);

    // Getter methods
    string getId() const;
    string getBrand() const;
    string getModel() const;
    string getCategory() const;
    string getColor() const;
    string getTransmission() const;
    int getYear() const;
    int getCapacity() const;
    int getKilometraj() const;
    double getRentalPricePerDay() const;

    // Setter methods
    void setId(string id);
    void setBrand(const string &brand);
    void setModel(const string &model);
    void setCategory(string category);
    void setColor(const string &color);
    void setTransmission(const string &transmission);
    void setYear(int year);
    void setCapacity(int capacity);
    void setKilometraj(int kilometraj);
    void setRentalPricePerDay(double rentalPricePerDay);

    // Other methods
    static void displayHeader();
    void displayInfo() const;
    void displayAllCarsAvailable(double price) const;
    static void displayAllCarsAvailableHeader();
    static void saveToFile(const string &filename, const Vehicle &vehicle);
    static void saveToFile(const string &filename, const vector<Vehicle> &vehicles);
    static vector<Vehicle> loadFromFile(const string &filename);
    static void deleteFromFiIe(const string &filename, string idToDelete);
    static void updateInFile(const string &filename, string idToUpdate, const string &newBrand, const string &newModel, const string& newCategory,
                             const string &newColor, const string &newTransmission, int newYear, int newCapacity, int kilometraj,
                             double newRentalPricePerDay);

    static Vehicle getVehicleById(const vector<Vehicle>& vehicles, string targetId);
};

#endif // VEHICLE_H
