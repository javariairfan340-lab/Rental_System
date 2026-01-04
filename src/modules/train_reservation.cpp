#include "train_reservation.h"
#include "utils.h"
#include "receipt_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string TRAIN_FILE = "data/train_tickets.txt";

struct AvailableTrain {
    string trainNumber;
    string trainName;
    string from;
    string to;
    string departureTime;
    string arrivalTime;
    double sleeperPrice;
    double acPrice;
    double firstClassPrice;
    int totalSleeperSeats;
    int totalACSeats;
    int totalFirstClassSeats;
    int availableSleeperSeats;
    int availableACSeats;
    int availableFirstClassSeats;
};

AvailableTrain availableTrains[] = {
    {"T101", "Express Line", "New York", "Boston", "07:00", "11:30", 40.0, 80.0, 150.0, 100, 50, 20, 100, 50, 20},
    {"T202", "Coast Runner", "Los Angeles", "San Diego", "09:00", "11:30", 35.0, 70.0, 130.0, 120, 40, 15, 120, 40, 15},
    {"T303", "Midwest Express", "Chicago", "St. Louis", "11:30", "16:00", 45.0, 90.0, 170.0, 110, 45, 18, 110, 45, 18},
    {"T404", "Southern Star", "Atlanta", "Miami", "13:00", "21:00", 60.0, 120.0, 220.0, 90, 55, 22, 90, 55, 22},
    {"T505", "Northeast Corridor", "Washington DC", "New York", "15:30", "18:30", 50.0, 100.0, 180.0, 105, 48, 20, 105, 48, 20},
    {"T606", "Pacific Express", "Seattle", "San Francisco", "08:00", "18:00", 70.0, 140.0, 250.0, 95, 60, 25, 95, 60, 25},
    {"T707", "Texas Star", "Dallas", "San Antonio", "10:00", "15:30", 42.0, 85.0, 160.0, 115, 42, 16, 115, 42, 16},
    {"T808", "Mountain Line", "Denver", "Salt Lake City", "12:00", "20:00", 65.0, 130.0, 240.0, 100, 52, 21, 100, 52, 21},
    {"T909", "Sunshine Express", "Tampa", "Orlando", "14:00", "16:30", 38.0, 75.0, 140.0, 125, 38, 14, 125, 38, 14},
    {"T010", "Capital Corridor", "Philadelphia", "Washington DC", "16:00", "18:30", 48.0, 95.0, 175.0, 108, 46, 19, 108, 46, 19}
};

const int NUM_TRAINS = 10;

void displayAvailableTrains() {
    clearScreen();
    printHeader("AVAILABLE TRAINS");
    
    cout << Color::BOLD << left << setw(5) << "No." << setw(10) << "Train" 
         << setw(18) << "Name" << setw(25) << "Route" << setw(12) << "Time" 
         << setw(12) << "Sleeper" << setw(15) << "Seats (S/A/F)" << Color::RESET << endl;
    printSeparator();
    
    for (int i = 0; i < NUM_TRAINS; i++) {
        cout << Color::YELLOW << left << setw(5) << (i + 1)
             << Color::CYAN << setw(10) << availableTrains[i].trainNumber
             << Color::WHITE << setw(18) << availableTrains[i].trainName
             << Color::MAGENTA << setw(25) << (availableTrains[i].from + " → " + availableTrains[i].to)
             << Color::BLUE << setw(12) << availableTrains[i].departureTime
             << Color::GREEN << "$" << setw(10) << fixed << setprecision(2) << availableTrains[i].sleeperPrice
             << Color::YELLOW << availableTrains[i].availableSleeperSeats << "/"
             << availableTrains[i].availableACSeats << "/"
             << availableTrains[i].availableFirstClassSeats
             << Color::RESET << endl;
    }
    printSeparator();
}

void bookTrainTicket(vector<TrainTicket>& bookings, int& nextId) {
    displayAvailableTrains();
    
    TrainTicket newBooking;
    newBooking.bookingId = nextId++;
    
    cout << endl;
    printInfo("Enter passenger details:");
    newBooking.passenger.name = getValidatedString("Passenger Name: ");
    newBooking.passenger.email = getValidatedString("Email: ");
    newBooking.passenger.phone = getValidatedString("Phone: ");
    
    int trainChoice = getValidatedInt("\nSelect train (1-" + to_string(NUM_TRAINS) + "): ", 1, NUM_TRAINS);
    AvailableTrain& selectedTrain = availableTrains[trainChoice - 1];
    
    newBooking.trainNumber = selectedTrain.trainNumber;
    newBooking.trainName = selectedTrain.trainName;
    newBooking.from = selectedTrain.from;
    newBooking.to = selectedTrain.to;
    newBooking.departureTime = selectedTrain.departureTime;
    newBooking.arrivalTime = selectedTrain.arrivalTime;
    
    newBooking.departureDate = getValidatedString("Travel Date (DD/MM/YYYY): ");
    
    cout << "\nSelect Class:" << endl;
    cout << "1. Sleeper ($" << selectedTrain.sleeperPrice << ")" << endl;
    cout << "2. AC ($" << selectedTrain.acPrice << ")" << endl;
    cout << "3. First Class ($" << selectedTrain.firstClassPrice << ")" << endl;
    
    int classChoice = getValidatedInt("Enter choice: ", 1, 3);
    
    if (classChoice == 1) {
        newBooking.ticketClass = "Sleeper";
        newBooking.ticketPrice = selectedTrain.sleeperPrice;
    } else if (classChoice == 2) {
        newBooking.ticketClass = "AC";
        newBooking.ticketPrice = selectedTrain.acPrice;
    } else {
        newBooking.ticketClass = "First Class";
        newBooking.ticketPrice = selectedTrain.firstClassPrice;
    }
    
    newBooking.seatNumber = getValidatedInt("Select Seat Number (1-100): ", 1, 100);
    
    // Check seat availability
    int availableSeats = 0;
    if (classChoice == 1) {
        availableSeats = selectedTrain.availableSleeperSeats;
    } else if (classChoice == 2) {
        availableSeats = selectedTrain.availableACSeats;
    } else {
        availableSeats = selectedTrain.availableFirstClassSeats;
    }
    
    if (availableSeats <= 0) {
        clearScreen();
        printError("Sorry, no seats available in " + newBooking.ticketClass + " class!");
        printInfo("Please choose a different class or train.");
        pauseScreen();
        return;
    }
    
    newBooking.status = "Confirmed";
    
    // Deduct one seat from available inventory
    if (classChoice == 1) {
        availableTrains[trainChoice - 1].availableSleeperSeats--;
    } else if (classChoice == 2) {
        availableTrains[trainChoice - 1].availableACSeats--;
    } else {
        availableTrains[trainChoice - 1].availableFirstClassSeats--;
    }
    
    bookings.push_back(newBooking);
    saveTrainBookings(bookings);
    
    clearScreen();
    printSuccess("Train ticket booked successfully!");
    cout << Color::BOLD << "\n--- BOOKING CONFIRMATION ---" << Color::RESET << endl;
    cout << "Booking ID: " << Color::YELLOW << newBooking.bookingId << Color::RESET << endl;
    cout << "Passenger: " << Color::CYAN << newBooking.passenger.name << Color::RESET << endl;
    cout << "Train: " << Color::GREEN << newBooking.trainNumber << " - " << newBooking.trainName << Color::RESET << endl;
    cout << "Route: " << newBooking.from << " → " << newBooking.to << endl;
    cout << "Class: " << newBooking.ticketClass << " | Seat: " << newBooking.seatNumber << endl;
    cout << "Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
         << newBooking.ticketPrice << Color::RESET << endl;
    
    cout << "\n" << Color::CYAN << "Generate receipt? (y/n): " << Color::RESET;
    char receiptChoice;
    cin >> receiptChoice;
    cin.ignore();
    
    if (receiptChoice == 'y' || receiptChoice == 'Y') {
        generateTrainTicketReceipt(newBooking);
    }
    
    pauseScreen();
}

void viewTrainBookings(const vector<TrainTicket>& bookings) {
    clearScreen();
    printHeader("TRAIN TICKET BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings found.");
        pauseScreen();
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const TrainTicket& b = bookings[i];
        
        cout << Color::BOLD << "\nBooking #" << b.bookingId << Color::RESET;
        if (b.status == "Confirmed") {
            cout << Color::GREEN << " [" << b.status << "]" << Color::RESET << endl;
        } else {
            cout << Color::RED << " [" << b.status << "]" << Color::RESET << endl;
        }
        
        printSeparator();
        cout << "Passenger: " << b.passenger.name << " | " << b.passenger.phone << endl;
        cout << "Train: " << b.trainNumber << " - " << b.trainName << endl;
        cout << "Route: " << b.from << " → " << b.to << endl;
        cout << "Date: " << b.departureDate << " | Time: " << b.departureTime << endl;
        cout << "Class: " << b.ticketClass << " | Seat: " << b.seatNumber << endl;
        cout << "Price: $" << fixed << setprecision(2) << b.ticketPrice << endl;
    }
    
    pauseScreen();
}

void cancelTrainBooking(vector<TrainTicket>& bookings) {
    clearScreen();
    printHeader("CANCEL TRAIN BOOKING");
    
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
            saveTrainBookings(bookings);
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

void searchTrainBooking(const vector<TrainTicket>& bookings) {
    clearScreen();
    printHeader("SEARCH TRAIN BOOKINGS");
    
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
            cout << "Train: " << bookings[i].trainNumber << " - " << bookings[i].trainName << endl;
            cout << "Route: " << bookings[i].from << " → " << bookings[i].to << endl;
            cout << "Class: " << bookings[i].ticketClass << " | Seat: " << bookings[i].seatNumber << endl;
            cout << "Status: " << bookings[i].status << endl;
            pauseScreen();
            return;
        }
    }
    
    printInfo("No booking found with ID: " + to_string(bookingId));
    pauseScreen();
}

void sortTrainBookings(vector<TrainTicket>& bookings) {
    clearScreen();
    printHeader("SORT TRAIN BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to sort.");
        pauseScreen();
        return;
    }
    
    // Selection sort by price
    int n = bookings.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (bookings[j].ticketPrice < bookings[minIdx].ticketPrice) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            TrainTicket temp = bookings[i];
            bookings[i] = bookings[minIdx];
            bookings[minIdx] = temp;
        }
    }
    
    printSuccess("Bookings sorted by price!");
    viewTrainBookings(bookings);
}

void loadTrainBookings(vector<TrainTicket>& bookings, int& nextId) {
    ifstream file(TRAIN_FILE);
    
    if (!file.is_open()) {
        nextId = 1;
        return;
    }
    
    TrainTicket booking;
    int maxId = 0;
    
    while (file >> booking.bookingId) {
        file.ignore();
        getline(file, booking.passenger.name);
        getline(file, booking.passenger.email);
        getline(file, booking.passenger.phone);
        getline(file, booking.trainNumber);
        getline(file, booking.trainName);
        getline(file, booking.from);
        getline(file, booking.to);
        getline(file, booking.departureDate);
        getline(file, booking.departureTime);
        getline(file, booking.arrivalTime);
        getline(file, booking.ticketClass);
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

void saveTrainBookings(const vector<TrainTicket>& bookings) {
    ofstream file(TRAIN_FILE);
    
    if (!file.is_open()) {
        printError("Error saving bookings to file!");
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const TrainTicket& b = bookings[i];
        file << b.bookingId << endl;
        file << b.passenger.name << endl;
        file << b.passenger.email << endl;
        file << b.passenger.phone << endl;
        file << b.trainNumber << endl;
        file << b.trainName << endl;
        file << b.from << endl;
        file << b.to << endl;
        file << b.departureDate << endl;
        file << b.departureTime << endl;
        file << b.arrivalTime << endl;
        file << b.ticketClass << endl;
        file << b.seatNumber << " " << b.ticketPrice << endl;
        file << b.status << endl;
    }
    
    file.close();
}

void trainReservationMenu() {
    static vector<TrainTicket> bookings;
    static int nextId = 1;
    static bool loaded = false;
    
    if (!loaded) {
        loadTrainBookings(bookings, nextId);
        loaded = true;
    }
    
    while (true) {
        clearScreen();
        printHeader("TRAIN RESERVATION SYSTEM");
        
        cout << Color::BOLD << "\n1. " << Color::RESET << "View Available Trains" << endl;
        cout << Color::BOLD << "2. " << Color::RESET << "Book Train Ticket" << endl;
        cout << Color::BOLD << "3. " << Color::RESET << "View My Bookings" << endl;
        cout << Color::BOLD << "4. " << Color::RESET << "Search Booking" << endl;
        cout << Color::BOLD << "5. " << Color::RESET << "Sort Bookings" << endl;
        cout << Color::BOLD << "6. " << Color::RESET << "Cancel Booking" << endl;
        cout << Color::BOLD << "7. " << Color::RESET << "Export Receipt to PDF" << endl;
        cout << Color::BOLD << "0. " << Color::RESET << "Back to Main Menu" << endl;
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 7);
        
        switch (choice) {
            case 1:
                displayAvailableTrains();
                pauseScreen();
                break;
            case 2:
                bookTrainTicket(bookings, nextId);
                break;
            case 3:
                viewTrainBookings(bookings);
                break;
            case 4:
                searchTrainBooking(bookings);
                break;
            case 5:
                sortTrainBookings(bookings);
                break;
            case 6:
                cancelTrainBooking(bookings);
                break;
            case 7: {
                clearScreen();
                printHeader("EXPORT RECEIPT TO PDF");
                int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
                string htmlPath = "receipts/train_ticket_" + to_string(bookingId) + ".html";
                
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
