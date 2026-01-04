#include "air_ticketing.h"
#include "utils.h"
#include "receipt_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string FLIGHT_FILE = "data/air_tickets.txt";

struct AvailableFlight {
    string flightNumber;
    string airline;
    string from;
    string to;
    string departureTime;
    string arrivalTime;
    double economyPrice;
    double businessPrice;
    double firstClassPrice;
    int totalEconomySeats;
    int totalBusinessSeats;
    int totalFirstClassSeats;
    int availableEconomySeats;
    int availableBusinessSeats;
    int availableFirstClassSeats;
};

AvailableFlight availableFlights[] = {
    {"AA101", "American Airlines", "New York", "Los Angeles", "08:00", "11:30", 250.0, 500.0, 1000.0, 150, 30, 10, 150, 30, 10},
    {"UA202", "United Airlines", "Chicago", "Miami", "10:15", "14:45", 180.0, 400.0, 850.0, 140, 25, 8, 140, 25, 8},
    {"DL303", "Delta Airlines", "Boston", "Seattle", "12:30", "15:45", 300.0, 600.0, 1200.0, 160, 35, 12, 160, 35, 12},
    {"SW404", "Southwest", "Dallas", "Denver", "14:00", "15:30", 150.0, 300.0, 600.0, 120, 20, 6, 120, 20, 6},
    {"BA505", "British Airways", "London", "New York", "18:00", "21:00", 450.0, 900.0, 1800.0, 180, 40, 15, 180, 40, 15},
    {"EK606", "Emirates", "Dubai", "London", "22:00", "02:30", 500.0, 1000.0, 2500.0, 200, 50, 20, 200, 50, 20},
    {"AA107", "American Airlines", "San Francisco", "New York", "06:30", "15:00", 280.0, 550.0, 1100.0, 150, 30, 10, 150, 30, 10},
    {"UA208", "United Airlines", "Houston", "Los Angeles", "09:00", "11:00", 200.0, 420.0, 900.0, 130, 22, 7, 130, 22, 7},
    {"DL309", "Delta Airlines", "Atlanta", "Seattle", "11:00", "14:30", 320.0, 640.0, 1250.0, 165, 32, 11, 165, 32, 11},
    {"LH510", "Lufthansa", "Frankfurt", "New York", "10:00", "13:00", 480.0, 950.0, 1900.0, 190, 45, 18, 190, 45, 18},
    {"AF611", "Air France", "Paris", "Los Angeles", "13:30", "16:30", 520.0, 1050.0, 2100.0, 185, 42, 16, 185, 42, 16},
    {"QR712", "Qatar Airways", "Doha", "London", "02:00", "07:00", 550.0, 1100.0, 2600.0, 210, 55, 22, 210, 55, 22},
    {"SQ813", "Singapore Airlines", "Singapore", "San Francisco", "23:00", "20:30", 600.0, 1200.0, 2800.0, 220, 60, 25, 220, 60, 25},
    {"JL914", "Japan Airlines", "Tokyo", "Los Angeles", "17:00", "11:00", 580.0, 1150.0, 2700.0, 195, 48, 19, 195, 48, 19},
    {"CX015", "Cathay Pacific", "Hong Kong", "New York", "15:00", "18:00", 590.0, 1180.0, 2750.0, 205, 52, 21, 205, 52, 21}
};

const int NUM_FLIGHTS = 15;

void displayAvailableFlights() {
    clearScreen();
    printHeader("AVAILABLE FLIGHTS");
    
    cout << Color::BOLD << left << setw(5) << "No." << setw(10) << "Flight" 
         << setw(18) << "Airline" << setw(20) << "Route" << setw(12) << "Time" 
         << setw(12) << "Economy" << setw(15) << "Seats (E/B/F)" << Color::RESET << endl;
    printSeparator();
    
    for (int i = 0; i < NUM_FLIGHTS; i++) {
        cout << Color::YELLOW << left << setw(5) << (i + 1)
             << Color::CYAN << setw(10) << availableFlights[i].flightNumber
             << Color::WHITE << setw(18) << availableFlights[i].airline
             << Color::MAGENTA << setw(20) << (availableFlights[i].from + "-" + availableFlights[i].to)
             << Color::BLUE << setw(12) << availableFlights[i].departureTime
             << Color::GREEN << "$" << setw(10) << fixed << setprecision(2) << availableFlights[i].economyPrice
             << Color::YELLOW << availableFlights[i].availableEconomySeats << "/" 
             << availableFlights[i].availableBusinessSeats << "/" 
             << availableFlights[i].availableFirstClassSeats
             << Color::RESET << endl;
    }
    printSeparator();
}

void bookFlight(vector<AirTicket>& bookings, int& nextId) {
    displayAvailableFlights();
    
    AirTicket newBooking;
    newBooking.bookingId = nextId++;
    
    cout << endl;
    printInfo("Enter passenger details:");
    newBooking.passenger.name = getValidatedString("Passenger Name: ");
    newBooking.passenger.email = getValidatedString("Email: ");
    newBooking.passenger.phone = getValidatedString("Phone: ");
    
    int flightChoice = getValidatedInt("\nSelect flight (1-" + to_string(NUM_FLIGHTS) + "): ", 1, NUM_FLIGHTS);
    AvailableFlight& selectedFlight = availableFlights[flightChoice - 1];
    
    newBooking.flightNumber = selectedFlight.flightNumber;
    newBooking.airline = selectedFlight.airline;
    newBooking.from = selectedFlight.from;
    newBooking.to = selectedFlight.to;
    newBooking.departureTime = selectedFlight.departureTime;
    newBooking.arrivalTime = selectedFlight.arrivalTime;
    
    newBooking.departureDate = getValidatedString("Departure Date (DD/MM/YYYY): ");
    
    cout << "\nSelect Class:" << endl;
    cout << "1. Economy ($" << selectedFlight.economyPrice << ")" << endl;
    cout << "2. Business ($" << selectedFlight.businessPrice << ")" << endl;
    cout << "3. First Class ($" << selectedFlight.firstClassPrice << ")" << endl;
    
    int classChoice = getValidatedInt("Enter choice: ", 1, 3);
    
    if (classChoice == 1) {
        newBooking.seatClass = "Economy";
        newBooking.pricePerTicket = selectedFlight.economyPrice;
    } else if (classChoice == 2) {
        newBooking.seatClass = "Business";
        newBooking.pricePerTicket = selectedFlight.businessPrice;
    } else {
        newBooking.seatClass = "First Class";
        newBooking.pricePerTicket = selectedFlight.firstClassPrice;
    }
    
    
    newBooking.numPassengers = getValidatedInt("Number of Passengers: ", 1, 9);
    
    // Check seat availability
    int availableSeats = 0;
    if (classChoice == 1) {
        availableSeats = selectedFlight.availableEconomySeats;
    } else if (classChoice == 2) {
        availableSeats = selectedFlight.availableBusinessSeats;
    } else {
        availableSeats = selectedFlight.availableFirstClassSeats;
    }
    
    if (newBooking.numPassengers > availableSeats) {
        clearScreen();
        printError("Not enough seats available!");
        printInfo("Available seats in " + newBooking.seatClass + ": " + to_string(availableSeats));
        pauseScreen();
        return;
    }
    
    newBooking.totalPrice = newBooking.pricePerTicket * newBooking.numPassengers;
    newBooking.status = "Confirmed";
    
    // Deduct seats from available inventory
    if (classChoice == 1) {
        availableFlights[flightChoice - 1].availableEconomySeats -= newBooking.numPassengers;
    } else if (classChoice == 2) {
        availableFlights[flightChoice - 1].availableBusinessSeats -= newBooking.numPassengers;
    } else {
        availableFlights[flightChoice - 1].availableFirstClassSeats -= newBooking.numPassengers;
    }
    
    bookings.push_back(newBooking);
    saveFlightBookings(bookings);
    
    clearScreen();
    printSuccess("Flight booked successfully!");
    cout << Color::BOLD << "\n--- BOOKING CONFIRMATION ---" << Color::RESET << endl;
    cout << "Booking ID: " << Color::YELLOW << newBooking.bookingId << Color::RESET << endl;
    cout << "Passenger: " << Color::CYAN << newBooking.passenger.name << Color::RESET << endl;
    cout << "Flight: " << Color::GREEN << newBooking.flightNumber << " (" << newBooking.airline << ")" << Color::RESET << endl;
    cout << "Route: " << newBooking.from << " → " << newBooking.to << endl;
    cout << "Class: " << newBooking.seatClass << endl;
    cout << "Total Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
         << newBooking.totalPrice << Color::RESET << endl;
    
    cout << "\n" << Color::CYAN << "Generate receipt? (y/n): " << Color::RESET;
    char receiptChoice;
    cin >> receiptChoice;
    cin.ignore();
    
    if (receiptChoice == 'y' || receiptChoice == 'Y') {
        generateAirTicketReceipt(newBooking);
    }
    
    pauseScreen();
}

void viewFlightBookings(const vector<AirTicket>& bookings) {
    clearScreen();
    printHeader("FLIGHT BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings found.");
        pauseScreen();
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const AirTicket& b = bookings[i];
        
        cout << Color::BOLD << "\nBooking #" << b.bookingId << Color::RESET;
        if (b.status == "Confirmed") {
            cout << Color::GREEN << " [" << b.status << "]" << Color::RESET << endl;
        } else {
            cout << Color::RED << " [" << b.status << "]" << Color::RESET << endl;
        }
        
        printSeparator();
        cout << "Passenger: " << b.passenger.name << " | " << b.passenger.phone << endl;
        cout << "Flight: " << b.flightNumber << " - " << b.airline << endl;
        cout << "Route: " << b.from << " → " << b.to << endl;
        cout << "Date: " << b.departureDate << " | Time: " << b.departureTime << endl;
        cout << "Class: " << b.seatClass << " | Passengers: " << b.numPassengers << endl;
        cout << "Total: $" << fixed << setprecision(2) << b.totalPrice << endl;
    }
    
    pauseScreen();
}

void cancelFlightBooking(vector<AirTicket>& bookings) {
    clearScreen();
    printHeader("CANCEL FLIGHT BOOKING");
    
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
            saveFlightBookings(bookings);
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

void searchFlightByDestination(const vector<AirTicket>& bookings, const string& destination) {
    bool found = false;
    
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].to.find(destination) != string::npos) {
            if (!found) {
                cout << Color::BOLD << "\nSearch Results:" << Color::RESET << endl;
                printSeparator();
                found = true;
            }
            
            cout << "Booking ID: " << bookings[i].bookingId << " | "
                 << bookings[i].passenger.name << " | "
                 << bookings[i].from << " → " << bookings[i].to << " | "
                 << bookings[i].status << endl;
        }
    }
    
    if (!found) {
        printInfo("No bookings found for destination: " + destination);
    }
}

void searchFlightById(const vector<AirTicket>& bookings, int id) {
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingId == id) {
            cout << Color::BOLD << "\nBooking Found:" << Color::RESET << endl;
            printSeparator();
            cout << "Booking ID: " << bookings[i].bookingId << endl;
            cout << "Passenger: " << bookings[i].passenger.name << endl;
            cout << "Flight: " << bookings[i].flightNumber << " - " << bookings[i].airline << endl;
            cout << "Route: " << bookings[i].from << " → " << bookings[i].to << endl;
            cout << "Status: " << bookings[i].status << endl;
            cout << "Total: $" << fixed << setprecision(2) << bookings[i].totalPrice << endl;
            return;
        }
    }
    
    printInfo("No booking found with ID: " + to_string(id));
}

void searchFlightBooking(const vector<AirTicket>& bookings) {
    clearScreen();
    printHeader("SEARCH FLIGHT BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to search.");
        pauseScreen();
        return;
    }
    
    cout << "\n1. Search by Booking ID" << endl;
    cout << "2. Search by Destination" << endl;
    
    int choice = getValidatedInt("\nEnter choice: ", 1, 2);
    
    if (choice == 1) {
        int id = getValidatedInt("Enter Booking ID: ", 1, 999999);
        searchFlightById(bookings, id);
    } else {
        string destination = getValidatedString("Enter Destination: ");
        searchFlightByDestination(bookings, destination);
    }
    
    pauseScreen();
}

void sortFlightBookings(vector<AirTicket>& bookings) {
    clearScreen();
    printHeader("SORT FLIGHT BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to sort.");
        pauseScreen();
        return;
    }
    
    cout << "\n1. Sort by Price (Low to High)" << endl;
    cout << "2. Sort by Price (High to Low)" << endl;
    cout << "3. Sort by Booking ID" << endl;
    
    int choice = getValidatedInt("\nEnter choice: ", 1, 3);
    
    // Selection sort implementation
    int n = bookings.size();
    for (int i = 0; i < n - 1; i++) {
        int selectedIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            bool shouldSelect = false;
            
            if (choice == 1 && bookings[j].totalPrice < bookings[selectedIdx].totalPrice) {
                shouldSelect = true;
            } else if (choice == 2 && bookings[j].totalPrice > bookings[selectedIdx].totalPrice) {
                shouldSelect = true;
            } else if (choice == 3 && bookings[j].bookingId < bookings[selectedIdx].bookingId) {
                shouldSelect = true;
            }
            
            if (shouldSelect) {
                selectedIdx = j;
            }
        }
        
        if (selectedIdx != i) {
            AirTicket temp = bookings[i];
            bookings[i] = bookings[selectedIdx];
            bookings[selectedIdx] = temp;
        }
    }
    
    printSuccess("Bookings sorted successfully!");
    viewFlightBookings(bookings);
}

void loadFlightBookings(vector<AirTicket>& bookings, int& nextId) {
    ifstream file(FLIGHT_FILE);
    
    if (!file.is_open()) {
        nextId = 1;
        return;
    }
    
    AirTicket booking;
    int maxId = 0;
    
    while (file >> booking.bookingId) {
        file.ignore();
        getline(file, booking.passenger.name);
        getline(file, booking.passenger.email);
        getline(file, booking.passenger.phone);
        getline(file, booking.flightNumber);
        getline(file, booking.airline);
        getline(file, booking.from);
        getline(file, booking.to);
        getline(file, booking.departureDate);
        getline(file, booking.departureTime);
        getline(file, booking.arrivalTime);
        getline(file, booking.seatClass);
        file >> booking.numPassengers >> booking.pricePerTicket >> booking.totalPrice;
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

void saveFlightBookings(const vector<AirTicket>& bookings) {
    ofstream file(FLIGHT_FILE);
    
    if (!file.is_open()) {
        printError("Error saving bookings to file!");
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const AirTicket& b = bookings[i];
        file << b.bookingId << endl;
        file << b.passenger.name << endl;
        file << b.passenger.email << endl;
        file << b.passenger.phone << endl;
        file << b.flightNumber << endl;
        file << b.airline << endl;
        file << b.from << endl;
        file << b.to << endl;
        file << b.departureDate << endl;
        file << b.departureTime << endl;
        file << b.arrivalTime << endl;
        file << b.seatClass << endl;
        file << b.numPassengers << " " << b.pricePerTicket << " " << b.totalPrice << endl;
        file << b.status << endl;
    }
    
    file.close();
}

void airTicketingMenu() {
    static vector<AirTicket> bookings;
    static int nextId = 1;
    static bool loaded = false;
    
    if (!loaded) {
        loadFlightBookings(bookings, nextId);
        loaded = true;
    }
    
    while (true) {
        clearScreen();
        printHeader("AIR TICKETING SYSTEM");
        
        cout << Color::BOLD << "\n1. " << Color::RESET << "View Available Flights" << endl;
        cout << Color::BOLD << "2. " << Color::RESET << "Book a Flight" << endl;
        cout << Color::BOLD << "3. " << Color::RESET << "View My Bookings" << endl;
        cout << Color::BOLD << "4. " << Color::RESET << "Search Bookings" << endl;
        cout << Color::BOLD << "5. " << Color::RESET << "Sort Bookings" << endl;
        cout << Color::BOLD << "6. " << Color::RESET << "Cancel Booking" << endl;
        cout << Color::BOLD << "7. " << Color::RESET << "Export Receipt to PDF" << endl;
        cout << Color::BOLD << "0. " << Color::RESET << "Back to Main Menu" << endl;
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 7);
        
        switch (choice) {
            case 1:
                displayAvailableFlights();
                pauseScreen();
                break;
            case 2:
                bookFlight(bookings, nextId);
                break;
            case 3:
                viewFlightBookings(bookings);
                break;
            case 4:
                searchFlightBooking(bookings);
                break;
            case 5:
                sortFlightBookings(bookings);
                break;
            case 6:
                cancelFlightBooking(bookings);
                break;
            case 7: {
                clearScreen();
                printHeader("EXPORT RECEIPT TO PDF");
                int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
                string htmlPath = "receipts/air_ticket_" + to_string(bookingId) + ".html";
                
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
