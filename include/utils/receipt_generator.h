#ifndef RECEIPT_GENERATOR_H
#define RECEIPT_GENERATOR_H

#include "structures.h"
#include <string>

// PDF Receipt Generation Functions
void generateCarRentalReceipt(const CarRental& booking);
void generateAirTicketReceipt(const AirTicket& booking);
void generateBusTicketReceipt(const BusTicket& booking);
void generateTrainTicketReceipt(const TrainTicket& booking);
void generateCinemaTicketReceipt(const CinemaTicket& booking);

// Helper function to create receipts directory
void ensureReceiptsDirectory();

#endif
