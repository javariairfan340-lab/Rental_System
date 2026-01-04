#ifndef AIR_TICKETING_H
#define AIR_TICKETING_H

#include "structures.h"
#include <vector>

void airTicketingMenu();
void displayAvailableFlights();
void bookFlight(std::vector<AirTicket>& bookings, int& nextId);
void viewFlightBookings(const std::vector<AirTicket>& bookings);
void cancelFlightBooking(std::vector<AirTicket>& bookings);
void searchFlightBooking(const std::vector<AirTicket>& bookings);
void searchFlightByDestination(const std::vector<AirTicket>& bookings, const std::string& destination);
void searchFlightById(const std::vector<AirTicket>& bookings, int id);
void sortFlightBookings(std::vector<AirTicket>& bookings);
void loadFlightBookings(std::vector<AirTicket>& bookings, int& nextId);
void saveFlightBookings(const std::vector<AirTicket>& bookings);

#endif
