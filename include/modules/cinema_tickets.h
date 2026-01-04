#ifndef CINEMA_TICKETS_H
#define CINEMA_TICKETS_H

#include "structures.h"
#include <vector>

void cinemaTicketsMenu();
void displayAvailableMovies();
void bookCinemaTicket(std::vector<CinemaTicket>& bookings, int& nextId);
void viewCinemaBookings(const std::vector<CinemaTicket>& bookings);
void cancelCinemaBooking(std::vector<CinemaTicket>& bookings);
void searchCinemaBooking(const std::vector<CinemaTicket>& bookings);
void sortCinemaBookings(std::vector<CinemaTicket>& bookings);
void loadCinemaBookings(std::vector<CinemaTicket>& bookings, int& nextId);
void saveCinemaBookings(const std::vector<CinemaTicket>& bookings);

#endif
