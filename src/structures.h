#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

// User structure
struct User {
    std::string name;
    std::string email;
    std::string phone;
};

// Car Rental structure
struct CarRental {
    int bookingId;
    User customer;
    std::string carModel;
    std::string carType;
    std::string pickupDate;
    std::string returnDate;
    int days;
    double pricePerDay;
    double totalPrice;
    std::string status; // "Active", "Completed", "Cancelled"
};

// Air Ticket structure
struct AirTicket {
    int bookingId;
    User passenger;
    std::string flightNumber;
    std::string airline;
    std::string from;
    std::string to;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalTime;
    std::string seatClass; // "Economy", "Business", "First"
    int numPassengers;
    double pricePerTicket;
    double totalPrice;
    std::string status;
};

// Bus Ticket structure
struct BusTicket {
    int bookingId;
    User passenger;
    std::string busNumber;
    std::string route;
    std::string from;
    std::string to;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalTime;
    int seatNumber;
    double ticketPrice;
    std::string status;
};

// Train Ticket structure
struct TrainTicket {
    int bookingId;
    User passenger;
    std::string trainNumber;
    std::string trainName;
    std::string from;
    std::string to;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalTime;
    std::string ticketClass; // "Sleeper", "AC", "First Class"
    int seatNumber;
    double ticketPrice;
    std::string status;
};

// Cinema Ticket structure
struct CinemaTicket {
    int bookingId;
    User customer;
    std::string movieName;
    std::string genre;
    std::string showDate;
    std::string showTime;
    std::string theater;
    int numTickets;
    int seatNumbers[10]; // Array for seat numbers (max 10 tickets)
    double pricePerTicket;
    double totalPrice;
    std::string status;
};

#endif
