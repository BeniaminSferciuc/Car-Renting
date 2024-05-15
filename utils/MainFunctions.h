#ifndef PROJECT___POO_MAINFUNCTIONS_H
#define PROJECT___POO_MAINFUNCTIONS_H

#include "../include/Administrator.h"
#include "../include/Vehicle.h"
#include "../include/Client.h"
#include "../include/Rental.h"
#include "../utils/MenuAdmin.h"

#include <iostream>
#include <vector>

using namespace std;

int readNumericValue(const string &message, const string &errorMessage);
string input(const string &label);
void displayInfoAboutCar(vector<Vehicle> availableVehicles, string carId, int fullPrice);
tm stringToTm(const string &dateStr);
bool compareDatesLessThen(const string &date1, const string &date2);
bool compareDatesBiggerThen(const string &date1, const string &date2);
vector<Vehicle> findAvailableVehicles(const vector<Vehicle> &vehicles, const vector<Rental> &rentals, const string &startDate,
                                      const string &endDate);

#endif //PROJECT___POO_MAINFUNCTIONS_H
