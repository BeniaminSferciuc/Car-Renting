#include "../include/Client.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
Client::Client(string id, const string& name, const string& address, const string& email, const string& phoneNumber)
        : id(id), name(name), address(address), email(email), phoneNumber(phoneNumber) {}

// Getter methods
string Client::getId() const {
    return id;
}

string Client::getName() const {
    return name;
}

string Client::getAddress() const {
    return address;
}

string Client::getEmail() const {
    return email;
}

string Client::getPhoneNumber() const {
    return phoneNumber;
}

// Setter methods
void Client::setId(string id) {
    this->id = id;
}

void Client::setName(const string& name) {
    this->name = name;
}

void Client::setAddress(const string& address) {
    this->address = address;
}

void Client::setEmail(const string& email) {
    this->email = email;
}

void Client::setPhoneNumber(const string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

// Method to display client information
void Client::displayInfo() const {
    cout << "Client id: " << id << endl;
    cout << "Fullname: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Email address: " << email << endl;
    cout << "Phone Number: " << phoneNumber << endl;
}

// Method to save clients to file
void Client::saveToFile(const string& filename, const vector<Client>& clients) {
    ofstream file(filename, ios_base::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    for (const auto& client : clients) {
        file << client.getId() << "," << client.getName() << "," << client.getAddress() << "," << client.getEmail() << "," << client.getPhoneNumber() << endl;
    }

    file.close();
}

// Method to load clients from file
vector<Client> Client::loadFromFile(const string& filename) {
    vector<Client> loadedClients;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return loadedClients;
    }

    loadedClients.clear();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            string idFromFile = tokens[0];
            string name = tokens[1];
            string address = tokens[2];
            string email = tokens[3];
            string phoneNumber = tokens[4];

            loadedClients.emplace_back(idFromFile, name, address, email, phoneNumber);
        } else {
            cerr << "Error: Invalid line format in file: " << filename << endl;
        }
    }

    file.close();

    return loadedClients;
}
