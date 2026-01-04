#ifndef TRAIN_RESERVATION_H
#define TRAIN_RESERVATION_H

#include "structures.h"
#include <vector>

void trainReservationMenu();
void displayAvailableTrains();
void bookTrainTicket(std::vector<TrainTicket>& bookings, int& nextId);
void viewTrainBookings(const std::vector<TrainTicket>& bookings);
void cancelTrainBooking(std::vector<TrainTicket>& bookings);
void searchTrainBooking(const std::vector<TrainTicket>& bookings);
void sortTrainBookings(std::vector<TrainTicket>& bookings);
void loadTrainBookings(std::vector<TrainTicket>& bookings, int& nextId);
void saveTrainBookings(const std::vector<TrainTicket>& bookings);

#endif
