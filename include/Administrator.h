#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <chrono>

using namespace std;

class Administrator {
private:
    string id;
    string username;
    string password;
    string email;
    bool loggedIn;
    std::chrono::system_clock::time_point lastLoginTime;

public:
    // Constructor
    Administrator();
    Administrator(string id, const string& username, const string& email, const string& password);

    // Getter methods
    string getId() const;
    string getUsername() const;
    string getEmail() const;
    string getPassword() const;

    // Setter methods
    void setId(string id);
    void setUsername(const string& username);
    void setEmail(const string& email);
    void setPassword(const string& password);

    void displayInfo();

    bool isLoggedIn() const;
    void login();
    void logout();
    std::chrono::system_clock::time_point getLastLoginTime() const;

    // Method for administrator authentication
    bool authenticate(const string& email, const string& password) const;

    // Method to save all vehicles to file
    static void saveToFile(const string& filename, const Administrator& admin);

    // Method to load all vehicles from file
    void loadFromFile(const string& filename);

    // Method to check if exist an account in file
    static bool existAccount(const string &filename);

};

#endif // ADMINISTRATOR_H
