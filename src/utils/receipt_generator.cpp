#include "receipt_generator.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

const string RECEIPTS_DIR = "receipts/";

// Ensure receipts directory exists
void ensureReceiptsDirectory() {
    struct stat info;
    if (stat(RECEIPTS_DIR.c_str(), &info) != 0) {
        // Directory doesn't exist, create it
        #ifdef _WIN32
            mkdir(RECEIPTS_DIR.c_str());
        #else
            mkdir(RECEIPTS_DIR.c_str(), 0755);
        #endif
    }
}

// Generate HTML receipt (saved as .html, can be converted to PDF)
void generateCarRentalReceipt(const CarRental& booking) {
    ensureReceiptsDirectory();
    
    stringstream filename;
    filename << RECEIPTS_DIR << "car_rental_" << booking.bookingId << ".html";
    
    ofstream file(filename.str());
    
    if (!file.is_open()) {
        printError("Failed to generate receipt!");
        return;
    }
    
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Car Rental Receipt #" << booking.bookingId << "</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 40px auto; padding: 20px; }\n";
    file << ".header { text-align: center; border-bottom: 3px solid #333; padding-bottom: 20px; margin-bottom: 30px; }\n";
    file << ".header h1 { color: #2c3e50; margin: 0; }\n";
    file << ".header p { color: #7f8c8d; margin: 5px 0; }\n";
    file << ".section { margin: 20px 0; }\n";
    file << ".section h2 { color: #34495e; border-bottom: 2px solid #3498db; padding-bottom: 10px; }\n";
    file << ".info-row { display: flex; justify-content: space-between; padding: 10px; border-bottom: 1px solid #ecf0f1; }\n";
    file << ".info-label { font-weight: bold; color: #2c3e50; }\n";
    file << ".info-value { color: #34495e; }\n";
    file << ".total { background: #3498db; color: white; padding: 15px; text-align: right; font-size: 1.2em; font-weight: bold; margin-top: 20px; }\n";
    file << ".status { display: inline-block; padding: 5px 15px; border-radius: 20px; font-weight: bold; }\n";
    file << ".status-active { background: #2ecc71; color: white; }\n";
    file << ".status-cancelled { background: #e74c3c; color: white; }\n";
    file << ".footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 2px solid #ecf0f1; color: #7f8c8d; }\n";
    file << "</style>\n</head>\n<body>\n";
    
    // Header
    file << "<div class=\"header\">\n";
    file << "<h1>🚗 CAR RENTAL RECEIPT</h1>\n";
    file << "<p>Complete Reservation Management System</p>\n";
    file << "<p>Booking ID: #" << booking.bookingId << "</p>\n";
    file << "</div>\n";
    
    // Customer Information
    file << "<div class=\"section\">\n";
    file << "<h2>Customer Information</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Name:</span><span class=\"info-value\">" << booking.customer.name << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Email:</span><span class=\"info-value\">" << booking.customer.email << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Phone:</span><span class=\"info-value\">" << booking.customer.phone << "</span></div>\n";
    file << "</div>\n";
    
    // Rental Details
    file << "<div class=\"section\">\n";
    file << "<h2>Rental Details</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Car Model:</span><span class=\"info-value\">" << booking.carModel << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Car Type:</span><span class=\"info-value\">" << booking.carType << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Pickup Date:</span><span class=\"info-value\">" << booking.pickupDate << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Return Date:</span><span class=\"info-value\">" << booking.returnDate << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Rental Period:</span><span class=\"info-value\">" << booking.days << " days</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Price per Day:</span><span class=\"info-value\">$" << fixed << setprecision(2) << booking.pricePerDay << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Status:</span><span class=\"info-value\"><span class=\"status status-" 
         << (booking.status == "Active" ? "active" : "cancelled") << "\">" << booking.status << "</span></span></div>\n";
    file << "</div>\n";
    
    // Total
    file << "<div class=\"total\">Total Amount: $" << fixed << setprecision(2) << booking.totalPrice << "</div>\n";
    
    // Footer
    file << "<div class=\"footer\">\n";
    file << "<p>Thank you for choosing our Car Rental Service!</p>\n";
    file << "<p>This is a computer-generated receipt.</p>\n";
    file << "<p>Generated: " << getCurrentDate() << " at " << getCurrentTime() << "</p>\n";
    file << "</div>\n";
    
    file << "</body>\n</html>";
    file.close();
    
    printSuccess("Receipt generated: " + filename.str());
    printInfo("You can open this file in a browser and print to PDF");
}

void generateAirTicketReceipt(const AirTicket& booking) {
    ensureReceiptsDirectory();
    
    stringstream filename;
    filename << RECEIPTS_DIR << "air_ticket_" << booking.bookingId << ".html";
    
    ofstream file(filename.str());
    
    if (!file.is_open()) {
        printError("Failed to generate receipt!");
        return;
    }
    
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Air Ticket Receipt #" << booking.bookingId << "</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 40px auto; padding: 20px; }\n";
    file << ".header { text-align: center; border-bottom: 3px solid #333; padding-bottom: 20px; margin-bottom: 30px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 30px; margin: -20px -20px 30px -20px; }\n";
    file << ".header h1 { margin: 0; }\n";
    file << ".section { margin: 20px 0; }\n";
    file << ".section h2 { color: #34495e; border-bottom: 2px solid #667eea; padding-bottom: 10px; }\n";
    file << ".info-row { display: flex; justify-content: space-between; padding: 10px; border-bottom: 1px solid #ecf0f1; }\n";
    file << ".info-label { font-weight: bold; color: #2c3e50; }\n";
    file << ".info-value { color: #34495e; }\n";
    file << ".flight-route { text-align: center; font-size: 1.5em; color: #667eea; margin: 20px 0; font-weight: bold; }\n";
    file << ".total { background: #667eea; color: white; padding: 15px; text-align: right; font-size: 1.2em; font-weight: bold; margin-top: 20px; }\n";
    file << ".footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 2px solid #ecf0f1; color: #7f8c8d; }\n";
    file << "</style>\n</head>\n<body>\n";
    
    file << "<div class=\"header\">\n";
    file << "<h1>✈️ AIR TICKET RECEIPT</h1>\n";
    file << "<p>Booking ID: #" << booking.bookingId << "</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"flight-route\">" << booking.from << " → " << booking.to << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2>Passenger Information</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Name:</span><span class=\"info-value\">" << booking.passenger.name << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Email:</span><span class=\"info-value\">" << booking.passenger.email << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Phone:</span><span class=\"info-value\">" << booking.passenger.phone << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2>Flight Details</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Flight Number:</span><span class=\"info-value\">" << booking.flightNumber << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Airline:</span><span class=\"info-value\">" << booking.airline << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Departure:</span><span class=\"info-value\">" << booking.departureDate << " at " << booking.departureTime << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Arrival:</span><span class=\"info-value\">" << booking.arrivalTime << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Class:</span><span class=\"info-value\">" << booking.seatClass << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Passengers:</span><span class=\"info-value\">" << booking.numPassengers << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Price per Ticket:</span><span class=\"info-value\">$" << fixed << setprecision(2) << booking.pricePerTicket << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"total\">Total Amount: $" << fixed << setprecision(2) << booking.totalPrice << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "<p>Have a pleasant flight!</p>\n";
    file << "<p>Generated: " << getCurrentDate() << " at " << getCurrentTime() << "</p>\n";
    file << "</div>\n";
    
    file << "</body>\n</html>";
    file.close();
    
    printSuccess("Receipt generated: " + filename.str());
    printInfo("You can open this file in a browser and print to PDF");
}

void generateBusTicketReceipt(const BusTicket& booking) {
    ensureReceiptsDirectory();
    
    stringstream filename;
    filename << RECEIPTS_DIR << "bus_ticket_" << booking.bookingId << ".html";
    
    ofstream file(filename.str());
    
    if (!file.is_open()) {
        printError("Failed to generate receipt!");
        return;
    }
    
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Bus Ticket Receipt #" << booking.bookingId << "</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 40px auto; padding: 20px; }\n";
    file << ".header { text-align: center; background: #f39c12; color: white; padding: 30px; margin: -20px -20px 30px -20px; }\n";
    file << ".section { margin: 20px 0; }\n";
    file << ".section h2 { color: #34495e; border-bottom: 2px solid #f39c12; padding-bottom: 10px; }\n";
    file << ".info-row { display: flex; justify-content: space-between; padding: 10px; border-bottom: 1px solid #ecf0f1; }\n";
    file << ".info-label { font-weight: bold; color: #2c3e50; }\n";
    file << ".total { background: #f39c12; color: white; padding: 15px; text-align: right; font-size: 1.2em; font-weight: bold; margin-top: 20px; }\n";
    file << ".footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 2px solid #ecf0f1; color: #7f8c8d; }\n";
    file << "</style>\n</head>\n<body>\n";
    
    file << "<div class=\"header\"><h1>🚌 BUS TICKET RECEIPT</h1><p>Booking ID: #" << booking.bookingId << "</p></div>\n";
    
    file << "<div class=\"section\">\n<h2>Passenger Information</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Name:</span><span class=\"info-value\">" << booking.passenger.name << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Phone:</span><span class=\"info-value\">" << booking.passenger.phone << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n<h2>Journey Details</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Bus Number:</span><span class=\"info-value\">" << booking.busNumber << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Route:</span><span class=\"info-value\">" << booking.from << " → " << booking.to << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Date:</span><span class=\"info-value\">" << booking.departureDate << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Departure:</span><span class=\"info-value\">" << booking.departureTime << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Seat Number:</span><span class=\"info-value\">" << booking.seatNumber << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"total\">Total Amount: $" << fixed << setprecision(2) << booking.ticketPrice << "</div>\n";
    file << "<div class=\"footer\"><p>Safe journey!</p><p>Generated: " << getCurrentDate() << "</p></div>\n";
    file << "</body>\n</html>";
    file.close();
    
    printSuccess("Receipt generated: " + filename.str());
}

void generateTrainTicketReceipt(const TrainTicket& booking) {
    ensureReceiptsDirectory();
    
    stringstream filename;
    filename << RECEIPTS_DIR << "train_ticket_" << booking.bookingId << ".html";
    
    ofstream file(filename.str());
    
    if (!file.is_open()) {
        printError("Failed to generate receipt!");
        return;
    }
    
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Train Ticket Receipt #" << booking.bookingId << "</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 40px auto; padding: 20px; }\n";
    file << ".header { text-align: center; background: #16a085; color: white; padding: 30px; margin: -20px -20px 30px -20px; }\n";
    file << ".section { margin: 20px 0; }\n";
    file << ".section h2 { color: #34495e; border-bottom: 2px solid #16a085; padding-bottom: 10px; }\n";
    file << ".info-row { display: flex; justify-content: space-between; padding: 10px; border-bottom: 1px solid #ecf0f1; }\n";
    file << ".info-label { font-weight: bold; color: #2c3e50; }\n";
    file << ".total { background: #16a085; color: white; padding: 15px; text-align: right; font-size: 1.2em; font-weight: bold; margin-top: 20px; }\n";
    file << ".footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 2px solid #ecf0f1; color: #7f8c8d; }\n";
    file << "</style>\n</head>\n<body>\n";
    
    file << "<div class=\"header\"><h1>🚆 TRAIN TICKET RECEIPT</h1><p>Booking ID: #" << booking.bookingId << "</p></div>\n";
    
    file << "<div class=\"section\">\n<h2>Passenger Information</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Name:</span><span class=\"info-value\">" << booking.passenger.name << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Phone:</span><span class=\"info-value\">" << booking.passenger.phone << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n<h2>Journey Details</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Train:</span><span class=\"info-value\">" << booking.trainNumber << " - " << booking.trainName << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Route:</span><span class=\"info-value\">" << booking.from << " → " << booking.to << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Date:</span><span class=\"info-value\">" << booking.departureDate << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Departure:</span><span class=\"info-value\">" << booking.departureTime << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Class:</span><span class=\"info-value\">" << booking.ticketClass << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Seat:</span><span class=\"info-value\">" << booking.seatNumber << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"total\">Total Amount: $" << fixed << setprecision(2) << booking.ticketPrice << "</div>\n";
    file << "<div class=\"footer\"><p>Happy journey!</p><p>Generated: " << getCurrentDate() << "</p></div>\n";
    file << "</body>\n</html>";
    file.close();
    
    printSuccess("Receipt generated: " + filename.str());
}

void generateCinemaTicketReceipt(const CinemaTicket& booking) {
    ensureReceiptsDirectory();
    
    stringstream filename;
    filename << RECEIPTS_DIR << "cinema_ticket_" << booking.bookingId << ".html";
    
    ofstream file(filename.str());
    
    if (!file.is_open()) {
        printError("Failed to generate receipt!");
        return;
    }
    
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Cinema Ticket Receipt #" << booking.bookingId << "</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 40px auto; padding: 20px; background: #1a1a1a; color: #fff; }\n";
    file << ".header { text-align: center; background: linear-gradient(135deg, #e74c3c 0%, #c0392b 100%); padding: 30px; margin: -20px -20px 30px -20px; }\n";
    file << ".section { margin: 20px 0; background: #2c2c2c; padding: 20px; border-radius: 10px; }\n";
    file << ".section h2 { color: #e74c3c; border-bottom: 2px solid #e74c3c; padding-bottom: 10px; }\n";
    file << ".info-row { display: flex; justify-content: space-between; padding: 10px; border-bottom: 1px solid #444; }\n";
    file << ".info-label { font-weight: bold; color: #ecf0f1; }\n";
    file << ".seats { display: flex; flex-wrap: wrap; gap: 10px; margin-top: 10px; }\n";
    file << ".seat { background: #e74c3c; padding: 10px 15px; border-radius: 5px; font-weight: bold; }\n";
    file << ".total { background: #e74c3c; color: white; padding: 15px; text-align: right; font-size: 1.2em; font-weight: bold; margin-top: 20px; border-radius: 10px; }\n";
    file << ".footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 2px solid #444; color: #7f8c8d; }\n";
    file << "</style>\n</head>\n<body>\n";
    
    file << "<div class=\"header\"><h1>🎬 CINEMA TICKET RECEIPT</h1><p>Booking ID: #" << booking.bookingId << "</p></div>\n";
    
    file << "<div class=\"section\">\n<h2>Customer Information</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Name:</span><span class=\"info-value\">" << booking.customer.name << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Phone:</span><span class=\"info-value\">" << booking.customer.phone << "</span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n<h2>Show Details</h2>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Movie:</span><span class=\"info-value\">" << booking.movieName << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Genre:</span><span class=\"info-value\">" << booking.genre << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Theater:</span><span class=\"info-value\">" << booking.theater << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Date & Time:</span><span class=\"info-value\">" << booking.showDate << " at " << booking.showTime << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Number of Tickets:</span><span class=\"info-value\">" << booking.numTickets << "</span></div>\n";
    file << "<div class=\"info-row\"><span class=\"info-label\">Seats:</span><span class=\"info-value\"><div class=\"seats\">";
    
    for (int i = 0; i < booking.numTickets; i++) {
        file << "<span class=\"seat\">" << booking.seatNumbers[i] << "</span>";
    }
    file << "</div></span></div>\n";
    file << "</div>\n";
    
    file << "<div class=\"total\">Total Amount: $" << fixed << setprecision(2) << booking.totalPrice << "</div>\n";
    file << "<div class=\"footer\"><p>Enjoy the show! 🍿</p><p>Generated: " << getCurrentDate() << "</p></div>\n";
    file << "</body>\n</html>";
    file.close();
    
    printSuccess("Receipt generated: " + filename.str());
}
