#include "../include/Vehicle.h"
#include "../utils/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Vehicle::Vehicle() {};

Vehicle::Vehicle(string id, const string &brand, const string &model, const string& category, const string &color, const string &transmission,
                 int year, int capacity, int kilometraj, double rentalPricePerDay)
        : id(id), brand(brand), model(model), category(category), color(color), transmission(transmission), year(year), capacity(capacity), kilometraj(kilometraj),
          rentalPricePerDay(rentalPricePerDay) {}


string Vehicle::getId() const {
    return id;
}

string Vehicle::getBrand() const {
    return brand;
}

string Vehicle::getModel() const {
    return model;
}

string Vehicle::getCategory() const {
    return category;
}

string Vehicle::getColor() const {
    return color;
}

string Vehicle::getTransmission() const {
    return transmission;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getCapacity() const {
    return capacity;
}

int Vehicle::getKilometraj() const {
    return kilometraj;
}

double Vehicle::getRentalPricePerDay() const {
    return rentalPricePerDay;
}


void Vehicle::setId(string id) {
    this->id = id;
}

void Vehicle::setBrand(const string &brand) {
    this->brand = brand;
}

void Vehicle::setModel(const string &model) {
    this->model = model;
}

void Vehicle::setCategory(string category) {
    this->category = category;
}

void Vehicle::setColor(const string &color) {
    this->color = color;
}

void Vehicle::setTransmission(const string &transmission) {
    this->transmission = transmission;
}

void Vehicle::setYear(int year) {
    this->year = year;
}

void Vehicle::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Vehicle::setKilometraj(int kilometraj) {
    this->kilometraj = kilometraj;
}

void Vehicle::setRentalPricePerDay(double rentalPricePerDay) {
    this->rentalPricePerDay = rentalPricePerDay;
}

void Vehicle::displayHeader() {
    cout << "\033[1;47m\033[30m"; 
    cout << setw(15) << left << "ID"
         << setw(15) << left << "BRAND"
         << setw(15) << left << "MODEL"
         << setw(15) << left << "CLASS"
         << setw(10) << left << "COLOR"
         << setw(15) << left << "TRANSMISSION"
         << setw(8) << left << "YEAR"
         << setw(15) << left << "CAPACITY"
         << setw(15) << left << "KILOMETRAJ"
         << setw(15) << left << "PRICE (DAY)" << endl;
    cout << "\033[0m"; 
}

void Vehicle::displayInfo() const {
    stringstream ss;
    ss << fixed << setprecision(2) << rentalPricePerDay;
    string rentalPriceString = ss.str();

    cout << setw(15) << left << id
         << setw(15) << left << brand
         << setw(15) << left << model
         << setw(15) << left << category
         << setw(10) << left << color
         << setw(15) << left << transmission
         << setw(8) << left << year
         << setw(15) << left << to_string(capacity) + " pers"
         << setw(15) << left << to_string(kilometraj) + " km"
         << setw(15) << left << rentalPriceString + "/day" << endl;
}

void Vehicle::displayAllCarsAvailableHeader() {
    cout << "\033[1;43m\033[1;30m";

    cout << setw(15) << left << "ID"
         << setw(15) << left << "BRAND"
         << setw(15) << left << "MODEL"
         << setw(10) << left << "COLOR"
         << setw(15) << left << "TRANSMISSION"
         << setw(15) << left << "YEAR"
         << setw(15) << left << "CAPACITY"
         << setw(15) << left << "PRICE (DAY)" << endl;

    cout << "\033[0m";
}

void Vehicle::displayAllCarsAvailable(double price) const {
    ostringstream oss;
    oss << fixed << setprecision(2) << rentalPricePerDay;
    string rentalPriceString = oss.str();
    
    double totalPrice = price * convertStringToDouble(rentalPriceString);
    ostringstream ossTotalPrice;
    ossTotalPrice << fixed << setprecision(2) << totalPrice << "/lei";

    cout << setw(15) << left << id
         << setw(15) << left << brand
         << setw(15) << left << model
         << setw(10) << left << color
         << setw(15) << left << transmission
         << setw(15) << left << year
         << setw(15) << left << to_string(capacity) + " pers"
         << setw(15) << left << ossTotalPrice.str() << endl;
}

void Vehicle::saveToFile(const string &filename, const Vehicle &vehicle) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    file << vehicle.getId() << "," << vehicle.getBrand() << "," << vehicle.getModel() << ","
         << vehicle.getColor() << "," << vehicle.getTransmission() << "," << vehicle.getYear() << ","
         << vehicle.getCapacity() << "," << vehicle.getKilometraj() << "," << vehicle.getRentalPricePerDay() << "," << vehicle.getCategory()  << endl;

    file.close();
}

void Vehicle::saveToFile(const string &filename, const vector<Vehicle> &vehicles) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    for (const auto &vehicle : vehicles) {
        file << vehicle.getId() << "," << vehicle.getBrand() << "," << vehicle.getModel() << ","
             << vehicle.getColor() << "," << vehicle.getTransmission() << "," << vehicle.getYear() << ","
             << vehicle.getCapacity() << "," << vehicle.getKilometraj() << "," << vehicle.getRentalPricePerDay() << "," << vehicle.getCategory() << endl;
    }

    file.close();
}

vector<Vehicle> Vehicle::loadFromFile(const string &filename) {
    vector<Vehicle> vehicles;

    ifstream file(filename);
    if (!file.is_open()) {
        ofstream createFile(filename);
        createFile.close();

        return vehicles;
    }

    vehicles.clear();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 10) {
            string id = tokens[0];
            string brand = tokens[1];
            string model = tokens[2];
            string color = tokens[3];
            string transmission = tokens[4];
            int year = stoi(tokens[5]);
            int capacity = stoi(tokens[6]);
            int kilometraj = stoi(tokens[7]);
            double rentalPricePerDay = stod(tokens[8]);
            string category = tokens[9];

            Vehicle vehicle(id, brand, model, category, color, transmission, year, capacity, kilometraj, rentalPricePerDay);
            vehicles.push_back(vehicle);
        } else {
            cerr << "Error: Invalid line format in file: " << filename << endl;
        }
    }

    file.close();
    return vehicles;
}

void Vehicle::deleteFromFiIe(const string &filename, string idToDelete) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return;
    }

    ofstream outFile("temp.txt"); 
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open temporary file for writing." << endl;
        inFile.close();
        return;
    }

    string line;
    bool deleted = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 10) {
            string id = tokens[0];
            if (id == idToDelete) {
                deleted = true; 
                continue; 
            }
        }
        
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (deleted) {
        cout << "\033[1;32mThe car has been deleted successfully!\033[0m" << endl;

        if (remove(filename.c_str()) != 0) {
            cerr << "Error: Unable to delete file: " << filename << endl;
            return;
        }
        if (rename("temp.txt", filename.c_str()) != 0) {
            cerr << "Error: Unable to rename file." << endl;
        }
    } else {
        
        remove("temp.txt");
        cerr << "Error: Vehicle with ID " << idToDelete << " not found." << endl;
    }
}

void Vehicle::updateInFile(const string &filename, string idToUpdate, const string &newBrand, const string &newModel,
                           const string &newColor, const string& newCategory, const string &newTransmission, int newYear, int newCapacity, int newKilometraj,
                           double newRentalPricePerDay) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open temporary file for writing." << endl;
        inFile.close();
        return;
    }

    string line;
    bool updated = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 10) {
            string id = tokens[0];
            if (id == idToUpdate) {
                tokens[1] = newBrand;
                tokens[2] = newModel;
                tokens[3] = newColor;
                tokens[4] = newTransmission;
                tokens[5] = to_string(newYear);
                tokens[6] = to_string(newCapacity);
                tokens[7] = to_string(newKilometraj);
                tokens[8] = to_string(newRentalPricePerDay);
                tokens[9] = newCategory;
                updated = true;
            }
        }
        
        string updatedLine = tokens[0];
        for (size_t i = 1; i < tokens.size(); ++i) {
            updatedLine += "," + tokens[i];
        }
        outFile << updatedLine << endl;
    }

    inFile.close();
    outFile.close();

    if (updated) {
        if (remove(filename.c_str()) != 0) {
            cerr << "Error: Unable to delete file: " << filename << endl;
            return;
        }
        if (rename("temp.txt", filename.c_str()) != 0) {
            cerr << "Error: Unable to rename file." << endl;
        }
    } else {
        remove("temp.txt");
        cerr << "Error: Vehicle with ID " << idToUpdate << " not found." << endl;
    }
}

Vehicle Vehicle::getVehicleById(const vector<Vehicle> &vehicles, string targetId) {
    for (const auto &vehicle: vehicles) {
        if (vehicle.getId() == targetId) {
            return vehicle;
        }
    }
    
    return Vehicle();
}
