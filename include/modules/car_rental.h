#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include "structures.h"
#include <vector>

// Function declarations for Car Rental module
void carRentalMenu();
void displayAvailableCars();
void bookCar(std::vector<CarRental>& bookings, int& nextId);
void viewCarBookings(const std::vector<CarRental>& bookings);
void cancelCarBooking(std::vector<CarRental>& bookings);
void searchCarBooking(const std::vector<CarRental>& bookings);
void searchCarByModel(const std::vector<CarRental>& bookings, const std::string& model);
void searchCarById(const std::vector<CarRental>& bookings, int id);
void sortCarBookings(std::vector<CarRental>& bookings);
void loadCarBookings(std::vector<CarRental>& bookings, int& nextId);
void saveCarBookings(const std::vector<CarRental>& bookings);

#endif
