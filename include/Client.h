#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

using namespace std;

class Client {
private:
    string id;
    string name;
    string address;
    string email;
    string phoneNumber;

public:
    // Constructor
    Client(string id, const string& name, const string& address, const string& email, const string& phoneNumber);

    // Getter methods
    string getId() const;
    string getName() const;
    string getAddress() const;
    string getEmail() const;
    string getPhoneNumber() const;

    // Setter methods
    void setId(string id);
    void setName(const string& name);
    void setAddress(const string& address);
    void setEmail(const string& email);
    void setPhoneNumber(const string& phoneNumber);

    // Method to display client information
    void displayInfo() const;

    // Method to save clients to file
    static void saveToFile(const string& filename, const vector<Client>& clients);

    // Method to load clients from file
    static vector<Client> loadFromFile(const string& filename);
};

#endif //CLIENT_H
