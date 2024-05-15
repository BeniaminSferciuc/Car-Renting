#include "../include/Administrator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Constructor
Administrator::Administrator() {}

Administrator::Administrator(string id, const string &username, const string &email, const string &password)
        : id(id), username(username), password(password), email(email) {}

// Getter methods
string Administrator::getId() const {
    return id;
}

string Administrator::getUsername() const {
    return username;
}

string Administrator::getEmail() const {
    return email;
}

string Administrator::getPassword() const {
    return password;
}

// Setter methods
void Administrator::setId(string id) {
    this->id = id;
}

void Administrator::setUsername(const string &username) {
    this->username = username;
}

void Administrator::setEmail(const std::string &email) {
    this->email = email;
}

void Administrator::setPassword(const string &password) {
    this->password = password;
}

void Administrator::displayInfo() {
    cout << setw(10) << left << "ID: " << id << endl;
    cout << setw(10) << left << "Username: " << username << endl;
    cout << setw(10) << left << "Email: " << email << endl;
}

// Method for administrator authentication
bool Administrator::authenticate(const string &email, const string &password) const {
    return (this->email == email && this->password == password);
}

void Administrator::saveToFile(const string &filename, const Administrator &admin) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    file << admin.getId() << "," << admin.getUsername() << "," << admin.getPassword() << "," << admin.getEmail()
         << endl;

    file.close();
}

void Administrator::loadFromFile(const string &filename) {
    ifstream file(filename);

    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        string id_str, username, email, password;

        if (getline(iss, id_str, ',') &&
            getline(iss, username, ',') &&
            getline(iss, password, ',') &&
            getline(iss, email)) {

            *this = Administrator(id_str, username, email, password);
        } else {
            cerr << "Error: Invalid format in file: " << filename << endl;
        }
    }

    file.close();
}

bool Administrator::existAccount(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return false;
    }

    // Verificăm dacă există cel puțin un rând în fișier
    return (file.peek() != ifstream::traits_type::eof());
}

//void Administrator::login() {
//    loggedIn = true;
//    lastLoginTime = std::chrono::system_clock::now();
//}
//
//void Administrator::logout() {
//    loggedIn = false;
//}
//
//bool Administrator::isLoggedIn() const {
//    return loggedIn;
//}
