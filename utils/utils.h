#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cctype>
#include <conio.h>
#include <chrono>
#include <vector>
#include <iomanip>

#include "../include/Vehicle.h"

using namespace std;
using namespace chrono;

void printRedMessage(const std::string& message);
void printYellowMessage(const std::string& message);
string trimSpaces(const std::string& str);
string generateUniqueId();
string getPassword();
string convertNumberToCategory(int number);
bool isCarIdAvailable(string carId, const vector<Vehicle>& availableVehicles);
bool isValidDate(int year, int month, int day);
string combineDate(int day, int month, int year);
bool isFirstDateBeforeSecondDate(int year1, int month1, int day1, int year2, int month2, int day2);
bool isValidTakeoverTime(const string& timeString, int currentDay);
bool isValidDeliveryTime(const string& timeString);
int numberOfDaysBetweenTwoDates(int year1, int month1, int day1, int year2, int month2, int day2);
double convertStringToDouble(const std::string& str);
void displayAllVehicles(const vector<Vehicle>& vehicles);
void displayCarCategories();

#endif // UTILS_H
