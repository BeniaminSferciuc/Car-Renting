#include "./utils.h"
#include "../include/Rental.h"
#include <fstream>

using namespace std;

void displayMenu() {
    cout << "\n ----- Menu -----\n" << endl;
    cout << "A - All cars in system\n";
    cout << "C - All cars rented\n";
    cout << "D - Add a new car to the system\n";
    cout << "E - Update a car from the system\n";
    cout << "F - Delete a car from the system\n";
    cout << "G - See your clients\n";
    cout << "H - See all old rentals\n";
    cout << "I - Rent the customer's car\n";
    cout << "J - Pick up the car\n";
    cout << "X - Exit\n";

    cout << "\nChoose an option: ";
}

char getOption() {
    string option;

    cin >> option;
    return toupper(option[0]);
}

void deleteVehicle() {
    string carId;

    cout << "Please enter the id of the car: ";
    cin >> carId;

    Vehicle::deleteFromFiIe("vehicles.txt", carId);
}

void displayAllRentals(const string& filename) {
    vector<Vehicle> vehicles = Vehicle::loadFromFile("vehicles.txt");
    vector<Client> clients = Client::loadFromFile("clients.txt");
    vector<Rental> rentals;

    if (filename == "statisticsRentals.txt") {
        rentals = Rental::loadFromFileStatistics(filename, vehicles, clients);
    } else {
        rentals = Rental::loadFromFile(filename, vehicles, clients);
    }


    if (!rentals.empty()) {
        for (auto &rental: rentals) {
            rental.displayInfo();
            cout << "---------------------------------" << endl;
        }
    } else {
        printYellowMessage("No rentals!");
    }
}

void displayAllClients() {
    vector<Client> clients = Client::loadFromFile("clients.txt");

    for (auto &client: clients) {
        client.displayInfo();
        cout << "---------------------------------" << endl;
    }
}

void rentCarToClient() {
    vector<Rental> currentRentals;
    vector<Vehicle> vehicles = Vehicle::loadFromFile("vehicles.txt");
    vector<Client> clients = Client::loadFromFile("clients.txt");
    vector<Rental> rentals = Rental::loadFromFile("rentals.txt", vehicles, clients);

    system("cls");
    printYellowMessage("Rent the customer's car");
    size_t length = rentals.size();

    (length == 0) ? cout << "" : cout << "All cars in the list of renting:" << endl;

    for (auto &rental : rentals) {
        rental.displayInfo();
        cout << "---------------------------------" << endl;
    }

    string carId, commentsAboutCar;
    bool validCarId = false;

    if (length != 0) {
        do {
            cout << "Please enter the car id: ";
            cin >> carId;

            for (auto &rental : rentals) {
                if (rental.getRentedVehicle()->getId() == carId) {
                    validCarId = true;
                    currentRentals.push_back(rental);
                    break;
                }
            }

            if (!validCarId) {
                printRedMessage("Wrong id");
            }
        } while (!validCarId);

        cout << "Please enter comments about car: ";
        cin.ignore();
        getline(cin, commentsAboutCar);

        ofstream file("allRentals.txt", ios::app);
        ofstream statisticsFile("statisticsRentals.txt", ios::app);

        file << currentRentals[0].getId() << "|" << currentRentals[0].getStartDate() << "|" << currentRentals[0].getEndDate() << "|"
             << currentRentals[0].getStartTime() << "|" << currentRentals[0].getEndTime() << "|" << currentRentals[0].getAddress() << "|" << to_string(currentRentals[0].getTotalPrice()) << "|"
             << currentRentals[0].getRentedVehicle()->getId() << "|" << currentRentals[0].getRentingClient()->getId() << "|" << commentsAboutCar << endl;

        statisticsFile << currentRentals[0].getId() << "|" << currentRentals[0].getStartDate() << "|" << currentRentals[0].getEndDate() << "|"
                       << currentRentals[0].getStartTime() << "|" << currentRentals[0].getEndTime() << "|" << currentRentals[0].getAddress() << "|" << to_string(currentRentals[0].getTotalPrice()) << "|"
                       << currentRentals[0].getRentedVehicle()->getId() << "|" << currentRentals[0].getRentingClient()->getId() << "|" << commentsAboutCar << endl;

        Rental::deleteFromFiIe("rentals.txt", currentRentals[0].getId(), ',');
    } else {
        printYellowMessage("Doesn't exist any rentals!");
    }
}

void Menu() {
    system("cls");
    string option;
    Menu:
    do {
        displayMenu();
        option = getOption();

        if (option == "A") {
            system("cls");
            displayAllVehicles(Vehicle::loadFromFile("vehicles.txt"));
        } else if (option == "C") {
            system("cls");
            displayAllRentals("rentals.txt");
        } else if (option == "D") {
            system("cls");
            cout << "New car" << endl;

            string brand, model, color, transmission;
            int category, kilometraj;
            short int year = 0;
            short int capacity = 0;
            double pricePerDay = 0;

            cout << "Please enter the brand: ";
            cin.ignore();
            getline(cin, brand);

            cout << "Please enter the model: ";
            getline(cin, model);

            cout << "Please enter the number of kilometers: ";
            cin >> kilometraj;

            do {
                system("cls");
                cout << "Please enter the category of the vehicle:" << endl;
                displayCarCategories();
                cout << "Please enter a number to select the vehicle category: ";

                cin >> category;

                if (cin.fail() || category < 1 || category > 8) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number between 1 and 8." << endl;
                }
            } while (category < 1 || category > 8);

            string selectedCategory = convertNumberToCategory(category);

            cout << "What color is the vehicle? ";
            cin.ignore();
            getline(cin, color);

            cout << "Is the transmission automatic or manual? ";
            getline(cin, transmission);

            do {
                cout << "What year was the vehicle manufactured? ";
                if (!(cin >> year)) {
                    cout << "\033[1;31mInvalid input. Please enter a valid year.\033[0m" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            do {
                cout << "How many seats does the vehicle have? ";
                if (!(cin >> capacity)) {
                    cout << "\033[1;31mInvalid input. Please enter a valid year.\033[0m" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            do {
                cout << "Please enter the daily rental price: ";
                if (!(cin >> pricePerDay)) {
                    cout << "\033[1;31mInvalid input. Please enter a valid year.\033[0m" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            auto vehicle = new Vehicle(generateUniqueId(), brand, model, selectedCategory, color, transmission, year,
                                       capacity, kilometraj, pricePerDay);
            Vehicle::saveToFile("vehicles.txt", *vehicle);
        } else if (option == "E") {
            string brand, model, color, transmission, carId;
            short int year = 0;
            short int capacity = 0;
            double pricePerDay = 0;
            int category, kilometraj;

            cout << "Please enter the id of the car: ";
            cin >> carId;

            vector<Vehicle> allVehicles = Vehicle::loadFromFile("vehicles.txt");
            Vehicle foundVehicle = Vehicle::getVehicleById(allVehicles, carId);
            Vehicle::displayHeader();
            foundVehicle.displayInfo();

            cout << "Please enter the brand: ";
            cin >> brand;
            cout << "Please enter the model: ";
            cin >> model;
            cout << "Please enter the number of kilometers: ";
            cin >> kilometraj;

            do {
                cout << "Please enter the category of the vehicle:" << endl;
                cout << "1. STANDARD" << endl;
                cout << "2. SUV" << endl;
                cout << "3. PREMIUM" << endl;
                cout << "4. VAN" << endl;
                cout << "5. ELECTRIC" << endl;
                cout << "6. ECONOMY" << endl;
                cout << "7. COMPACT" << endl;
                cout << "8. CROSSOVER" << endl;
                cout << "Please enter a number to select the vehicle category: ";

                cin >> category;

                if (category < 1 || category > 8) {
                    cout << "Invalid category number. Please enter a number between 1 and 8." << endl;
                }
            } while (category < 1 || category > 8);

            string selectedCategory = convertNumberToCategory(category);

            cout << "What color is the vehicle? ";
            cin >> color;
            cout << "Is the transmission automatic or manual? ";
            cin >> transmission;

            do {
                cout << "What year was the vehicle manufactured? ";
                if (!(cin >> year)) {
                    cout << "Invalid input. Please enter a valid year." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            do {
                cout << "How many seats does the vehicle have? ";
                if (!(cin >> capacity)) {
                    cout << "Invalid input. Please enter a valid year." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            do {
                cout << "Please enter the daily rental price: ";
                if (!(cin >> pricePerDay)) {
                    cout << "Invalid input. Please enter a valid year." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (year <= 0);

            Vehicle::updateInFile("vehicles.txt", carId, brand, model, selectedCategory, color, transmission, year,
                                  capacity, kilometraj,
                                  pricePerDay);
        } else if (option == "F") {
            deleteVehicle();
        } else if (option == "G") {
            system("cls");
            printYellowMessage("All old clients");

            displayAllClients();
        } else if (option == "H") {
            system("cls");
            printYellowMessage("All rentals");
            displayAllRentals("statisticsRentals.txt");
        } else if (option == "I") {
            rentCarToClient();
        } else if (option == "J") {
            system("cls");
            printYellowMessage("Check the car");

            vector<Vehicle> vehicles = Vehicle::loadFromFile("vehicles.txt");
            vector<Client> clients = Client::loadFromFile("clients.txt");
            vector<Rental> rentals = Rental::loadFromFileStatistics("allRentals.txt", vehicles, clients);

            for (auto &rental : rentals) {
                rental.displayInfo();
                cout << "---------------------------------" << endl;
            }

            string carId;
            int checkCarOption;
            bool validCarId = false;

            cout << "What do you want to do? " << endl;
            cout << "1 - Check and take the car" << endl;
            cout << "2 - Go back" << endl;
            cin >> checkCarOption;

            if (checkCarOption == 1) {
                do {
                    cout << "Please enter the car id: ";
                    cin >> carId;

                    for (auto &rental : rentals) {
                        if (rental.getRentedVehicle()->getId() == carId) {
                            validCarId = true;
                            Rental::deleteFromFiIe("allRentals.txt", carId, '|');
                            break;
                        }
                    }

                    if (!validCarId) {
                        printRedMessage("Wrong id");
                    }
                } while (!validCarId);
            } else if (checkCarOption == 2) {
                goto Menu;
            }
        } else if (option == "X") {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid option! Please choose a valid option." << endl;
        }

    } while (true);
}

