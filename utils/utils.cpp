#include "utils.h"

void printRedMessage(const string &message) {
    cout << "\033[1;31m" << message << "\033[0m" << endl;
}

void printYellowMessage(const string &message) {
    cout << "\033[1;33m" << message << "\033[0m" << endl;
}

string trimSpaces(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == string::npos || last == string::npos)
        return "";

    return str.substr(first, last - first + 1);
};

string generateUniqueId() {
    static int counter = 0;
    auto now = chrono::system_clock::now();
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count() % 10000000; // Limităm la 8 cifre

    // Dacă am avut o nouă secundă, resetăm contorul
    static auto last = now;
    if (now - last >= chrono::seconds(1)) {
        counter = 0;
        last = now;
    }

    // Combinație între valoarea timpului în milisecunde și un contor
    return to_string(value * 100 + counter++);
}

string getPassword() {
    string password;
    char ch;

    // Citim caracterele unul câte unul până când apăsăm Enter
    while ((ch = _getch()) != '\r' && ch != '\n') {
        if (ch == '\b') { // Dacă este apăsată tasta Backspace
            if (!password.empty()) {
                // Ștergem ultimul caracter din parolă și de pe ecran
                password.pop_back();
                cout << "\b \b"; // Ștergem un caracter și mutăm cursorul înapoi
            }
        } else {
            // Afisam un asterix în locul caracterului introdus
            password += ch;
            cout << '*';
        }
    }
    cout << endl; // Adaugăm un sfârșit de linie după ce am terminat de citit parola
    return password;
}

string convertNumberToCategory(int number) {
    switch (number) {
        case 1:
            return "STANDARD";
        case 2:
            return "SUV";
        case 3:
            return "PREMIUM";
        case 4:
            return "VAN";
        case 5:
            return "ELECTRIC";
        case 6:
            return "ECONOMY";
        case 7:
            return "COMPACT";
        case 8:
            return "CROSSOVER";
        default:
            return "Unknown";
    }
}

bool isCarIdAvailable(string carId, const vector<Vehicle> &availableVehicles) {
    for (const auto &vehicle: availableVehicles) {
        if (vehicle.getId() == carId) {
            return true; // ID-ul mașinii există deja
        }
    }
    return false; // ID-ul mașinii nu există
}

bool isValidDate(int year, int month, int day) {
    // Verificam daca anul este mai mare sau egal cu anul curent
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    if (year < currentYear) {
        printRedMessage("Year must be at least the current year.");
        return false;
    }
    // If the year is equal to the current year, check the month
    if (year == currentYear && month < currentMonth) {
        printRedMessage("Month must be at least the current month.");
        return false;
    }
    // If the year and month are equal to the current ones, check the day
    if (year == currentYear && month == currentMonth && day < currentDay) {
        printRedMessage("Day must be at least the current day.");
        return false;
    }

    // Check if the month is between 1 and 12
    if (month < 1 || month > 12) {
        printRedMessage("Month must be between 1 and 12.");
        return false;
    }

    // Verificam daca ziua este in intervalul corect pentru fiecare luna
    int daysInMonth;
    switch (month) {
        case 2: // Februarie
            // Verificam daca este an bisect
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11: // Aprilie, Iunie, Septembrie, Noiembrie
            daysInMonth = 30;
            break;
        default: // Celelalte luni
            daysInMonth = 31;
            break;
    }

    if (day < 1 || day > daysInMonth) {
        printRedMessage("Day must be between 1 and the number of days in the respective month.");
        return false;
    }

    return true;
}

string combineDate(int day, int month, int year) {
    stringstream ss;
    // Folosim setw și setfill pentru a asigura că zilele și lunile sunt afișate cu două cifre
    ss << setw(2) << setfill('0') << day << "-" << setw(2) << setfill('0') << month << "-" << year;
    return ss.str();
}

bool isFirstDateBeforeSecondDate(int year1, int month1, int day1, int year2, int month2, int day2) {
    if (year1 < year2) {
        return true;
    } else if (year1 == year2) {
        if (month1 < month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 < day2) {
                return true;
            }
        }
    }

    cout << "\033[1;31mDelivery date must be after takeover date!\033[0m" << endl;

    return false;
}

bool isValidDeliveryTime(const string &timeString) {
    int hours, minutes;
    char colon;
    stringstream ss(timeString);
    ss >> hours >> colon >> minutes;

    // Check if the format is correct and if hours and minutes are within valid ranges
    if (ss.fail() || colon != ':' || hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        printRedMessage("Time format is invalid. Please use HH:MM format (24-hour clock).");
        return false;
    }

    // Check if minutes are valid (0 or 30)
    if (minutes != 0 && minutes != 30) {
        printRedMessage("Minutes must be either 00 or 30.");
        return false;
    }

    return true;
}

bool isValidTakeoverTime(const string &timeString, int currentDay) {
    int hours, minutes;
    char colon;
    stringstream ss(timeString);
    ss >> hours >> colon >> minutes;

    // Get current time
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;

    // Check if the format is correct and if hours and minutes are within valid ranges
    if (ss.fail() || colon != ':' || hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        printRedMessage("Time format is invalid. Please use HH:MM format (24-hour clock).");
        return false;
    }

    // Check if minutes are valid (0 or 30)
    if (minutes != 0 && minutes != 30) {
        printRedMessage("Minutes must be either 00 or 30.");
        return false;
    }

    // Check if the entered time is less than 5 hours from the current time
    if (currentDay == localTime->tm_mday) {
        // Check if the entered time is in the past
        if (hours < currentHour || (hours == currentHour && minutes < currentMinute)) {
            printRedMessage("The time cannot be in the past.");
            return false;
        }

        if (hours - currentHour < 5) {
            printYellowMessage("Please choose a time at least 5 hours from now for vehicle preparation.");
            return false;
        }

        if (hours - currentHour == 5 && minutes < currentMinute) {
            printYellowMessage("Please note that this may not allow sufficient time for vehicle preparation.");
        }
    }

    return true;
}

// Funcție pentru a verifica dacă un an este bisect
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Funcție pentru a obține numărul de zile dintr-o lună
int daysInMonth(int year, int month) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int numberOfDaysBetweenTwoDates(int year1, int month1, int day1, int year2, int month2, int day2) {
    int days = 0;

    // Parcurgem fiecare an între cele două date
    for (int year = year1; year <= year2; ++year) {
        int startMonth = (year == year1) ? month1 : 1; // Luna de început pentru primul an
        int endMonth = (year == year2) ? month2 : 12;  // Luna de sfârșit pentru ultimul an

        // Parcurgem fiecare lună din anul curent
        for (int month = startMonth; month <= endMonth; ++month) {
            int startDay = (year == year1 && month == month1) ? day1 : 1; // Ziua de început pentru prima lună
            int endDay = (year == year2 && month == month2) ? day2 : daysInMonth(year, month); // Ziua de sfârșit pentru ultima lună

            // Adăugăm numărul de zile din fiecare lună
            days += endDay - startDay + 1;
        }
    }

    return days;
}

double convertStringToDouble(const string& str) {
    string num;
    for (char c : str) {
        if (c != ',') {
            num += c;
        }
    }
    istringstream iss(num);
    double result;
    iss >> result;
    return result;
}

void displayAllVehicles(const vector<Vehicle>& vehicles) {
    cout << "\n----- All vehicles ----\n" << endl;
    Vehicle::displayHeader();
    for (const auto& vehicle : vehicles) {
        vehicle.displayInfo();
    }
}

void displayCarCategories() {
    cout << "1 - STANDARD" << endl;
    cout << "2 - SUV" << endl;
    cout << "3 - PREMIUM" << endl;
    cout << "4 - VAN" << endl;
    cout << "5 - ELECTRIC" << endl;
    cout << "6 - ECONOMY" << endl;
    cout << "7 - COMPACT" << endl;
    cout << "8 - CROSSOVER" << endl;
}

