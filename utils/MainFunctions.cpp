#include "MainFunctions.h"

int readNumericValue(const string &message, const string &errorMessage) {
    int value;
    while (true) {
        cout << message;
        if (!(cin >> value)) {
            printRedMessage(errorMessage);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return value;
}

string input(const string &label) {
    string input;
    cout << label + ": ";
    cin >> input;

    return trimSpaces(input);
};

void displayInfoAboutCar(vector<Vehicle> availableVehicles, string carId, int fullPrice) {
    system("cls");
    cout << endl;
    Vehicle myVehicle = Vehicle::getVehicleById(availableVehicles, carId);
    Vehicle::displayAllCarsAvailableHeader();
    myVehicle.displayAllCarsAvailable(fullPrice);
    cout << endl;
}

// Funcție pentru a converti un șir de caractere într-o structură tm
tm stringToTm(const string &dateStr) {
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%Y-%m-%d"); // Formatul datei poate fi ajustat după nevoie
    return tm;
}

// Funcție pentru a compara două date de tip string
bool compareDatesLessThen(const string &date1, const string &date2) {
    tm tm1 = stringToTm(date1);
    tm tm2 = stringToTm(date2);
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    return time1 < time2;
}

bool compareDatesBiggerThen(const string &date1, const string &date2) {
    tm tm1 = stringToTm(date1);
    tm tm2 = stringToTm(date2);
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    return time1 > time2;
}

vector<Vehicle> findAvailableVehicles(const vector<Vehicle> &vehicles, const vector<Rental> &rentals, const string &startDate,
                                      const string &endDate) {
    vector<Vehicle> availableVehicles;
    vector<Client> clients = Client::loadFromFile("clients.txt");
    vector<Rental> allRentals = Rental::loadFromFileStatistics("allRentals.txt", vehicles, clients);

    for (const auto &vehicle: vehicles) {
        bool isAvailable = true;

        // Verificăm dacă mașina este deja rezervată în perioada cerută
        for (const auto &rental: rentals) {
            if (rental.getRentedVehicle()->getId() == vehicle.getId()) {
                // Verificăm dacă există o suprapunere între perioadele de rezervare
                if (!(compareDatesLessThen(endDate, rental.getStartDate()) ||
                      compareDatesBiggerThen(startDate, rental.getEndDate()))) {
                    // Dacă există suprapunere, mașina nu este disponibilă
                    isAvailable = false;
                    break; // Ieșim din bucla for când găsim o suprapunere
                }
            }
        }

        for (const auto &rental: allRentals) {
            if (rental.getRentedVehicle()->getId() == vehicle.getId()) {
                // Verificăm dacă există o suprapunere între perioadele de rezervare
                if (!(compareDatesLessThen(endDate, rental.getStartDate()) ||
                      compareDatesBiggerThen(startDate, rental.getEndDate()))) {
                    // Dacă există suprapunere, mașina nu este disponibilă
                    isAvailable = false;
                    break; // Ieșim din bucla for când găsim o suprapunere
                }
            }
        }

        if (isAvailable) {
            availableVehicles.push_back(vehicle);
        }
    }


    return availableVehicles;
}
