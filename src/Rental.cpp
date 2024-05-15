#include "../include/Rental.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
Rental::Rental(const string& id, const string &startDate, const string &endDate, const string &startTime, const string &endTime, const string& address,
               const Vehicle *rentedVehicle, const Client *rentingClient)
        : id(id), startDate(startDate), endDate(endDate), startTime(startTime), endTime(endTime), address(address),
          rentedVehicle(rentedVehicle), rentingClient(rentingClient) {}

// Getter methods
string Rental::getId() const {
    return id;
}

string Rental::getStartDate() const {
    return startDate;
}

string Rental::getEndDate() const {
    return endDate;
}

string Rental::getStartTime() const {
    return startTime;
}

string Rental::getEndTime() const {
    return endTime;
}

string Rental::getAddress() const {
    return address;
}

string Rental::getComments() const {
    return comments;
}

double Rental::getTotalPrice() const {
    return totalPrice;
}

const Vehicle *Rental::getRentedVehicle() const {
    return rentedVehicle;
}

const Client *Rental::getRentingClient() const {
    return rentingClient;
}

// Setter methods
void Rental::setId(const string& id) {
    this->id = id;
}

void Rental::setStartDate(const string &startDate) {
    this->startDate = startDate;
}

void Rental::setEndDate(const string &endDate) {
    this->endDate = endDate;
}

void Rental::setStartTime(const string &startTime) {
    this->startTime = startTime;
}

void Rental::setEndTime(const string &endTime) {
    this->endTime = endTime;
}

void Rental::setAddress(const string &address) {
    this->address = address;
}

void Rental::setComments(const std::string &comments) {
    this->comments = comments;
}

void Rental::setTotalPrice(double totalPrice) {
    this->totalPrice = totalPrice;
}

void Rental::setRentedVehicle(const Vehicle *rentedVehicle) {
    this->rentedVehicle = rentedVehicle;
}

void Rental::setRentingClient(const Client *rentingClient) {
    this->rentingClient = rentingClient;
}

// Method to display rental information
void Rental::displayInfo() const {
    cout << "Rental ID: " << id << endl;
    cout << "Takeover address: " << address << endl;
    cout << "Takeover date: " << startDate << endl;
    cout << "Delivery date: " << endDate << endl;
    cout << "Takeover time: " << startTime << endl;
    cout << "Delivery time: " << endTime << endl;
    cout << "Total price: " << totalPrice << "/lei" << endl;
    cout << "Car id: " << rentedVehicle->getId() << endl;
    cout << "Brand and Model: " << rentedVehicle->getBrand() + " " + rentedVehicle->getModel() << endl;
    rentingClient->displayInfo();

    if (!comments.empty()) {
        cout << "Comments: " << comments << endl;
    }
}

// Method to save rentals to file
void Rental::saveToFile(const string &filename, const vector<Rental> &rentals) {
    ofstream file(filename, ios_base::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    for (const auto &rental: rentals) {
        file << rental.getId() << "," << rental.getStartDate() << "," << rental.getEndDate() << ","
             << rental.getStartTime() << "," << rental.getEndTime() << "," << rental.getAddress() << "," << to_string(rental.getTotalPrice()) << ","
             << rental.getRentedVehicle()->getId() << "," << rental.getRentingClient()->getId() << endl;
    }

    file.close();
}

void Rental::deleteFromFiIe(const string &filename, string idToDelete, char separator) {
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
        while (getline(ss, token, separator)) {
            tokens.push_back(token);
        }

        if (tokens.size() == 10) {
            string id = tokens[7];
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

// Method to load rentals from file
vector<Rental> Rental::loadFromFile(const string &filename, const vector<Vehicle> &vehicles, const vector<Client> &clients) {
    vector<Rental> loadedRentals;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return loadedRentals;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, startDate, endDate, startTime, endTime, address, totalPrice, rentedVehicleId, rentingClientId;

        if (getline(ss, id, ',') &&
            getline(ss, startDate, ',') &&
            getline(ss, endDate, ',') &&
            getline(ss, startTime, ',') &&
            getline(ss, endTime, ',') &&
            getline(ss, address, ',') &&
            getline(ss, totalPrice, ',') &&
            getline(ss, rentedVehicleId, ',') &&
            getline(ss, rentingClientId, ',')) {

            const Vehicle *rentedVehiclePtr = nullptr;
            const Client *rentingClientPtr = nullptr;

            // Găsim vehiculul închiriat după ID
            for (const auto &vehicle: vehicles) {
                if (vehicle.getId() == rentedVehicleId) {
                    rentedVehiclePtr = &vehicle;
                    break;
                }
            }

            // Găsim clientul care închiriază după ID
            for (const auto &client: clients) {
                if (client.getId() == rentingClientId) {
                    rentingClientPtr = &client;
                    break;
                }
            }

            if (rentedVehiclePtr && rentingClientPtr) {
                Rental rental(id, startDate, endDate, startTime, endTime, address, rentedVehiclePtr, rentingClientPtr);
                rental.setTotalPrice(stod(totalPrice));
                loadedRentals.push_back(rental);
            } else {
                cerr << "Error: Could not find vehicle or client with ID: " << rentedVehicleId << " or " << rentingClientId
                     << endl;
            }
        } else {
            cerr << "Error: Invalid format in line: " << line << endl;
        }
    }

    file.close();

    return loadedRentals;
}

vector<Rental> Rental::loadFromFileStatistics(const string &filename, const vector<Vehicle> &vehicles, const vector<Client> &clients) {
    vector<Rental> loadedRentals;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return loadedRentals;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, startDate, endDate, startTime, endTime, address, totalPrice, rentedVehicleId, rentingClientId, comments;

        if (getline(ss, id, '|') &&
            getline(ss, startDate, '|') &&
            getline(ss, endDate, '|') &&
            getline(ss, startTime, '|') &&
            getline(ss, endTime, '|') &&
            getline(ss, address, '|') &&
            getline(ss, totalPrice, '|') &&
            getline(ss, rentedVehicleId, '|') &&
            getline(ss, rentingClientId, '|') &&
            getline(ss, comments)) {

            const Vehicle *rentedVehiclePtr = nullptr;
            const Client *rentingClientPtr = nullptr;

            // Găsim vehiculul închiriat după ID
            for (const auto &vehicle: vehicles) {
                if (vehicle.getId() == rentedVehicleId) {
                    rentedVehiclePtr = &vehicle;
                    break;
                }
            }

            // Găsim clientul care închiriază după ID
            for (const auto &client: clients) {
                if (client.getId() == rentingClientId) {
                    rentingClientPtr = &client;
                    break;
                }
            }

            if (rentedVehiclePtr && rentingClientPtr) {
                Rental rental(id, startDate, endDate, startTime, endTime, address, rentedVehiclePtr, rentingClientPtr);
                rental.setTotalPrice(stod(totalPrice));
                rental.setComments(comments);
                loadedRentals.push_back(rental);
            } else {
                cerr << "Error: Could not find vehicle or client with ID: " << rentedVehicleId << " or " << rentingClientId
                     << endl;
            }
        } else {
            cerr << "Error: Invalid format in line: " << line << endl;
        }
    }

    file.close();

    return loadedRentals;
}