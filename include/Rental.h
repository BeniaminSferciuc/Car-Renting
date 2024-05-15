#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include "Client.h"

using namespace std;

class Rental {
private:
    string id;
    string startDate;
    string endDate;
    string startTime;
    string endTime;
    string address;
    string comments;
    double totalPrice;
    const Vehicle* rentedVehicle;
    const Client* rentingClient;

public:
    // Constructor
    Rental(const string& id, const string& startDate, const string& endDate, const string& startTime, const string& endTime, const string& address, const Vehicle* rentedVehicle, const Client* rentingClient);

    // Getter methods
    string getId() const;
    string getStartDate() const;
    string getEndDate() const;
    string getStartTime() const;
    string getEndTime() const;
    string getAddress() const;
    string getComments() const;
    double getTotalPrice() const;
    const Vehicle* getRentedVehicle() const;
    const Client* getRentingClient() const;

    // Setter methods
    void setId(const string& id);
    void setStartDate(const string& startDate);
    void setEndDate(const string& endDate);
    void setStartTime(const string& startTime);
    void setEndTime(const string& endTime);
    void setAddress(const string& address);
    void setComments(const string& comments);
    void setTotalPrice(double totalPrice);
    void setRentedVehicle(const Vehicle* rentedVehicle);
    void setRentingClient(const Client* rentingClient);

    // Method to display rental information
    void displayInfo() const;

    // Method to save rentals to file
    static void saveToFile(const string& filename, const vector<Rental>& rentals);

    // Method to load rentals from file
    static vector<Rental> loadFromFile(const string& filename, const vector<Vehicle>& vehicles, const vector<Client>& clients);
    static vector<Rental> loadFromFileStatistics(const string &filename, const vector<Vehicle> &vehicles, const vector<Client> &clients);
    static void deleteFromFiIe(const string &filename, string idToDelete, char separator);
};

#endif // RENTAL_H
