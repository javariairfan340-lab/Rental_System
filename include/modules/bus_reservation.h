#ifndef BUS_RESERVATION_H
#define BUS_RESERVATION_H

#include "structures.h"
#include <vector>

void busReservationMenu();
void displayAvailableBuses();
void bookBusTicket(std::vector<BusTicket>& bookings, int& nextId);
void viewBusBookings(const std::vector<BusTicket>& bookings);
void cancelBusBooking(std::vector<BusTicket>& bookings);
void searchBusBooking(const std::vector<BusTicket>& bookings);
void sortBusBookings(std::vector<BusTicket>& bookings);
void loadBusBookings(std::vector<BusTicket>& bookings, int& nextId);
void saveBusBookings(const std::vector<BusTicket>& bookings);

#endif
