#include "bus_reservation.h"
#include "utils.h"
#include "receipt_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string BUS_FILE = "data/bus_tickets.txt";

struct AvailableBus {
    string busNumber;
    string route;
    string from;
    string to;
    string departureTime;
    string arrivalTime;
    double ticketPrice;
    int totalSeats;
    int availableSeats;
};

AvailableBus availableBuses[] = {
    {"B101", "Express", "New York", "Washington DC", "06:00", "10:00", 45.0, 40, 40},
    {"B202", "Deluxe", "Los Angeles", "San Francisco", "08:30", "14:30", 65.0, 35, 35},
    {"B303", "Standard", "Chicago", "Detroit", "10:00", "14:30", 35.0, 45, 45},
    {"B404", "Express", "Miami", "Orlando", "12:00", "15:00", 40.0, 40, 40},
    {"B505", "Luxury", "Boston", "New York", "14:30", "18:30", 55.0, 30, 30},
    {"B606", "Express", "Seattle", "Portland", "07:00", "10:30", 38.0, 42, 42},
    {"B707", "Deluxe", "Dallas", "Houston", "09:30", "13:30", 42.0, 38, 38},
    {"B808", "Standard", "Philadelphia", "Baltimore", "11:00", "13:00", 28.0, 45, 45},
    {"B909", "Luxury", "San Diego", "Los Angeles", "13:00", "15:30", 50.0, 32, 32},
    {"B010", "Express", "Phoenix", "Las Vegas", "15:00", "20:00", 55.0, 40, 40}
};

const int NUM_BUSES = 10;

void displayAvailableBuses() {
    clearScreen();
    printHeader("AVAILABLE BUS ROUTES");
    
    cout << Color::BOLD << left << setw(5) << "No." << setw(10) << "Bus" 
         << setw(12) << "Type" << setw(25) << "Route" << setw(12) << "Time" 
         << setw(10) << "Price" << setw(15) << "Seats Avail" << Color::RESET << endl;
    printSeparator();
    
    for (int i = 0; i < NUM_BUSES; i++) {
        cout << Color::YELLOW << left << setw(5) << (i + 1)
             << Color::CYAN << setw(10) << availableBuses[i].busNumber
             << Color::WHITE << setw(12) << availableBuses[i].route
             << Color::MAGENTA << setw(25) << (availableBuses[i].from + " → " + availableBuses[i].to)
             << Color::BLUE << setw(12) << availableBuses[i].departureTime
             << Color::GREEN << "$" << setw(8) << fixed << setprecision(2) << availableBuses[i].ticketPrice
             << Color::YELLOW << availableBuses[i].availableSeats << "/" << availableBuses[i].totalSeats
             << Color::RESET << endl;
    }
    printSeparator();
}

void bookBusTicket(vector<BusTicket>& bookings, int& nextId) {
    displayAvailableBuses();
    
    BusTicket newBooking;
    newBooking.bookingId = nextId++;
    
    cout << endl;
    printInfo("Enter passenger details:");
    newBooking.passenger.name = getValidatedString("Passenger Name: ");
    newBooking.passenger.email = getValidatedString("Email: ");
    newBooking.passenger.phone = getValidatedString("Phone: ");
    
    int busChoice = getValidatedInt("\nSelect bus (1-" + to_string(NUM_BUSES) + "): ", 1, NUM_BUSES);
    AvailableBus& selectedBus = availableBuses[busChoice - 1];
    
    // Check seat availability
    if (selectedBus.availableSeats <= 0) {
        clearScreen();
        printError("Sorry, this bus is fully booked!");
        printInfo("No seats available on " + selectedBus.busNumber + " (" + selectedBus.from + " → " + selectedBus.to + ")");
        pauseScreen();
        return;
    }
    
    newBooking.busNumber = selectedBus.busNumber;
    newBooking.route = selectedBus.route;
    newBooking.from = selectedBus.from;
    newBooking.to = selectedBus.to;
    newBooking.departureTime = selectedBus.departureTime;
    newBooking.arrivalTime = selectedBus.arrivalTime;
    newBooking.ticketPrice = selectedBus.ticketPrice;
    
    newBooking.departureDate = getValidatedString("Travel Date (DD/MM/YYYY): ");
    newBooking.seatNumber = getValidatedInt("Select Seat Number (1-" + to_string(selectedBus.totalSeats) + "): ", 
                                            1, selectedBus.totalSeats);
    
    newBooking.status = "Confirmed";
    
    // Deduct one seat from available inventory
    availableBuses[busChoice - 1].availableSeats--;
    
    bookings.push_back(newBooking);
    saveBusBookings(bookings);
    
    clearScreen();
    printSuccess("Bus ticket booked successfully!");
    cout << Color::BOLD << "\n--- BOOKING CONFIRMATION ---" << Color::RESET << endl;
    cout << "Booking ID: " << Color::YELLOW << newBooking.bookingId << Color::RESET << endl;
    cout << "Passenger: " << Color::CYAN << newBooking.passenger.name << Color::RESET << endl;
    cout << "Bus: " << Color::GREEN << newBooking.busNumber << " (" << newBooking.route << ")" << Color::RESET << endl;
    cout << "Route: " << newBooking.from << " → " << newBooking.to << endl;
    cout << "Seat: " << newBooking.seatNumber << endl;
    cout << "Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
         << newBooking.ticketPrice << Color::RESET << endl;
    
    cout << "\n" << Color::CYAN << "Generate receipt? (y/n): " << Color::RESET;
    char receiptChoice;
    cin >> receiptChoice;
    cin.ignore();
    
    if (receiptChoice == 'y' || receiptChoice == 'Y') {
        generateBusTicketReceipt(newBooking);
    }
    
    pauseScreen();
}

void viewBusBookings(const vector<BusTicket>& bookings) {
    clearScreen();
    printHeader("BUS TICKET BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings found.");
        pauseScreen();
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const BusTicket& b = bookings[i];
        
        cout << Color::BOLD << "\nBooking #" << b.bookingId << Color::RESET;
        if (b.status == "Confirmed") {
            cout << Color::GREEN << " [" << b.status << "]" << Color::RESET << endl;
        } else {
            cout << Color::RED << " [" << b.status << "]" << Color::RESET << endl;
        }
        
        printSeparator();
        cout << "Passenger: " << b.passenger.name << " | " << b.passenger.phone << endl;
        cout << "Bus: " << b.busNumber << " - " << b.route << endl;
        cout << "Route: " << b.from << " → " << b.to << endl;
        cout << "Date: " << b.departureDate << " | Time: " << b.departureTime << endl;
        cout << "Seat: " << b.seatNumber << endl;
        cout << "Price: $" << fixed << setprecision(2) << b.ticketPrice << endl;
    }
    
    pauseScreen();
}

void cancelBusBooking(vector<BusTicket>& bookings) {
    clearScreen();
    printHeader("CANCEL BUS BOOKING");
    
    if (bookings.empty()) {
        printInfo("No bookings to cancel.");
        pauseScreen();
        return;
    }
    
    int bookingId = getValidatedInt("Enter Booking ID to cancel: ", 1, 999999);
    
    bool found = false;
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingId == bookingId && bookings[i].status == "Confirmed") {
            bookings[i].status = "Cancelled";
            saveBusBookings(bookings);
            printSuccess("Booking cancelled successfully!");
            found = true;
            break;
        }
    }
    
    if (!found) {
        printError("Active booking not found with ID: " + to_string(bookingId));
    }
    
    pauseScreen();
}

void searchBusBooking(const vector<BusTicket>& bookings) {
    clearScreen();
    printHeader("SEARCH BUS BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to search.");
        pauseScreen();
        return;
    }
    
    int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
    
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingId == bookingId) {
            cout << Color::BOLD << "\nBooking Found:" << Color::RESET << endl;
            printSeparator();
            cout << "Booking ID: " << bookings[i].bookingId << endl;
            cout << "Passenger: " << bookings[i].passenger.name << endl;
            cout << "Bus: " << bookings[i].busNumber << " - " << bookings[i].route << endl;
            cout << "Route: " << bookings[i].from << " → " << bookings[i].to << endl;
            cout << "Seat: " << bookings[i].seatNumber << endl;
            cout << "Status: " << bookings[i].status << endl;
            pauseScreen();
            return;
        }
    }
    
    printInfo("No booking found with ID: " + to_string(bookingId));
    pauseScreen();
}

void sortBusBookings(vector<BusTicket>& bookings) {
    clearScreen();
    printHeader("SORT BUS BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to sort.");
        pauseScreen();
        return;
    }
    
    // Bubble sort by booking ID
    int n = bookings.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bookings[j].bookingId > bookings[j + 1].bookingId) {
                BusTicket temp = bookings[j];
                bookings[j] = bookings[j + 1];
                bookings[j + 1] = temp;
            }
        }
    }
    
    printSuccess("Bookings sorted by ID!");
    viewBusBookings(bookings);
}

void loadBusBookings(vector<BusTicket>& bookings, int& nextId) {
    ifstream file(BUS_FILE);
    
    if (!file.is_open()) {
        nextId = 1;
        return;
    }
    
    BusTicket booking;
    int maxId = 0;
    
    while (file >> booking.bookingId) {
        file.ignore();
        getline(file, booking.passenger.name);
        getline(file, booking.passenger.email);
        getline(file, booking.passenger.phone);
        getline(file, booking.busNumber);
        getline(file, booking.route);
        getline(file, booking.from);
        getline(file, booking.to);
        getline(file, booking.departureDate);
        getline(file, booking.departureTime);
        getline(file, booking.arrivalTime);
        file >> booking.seatNumber >> booking.ticketPrice;
        file.ignore();
        getline(file, booking.status);
        
        bookings.push_back(booking);
        if (booking.bookingId > maxId) {
            maxId = booking.bookingId;
        }
    }
    
    file.close();
    nextId = maxId + 1;
}

void saveBusBookings(const vector<BusTicket>& bookings) {
    ofstream file(BUS_FILE);
    
    if (!file.is_open()) {
        printError("Error saving bookings to file!");
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const BusTicket& b = bookings[i];
        file << b.bookingId << endl;
        file << b.passenger.name << endl;
        file << b.passenger.email << endl;
        file << b.passenger.phone << endl;
        file << b.busNumber << endl;
        file << b.route << endl;
        file << b.from << endl;
        file << b.to << endl;
        file << b.departureDate << endl;
        file << b.departureTime << endl;
        file << b.arrivalTime << endl;
        file << b.seatNumber << " " << b.ticketPrice << endl;
        file << b.status << endl;
    }
    
    file.close();
}

void busReservationMenu() {
    static vector<BusTicket> bookings;
    static int nextId = 1;
    static bool loaded = false;
    
    if (!loaded) {
        loadBusBookings(bookings, nextId);
        loaded = true;
    }
    
    while (true) {
        clearScreen();
        printHeader("BUS RESERVATION SYSTEM");
        
        cout << Color::BOLD << "\n1. " << Color::RESET << "View Available Buses" << endl;
        cout << Color::BOLD << "2. " << Color::RESET << "Book Bus Ticket" << endl;
        cout << Color::BOLD << "3. " << Color::RESET << "View My Bookings" << endl;
        cout << Color::BOLD << "4. " << Color::RESET << "Search Booking" << endl;
        cout << Color::BOLD << "5. " << Color::RESET << "Sort Bookings" << endl;
        cout << Color::BOLD << "6. " << Color::RESET << "Cancel Booking" << endl;
        cout << Color::BOLD << "7. " << Color::RESET << "Export Receipt to PDF" << endl;
        cout << Color::BOLD << "0. " << Color::RESET << "Back to Main Menu" << endl;
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 7);
        
        switch (choice) {
            case 1:
                displayAvailableBuses();
                pauseScreen();
                break;
            case 2:
                bookBusTicket(bookings, nextId);
                break;
            case 3:
                viewBusBookings(bookings);
                break;
            case 4:
                searchBusBooking(bookings);
                break;
            case 5:
                sortBusBookings(bookings);
                break;
            case 6:
                cancelBusBooking(bookings);
                break;
            case 7: {
                clearScreen();
                printHeader("EXPORT RECEIPT TO PDF");
                int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
                string htmlPath = "receipts/bus_ticket_" + to_string(bookingId) + ".html";
                
                ifstream checkFile(htmlPath);
                if (checkFile.good()) {
                    checkFile.close();
                    convertReceiptToPDF(htmlPath);
                } else {
                    printError("Receipt not found for booking ID: " + to_string(bookingId));
                    printInfo("Generate receipt first by booking and choosing 'y' for receipt generation.");
                }
                pauseScreen();
                break;
            }
            case 0:
                return;
        }
    }
}
