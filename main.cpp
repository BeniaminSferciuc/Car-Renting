#include "./include/Administrator.h"
#include "./include/Vehicle.h"
#include "./include/Client.h"
#include "./include/Rental.h"
#include "./utils/MenuAdmin.h"
#include "./utils/MainFunctions.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int whoAmI;
    int adminAccount;
    int tracking = 0;
    bool existAccount = false;

    vector<Client> clients;
    vector<Rental> rentals;

    if (Administrator::existAccount("admin.txt")) {
        existAccount = true;
    }

    printYellowMessage("Welcome to our rental service!\n\nPlease select your role:");
    cout << "1 - Administrator\n" << "2 - Client" << endl;

    do {
        cout << "\nHow would you like to proceed? ";
        cin >> whoAmI;

        if (whoAmI != 1 && whoAmI != 2) {
            printRedMessage("Invalid role.");
        }

        if (tracking == 2) {
            cout << "Please enter '1' if you're an admin or '2' if you're a client" << endl;
        };

        tracking++;
    } while (whoAmI != 1 && whoAmI != 2);

    if (whoAmI == 1) { // Admin
        system("cls");
        wrongAnswer:

        printYellowMessage("---- Create an account or login in your account -----");
        cout << "\n1 - Login\n2 - Register" << endl;

        cout << "\nHow would you like to proceed? ";
        cin >> adminAccount;

        if (adminAccount == 1) {
            login:
            string email;
            string password;

            cout << "\nPlease login" << endl;

            auto connectAdmin = Administrator();
            connectAdmin.loadFromFile("admin.txt");

            loginAgain:
            cout << "Email: ";
            cin >> email;
            cin.ignore();
            cout << "Password: ";
            password = getPassword();

            email = trimSpaces(email);
            password = trimSpaces(password);

            if (connectAdmin.authenticate(email, password)) {
                system("cls");
                cout << "\nAuthentication successful! Welcome!\n" << endl;

                Menu();
            } else {
                system("cls");

                cout << "\033[1;31mLogin failed! The credentials you provided are incorrect. Please try again.\033[0m"
                     << endl;
                goto loginAgain;
            }

        } else if (adminAccount == 2) {
            if (existAccount) {
                system("cls");
                printYellowMessage("Already have an account on current device! Redirected to login");
                goto login;
            } else {
                cout << "Create an account here" << endl;
                cout << endl;

                string username = input("Username");
                string email = input("Email");
                string password = input("Password");

                Administrator admin = Administrator("1", username, email, password);
                Administrator::saveToFile("admin.txt", admin);

                goto login;
            }
        } else {
            system("cls");
            printRedMessage("Invalid option!");
            goto wrongAnswer;
        }
    } else if (whoAmI == 2) { // Client
        vector<Vehicle> allVehicles = Vehicle::loadFromFile("vehicles.txt");

        string option;
        system("cls");

        cout << "\033[1;47m\033[1;30m  " << "Rent a car" << "  \033[0m" << endl;
        cout << "Discover the perfect car to suit your needs." << endl;

        do {
            cout << "\n ----- Menu -----\n" << endl;
            cout << "A - Rent a car\n";
            cout << "X - Exit\n";

            cout << "\nChoose an option: ";
            cin >> option;
            option = toupper(option[0]);

            if (option == "A") {
                system("cls");

                string address, takeoverTime, deliveryTime, carId;
                int takeoverYear, takeoverMonth, takeoverDay, deliveryDateYear, deliveryDateMonth, deliveryDateDay;
                bool compareDates, isValid = false;

                cout << "Choose pick up location: ";
                cin.ignore();
                getline(cin, address);

                do {
                    cout << "Please enter takeover date" << endl;
                    do {
                        takeoverYear = readNumericValue("Please enter the year: ",
                                                        "Invalid input. Please enter a valid numeric year.");
                        takeoverMonth = readNumericValue("Please enter the month: ",
                                                         "Invalid input. Please enter a valid numeric month.");
                        takeoverDay = readNumericValue("Please enter the day: ",
                                                       "Invalid input. Please enter a valid numeric day.");

                        if (!isValidDate(takeoverYear, takeoverMonth, takeoverDay)) {
                            cout << "\u001B[1;31mThe entered date is not valid.\u001B[0m" << endl;
                        } else {
                            isValid = true;
                        }
                    } while (!isValid);

                    cout << "Please enter delivery date" << endl;
                    isValid = false;
                    do {
                        cout << "Please enter the year: ";
                        if (!(cin >> deliveryDateYear)) {
                            cout << "\u001B[1;31mInvalid input. Please enter a valid numeric year.\u001B[0m" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "Please enter the month: ";
                        if (!(cin >> deliveryDateMonth)) {
                            cout << "\u001B[1;31mInvalid input. Please enter a valid numeric month.\u001B[0m" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "Please enter the day: ";
                        if (!(cin >> deliveryDateDay)) {
                            cout << "\u001B[1;31mInvalid input. Please enter a valid numeric day.\u001B[0m" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        if (!isValidDate(deliveryDateYear, deliveryDateMonth, deliveryDateDay)) {
                            cout << "\u001B[1;31mThe entered date is not valid.\u001B[0m" << endl;
                        } else {
                            isValid = true;
                        }
                    } while (!isValid);

                    compareDates = isFirstDateBeforeSecondDate(takeoverYear, takeoverMonth, takeoverDay,
                                                               deliveryDateYear, deliveryDateMonth, deliveryDateDay);
                } while (!compareDates);

                string takeoverDate = combineDate(takeoverYear, takeoverMonth, takeoverDay);
                string deliveryDate = combineDate(deliveryDateYear, deliveryDateMonth, deliveryDateDay);

                vector<Client> ourClients = Client::loadFromFile("clients.txt");
                vector<Rental> ourRentals = Rental::loadFromFile("rentals.txt", allVehicles, ourClients);

                vector<Vehicle> availableVehicles = findAvailableVehicles(allVehicles, ourRentals, takeoverDate,
                                                                          deliveryDate);

                do {
                    cout << "Enter takeover time (HH:MM format, 24-hour clock): ";
                    cin >> takeoverTime;
                } while (!isValidTakeoverTime(takeoverTime, takeoverDay));

                do {
                    cout << "Enter delivery time (HH:MM format, 24-hour clock): ";
                    cin >> deliveryTime;
                } while (!isValidDeliveryTime(deliveryTime));

                system("cls");

                int numberOfDays = numberOfDaysBetweenTwoDates(takeoverYear, takeoverMonth, takeoverDay,
                                                               deliveryDateYear,
                                                               deliveryDateMonth, deliveryDateDay);

                printYellowMessage("Choose your perfect car");

                filters:
                cout << "1 - Display all the cars" << endl;
                cout << "2 - Filter by brand\n3 - Filter by category\n4 - Filter by transmission\n";

                vector<Vehicle> filterVehicles;
                short int filter;

                do {
                    cout << "Please choose a filter: ";
                    cin >> filter;

                    if (std::cin.fail() || filter < 1 || filter > 4) {
                        std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                } while(filter < 1 || filter > 4);

                if (filter == 1) {
                    Vehicle::displayAllCarsAvailableHeader();
                    for (const auto &vehicle: availableVehicles) {
                        vehicle.displayAllCarsAvailable(numberOfDays);
                    }
                } else if (filter == 2) {
                    string brand;

                    cout << "Please enter the brand you want: ";
                    cin >> brand;

                    for (auto &vehicle: availableVehicles) {
                        if (vehicle.getBrand() == brand) {
                            filterVehicles.push_back(vehicle);
                        }
                    }

                    cout << "Results: " << endl;

                    if (filterVehicles.empty()) {
                        printRedMessage("Sorry, no vehicles found.");
                        goto filters;
                    }

                    Vehicle::displayAllCarsAvailableHeader();
                    for (auto &vehicle: filterVehicles) {
                        vehicle.displayAllCarsAvailable(numberOfDays);
                    }
                } else if (filter == 3) {
                    int numberCategory;
                    string category;

                    cout << "Categories: " << endl;
                    displayCarCategories();

                    do {
                        cout << "Please enter the number category you want: ";
                        cin >> numberCategory;

                        if (std::cin.fail() || numberCategory < 1 || numberCategory > 8) {
                            std::cout << "Invalid input. Please enter a number between 1 and 8." << std::endl;
                            std::cin.clear(); // Resetați starea de eroare a lui cin
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorați restul liniei
                        }

                    } while(numberCategory < 1 || numberCategory > 8);

                    if (numberCategory == 1) {
                        category = "STANDARD";
                    } else if (numberCategory == 2) {
                        category = "SUV";
                    } else if (numberCategory == 3) {
                        category = "PREMIUM";
                    } else if (numberCategory == 4) {
                        category = "VAN";
                    } else if (numberCategory == 5) {
                        category = "ELECTRIC";
                    } else if (numberCategory == 6) {
                        category = "ECONOMY";
                    } else if (numberCategory == 7) {
                        category = "COMPACT";
                    } else if (numberCategory == 8) {
                        category = "CROSSOVER";
                    }

                    for (auto &vehicle: availableVehicles) {
                        if (vehicle.getCategory() == category) {
                            filterVehicles.push_back(vehicle);
                        }
                    }

                    cout << "Results: " << endl;

                    Vehicle::displayAllCarsAvailableHeader();
                    for (auto &vehicle: filterVehicles) {
                        vehicle.displayAllCarsAvailable(numberOfDays);
                    }
                } else if (filter == 4) {
                    string transmission;
                    short int numberTransmission;

                    cout << "1 - Automatic\n2 - Manual" << endl;

                    do {
                        cout << "Please enter the number of transmission you want: ";
                        cin >> numberTransmission;

                        if (std::cin.fail() || numberTransmission < 1 || numberTransmission > 2) {
                            std::cout << "Invalid input. Please enter a number between 1 and 2." << std::endl;
                            std::cin.clear(); // Resetați starea de eroare a lui cin
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorați restul liniei
                        }

                    } while(numberTransmission < 1 || numberTransmission > 2);

                    if (numberTransmission == 1) {
                        transmission = "Automatic";
                    } else if (numberTransmission == 2) {
                        transmission = "Manual";
                    }

                    for (auto &vehicle: availableVehicles) {
                        if (vehicle.getTransmission() == transmission) {
                            filterVehicles.push_back(vehicle);
                        }
                    }

                    cout << "Results: " << endl;

                    Vehicle::displayAllCarsAvailableHeader();
                    for (auto &vehicle: filterVehicles) {
                        vehicle.displayAllCarsAvailable(numberOfDays);
                    }
                }

                do {
                    cout << "\nPlease enter the id of the car: ";
                    cin >> carId;

                    if (cin.fail()) {
                        cout << "\033[1;31mInvalid input. Please enter a valid numeric ID.\033[0m" << endl;

                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    if (!isCarIdAvailable(carId, availableVehicles)) {
                        cout << "\033[1;31mWrong ID. Please enter a valid ID.\033[0m" << endl;
                    }
                } while (!isCarIdAvailable(carId, availableVehicles));

                displayInfoAboutCar(availableVehicles, carId, numberOfDays);

                string firstname = input("Please enter your firstname");
                string lastname = input("Please enter your lastname");
                string email = input("Please enter your email");
                string phoneNumber = input("Please enter your phone number");

                string fullname = firstname + " " + lastname;

                Vehicle clientVehicle = Vehicle::getVehicleById(availableVehicles, carId);
                Client ourClient(generateUniqueId(), fullname, address, email, phoneNumber);

                clients.push_back(ourClient);

                Rental rental(generateUniqueId(), takeoverDate, deliveryDate, takeoverTime, deliveryTime, address,
                              &clientVehicle, &ourClient);

                Vehicle myVehicle = Vehicle::getVehicleById(availableVehicles, carId);
                double fullPrice = numberOfDays * myVehicle.getRentalPricePerDay();

                rental.setTotalPrice(fullPrice);
                rentals.push_back(rental);

                int confirm;
                cout << "Please confirm transaction" << endl;
                cout << "Yes - 1\nNo - 2\n";
                cin >> confirm;

                if (confirm == 1) {
                    cout << "Payment successfully" << endl;

                    Client::saveToFile("clients.txt", clients);
                    Rental::saveToFile("rentals.txt", rentals);
                } else {
                    printYellowMessage("You just cancel the transaction!");
                }
            } else if (option == "X") {
                break;
            }
        } while (true);
    }

    return 0;
}
