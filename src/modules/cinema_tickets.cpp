#include "cinema_tickets.h"
#include "utils.h"
#include "receipt_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string CINEMA_FILE = "data/cinema_tickets.txt";

struct AvailableMovie {
    string movieName;
    string genre;
    string theater;
    string showTimes[4];
    double ticketPrice;
    int numShowTimes;
    int totalSeatsPerShow;
    int availableSeats[4]; // Available seats for each showtime
};

AvailableMovie availableMovies[] = {
    {"The Matrix Resurrections", "Sci-Fi", "Cinema Hall 1", {"10:00", "14:00", "18:00", "22:00"}, 15.0, 4, 100, {100, 100, 100, 100}},
    {"Dune: Part Two", "Adventure", "Cinema Hall 2", {"11:00", "15:00", "19:00", "23:00"}, 18.0, 4, 120, {120, 120, 120, 120}},
    {"Oppenheimer", "Biography", "Cinema Hall 3", {"12:00", "16:00", "20:00", ""}, 16.0, 3, 150, {150, 150, 150, 0}},
    {"Barbie", "Comedy", "Cinema Hall 1", {"13:00", "17:00", "21:00", ""}, 14.0, 3, 100, {100, 100, 100, 0}},
    {"Mission Impossible", "Action", "Cinema Hall 2", {"10:30", "14:30", "18:30", "22:30"}, 17.0, 4, 120, {120, 120, 120, 120}},
    {"Avatar: The Way of Water", "Sci-Fi", "Cinema Hall 3", {"09:00", "13:00", "17:00", "21:00"}, 19.0, 4, 150, {150, 150, 150, 150}},
    {"Guardians of the Galaxy 3", "Action", "Cinema Hall 1", {"11:30", "15:30", "19:30", ""}, 16.0, 3, 100, {100, 100, 100, 0}},
    {"Spider-Man: Across the Spider-Verse", "Animation", "Cinema Hall 2", {"10:00", "14:00", "18:00", "22:00"}, 15.0, 4, 120, {120, 120, 120, 120}},
    {"The Batman", "Action", "Cinema Hall 3", {"12:30", "16:30", "20:30", ""}, 17.0, 3, 150, {150, 150, 150, 0}},
    {"Top Gun: Maverick", "Action", "Cinema Hall 1", {"09:30", "13:30", "17:30", "21:30"}, 18.0, 4, 100, {100, 100, 100, 100}},
    {"Interstellar", "Sci-Fi", "Cinema Hall 2", {"11:00", "15:00", "19:00", ""}, 16.0, 3, 120, {120, 120, 120, 0}},
    {"Inception", "Thriller", "Cinema Hall 3", {"10:00", "14:00", "18:00", "22:00"}, 15.0, 4, 150, {150, 150, 150, 150}},
    {"The Dark Knight", "Action", "Cinema Hall 1", {"12:00", "16:00", "20:00", ""}, 17.0, 3, 100, {100, 100, 100, 0}},
    {"Avengers: Endgame", "Action", "Cinema Hall 2", {"09:00", "13:00", "17:00", "21:00"}, 19.0, 4, 120, {120, 120, 120, 120}},
    {"Joker", "Drama", "Cinema Hall 3", {"11:30", "15:30", "19:30", "23:00"}, 16.0, 4, 150, {150, 150, 150, 150}}
};

const int NUM_MOVIES = 15;

void displayAvailableMovies() {
    clearScreen();
    printHeader("NOW SHOWING - AVAILABLE MOVIES");
    
    for (int i = 0; i < NUM_MOVIES; i++) {
        cout << Color::BOLD << Color::YELLOW << "\n[" << (i + 1) << "] " 
             << Color::CYAN << availableMovies[i].movieName << Color::RESET << endl;
        cout << "    Genre: " << Color::MAGENTA << availableMovies[i].genre << Color::RESET << endl;
        cout << "    Theater: " << Color::WHITE << availableMovies[i].theater << Color::RESET << endl;
        cout << "    Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
             << availableMovies[i].ticketPrice << Color::RESET << " per ticket" << endl;
        
        cout << "    Showtimes & Seats:" << endl;
        for (int j = 0; j < availableMovies[i].numShowTimes; j++) {
            cout << "      " << Color::BLUE << availableMovies[i].showTimes[j] << Color::RESET << " - ";
            
            // Color code based on availability
            int available = availableMovies[i].availableSeats[j];
            int total = availableMovies[i].totalSeatsPerShow;
            
            if (available == 0) {
                cout << Color::RED << "SOLD OUT" << Color::RESET;
            } else if (available < total * 0.3) {
                cout << Color::YELLOW << available << "/" << total << " seats (Filling Fast!)" << Color::RESET;
            } else {
                cout << Color::GREEN << available << "/" << total << " seats" << Color::RESET;
            }
            cout << endl;
        }
    }
    printSeparator();
}

void bookCinemaTicket(vector<CinemaTicket>& bookings, int& nextId) {
    displayAvailableMovies();
    
    CinemaTicket newBooking;
    newBooking.bookingId = nextId++;
    
    cout << endl;
    printInfo("Enter customer details:");
    newBooking.customer.name = getValidatedString("Customer Name: ");
    newBooking.customer.email = getValidatedString("Email: ");
    newBooking.customer.phone = getValidatedString("Phone: ");
    
    int movieChoice = getValidatedInt("\nSelect movie (1-" + to_string(NUM_MOVIES) + "): ", 1, NUM_MOVIES);
    AvailableMovie& selectedMovie = availableMovies[movieChoice - 1];
    
    newBooking.movieName = selectedMovie.movieName;
    newBooking.genre = selectedMovie.genre;
    newBooking.theater = selectedMovie.theater;
    newBooking.pricePerTicket = selectedMovie.ticketPrice;
    
    newBooking.showDate = getValidatedString("Show Date (DD/MM/YYYY): ");
    
    cout << "\nAvailable Showtimes:" << endl;
    for (int i = 0; i < selectedMovie.numShowTimes; i++) {
        cout << (i + 1) << ". " << selectedMovie.showTimes[i] << endl;
    }
    
    int timeChoice = getValidatedInt("Select showtime: ", 1, selectedMovie.numShowTimes);
    newBooking.showTime = selectedMovie.showTimes[timeChoice - 1];
    
    newBooking.numTickets = getValidatedInt("Number of Tickets (1-10): ", 1, 10);
    
    // Array usage for seat numbers
    cout << "\nEnter seat numbers:" << endl;
    for (int i = 0; i < newBooking.numTickets; i++) {
        newBooking.seatNumbers[i] = getValidatedInt("Seat " + to_string(i + 1) + " (1-100): ", 1, 100);
    }
    
    newBooking.totalPrice = newBooking.pricePerTicket * newBooking.numTickets;
    newBooking.status = "Confirmed";
    
    bookings.push_back(newBooking);
    saveCinemaBookings(bookings);
    
    clearScreen();
    printSuccess("Cinema tickets booked successfully!");
    cout << Color::BOLD << "\n--- BOOKING CONFIRMATION ---" << Color::RESET << endl;
    cout << "Booking ID: " << Color::YELLOW << newBooking.bookingId << Color::RESET << endl;
    cout << "Customer: " << Color::CYAN << newBooking.customer.name << Color::RESET << endl;
    cout << "Movie: " << Color::GREEN << newBooking.movieName << Color::RESET << endl;
    cout << "Show: " << newBooking.showDate << " at " << newBooking.showTime << endl;
    cout << "Tickets: " << newBooking.numTickets << " | Seats: ";
    for (int i = 0; i < newBooking.numTickets; i++) {
        cout << newBooking.seatNumbers[i];
        if (i < newBooking.numTickets - 1) cout << ", ";
    }
    cout << endl;
    cout << "Total Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
         << newBooking.totalPrice << Color::RESET << endl;
    
    cout << "\n" << Color::CYAN << "Generate receipt? (y/n): " << Color::RESET;
    char receiptChoice;
    cin >> receiptChoice;
    cin.ignore();
    
    if (receiptChoice == 'y' || receiptChoice == 'Y') {
        generateCinemaTicketReceipt(newBooking);
    }
    
    pauseScreen();
}

void viewCinemaBookings(const vector<CinemaTicket>& bookings) {
    clearScreen();
    printHeader("CINEMA TICKET BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings found.");
        pauseScreen();
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const CinemaTicket& b = bookings[i];
        
        cout << Color::BOLD << "\nBooking #" << b.bookingId << Color::RESET;
        if (b.status == "Confirmed") {
            cout << Color::GREEN << " [" << b.status << "]" << Color::RESET << endl;
        } else {
            cout << Color::RED << " [" << b.status << "]" << Color::RESET << endl;
        }
        
        printSeparator();
        cout << "Customer: " << b.customer.name << " | " << b.customer.phone << endl;
        cout << "Movie: " << b.movieName << " (" << b.genre << ")" << endl;
        cout << "Theater: " << b.theater << endl;
        cout << "Show: " << b.showDate << " at " << b.showTime << endl;
        cout << "Tickets: " << b.numTickets << " | Seats: ";
        for (int j = 0; j < b.numTickets; j++) {
            cout << b.seatNumbers[j];
            if (j < b.numTickets - 1) cout << ", ";
        }
        cout << endl;
        cout << "Total: $" << fixed << setprecision(2) << b.totalPrice << endl;
    }
    
    pauseScreen();
}

void cancelCinemaBooking(vector<CinemaTicket>& bookings) {
    clearScreen();
    printHeader("CANCEL CINEMA BOOKING");
    
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
            saveCinemaBookings(bookings);
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

void searchCinemaBooking(const vector<CinemaTicket>& bookings) {
    clearScreen();
    printHeader("SEARCH CINEMA BOOKINGS");
    
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
            cout << "Customer: " << bookings[i].customer.name << endl;
            cout << "Movie: " << bookings[i].movieName << endl;
            cout << "Show: " << bookings[i].showDate << " at " << bookings[i].showTime << endl;
            cout << "Tickets: " << bookings[i].numTickets << endl;
            cout << "Status: " << bookings[i].status << endl;
            pauseScreen();
            return;
        }
    }
    
    printInfo("No booking found with ID: " + to_string(bookingId));
    pauseScreen();
}

void sortCinemaBookings(vector<CinemaTicket>& bookings) {
    clearScreen();
    printHeader("SORT CINEMA BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to sort.");
        pauseScreen();
        return;
    }
    
    // Bubble sort by total price
    int n = bookings.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bookings[j].totalPrice > bookings[j + 1].totalPrice) {
                CinemaTicket temp = bookings[j];
                bookings[j] = bookings[j + 1];
                bookings[j + 1] = temp;
            }
        }
    }
    
    printSuccess("Bookings sorted by price!");
    viewCinemaBookings(bookings);
}

void loadCinemaBookings(vector<CinemaTicket>& bookings, int& nextId) {
    ifstream file(CINEMA_FILE);
    
    if (!file.is_open()) {
        nextId = 1;
        return;
    }
    
    CinemaTicket booking;
    int maxId = 0;
    
    while (file >> booking.bookingId) {
        file.ignore();
        getline(file, booking.customer.name);
        getline(file, booking.customer.email);
        getline(file, booking.customer.phone);
        getline(file, booking.movieName);
        getline(file, booking.genre);
        getline(file, booking.showDate);
        getline(file, booking.showTime);
        getline(file, booking.theater);
        file >> booking.numTickets;
        
        for (int i = 0; i < booking.numTickets; i++) {
            file >> booking.seatNumbers[i];
        }
        
        file >> booking.pricePerTicket >> booking.totalPrice;
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

void saveCinemaBookings(const vector<CinemaTicket>& bookings) {
    ofstream file(CINEMA_FILE);
    
    if (!file.is_open()) {
        printError("Error saving bookings to file!");
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const CinemaTicket& b = bookings[i];
        file << b.bookingId << endl;
        file << b.customer.name << endl;
        file << b.customer.email << endl;
        file << b.customer.phone << endl;
        file << b.movieName << endl;
        file << b.genre << endl;
        file << b.showDate << endl;
        file << b.showTime << endl;
        file << b.theater << endl;
        file << b.numTickets << endl;
        
        for (int j = 0; j < b.numTickets; j++) {
            file << b.seatNumbers[j] << " ";
        }
        file << endl;
        
        file << b.pricePerTicket << " " << b.totalPrice << endl;
        file << b.status << endl;
    }
    
    file.close();
}

void cinemaTicketsMenu() {
    static vector<CinemaTicket> bookings;
    static int nextId = 1;
    static bool loaded = false;
    
    if (!loaded) {
        loadCinemaBookings(bookings, nextId);
        loaded = true;
    }
    
    while (true) {
        clearScreen();
        printHeader("CINEMA TICKET BOOKING");
        
        cout << Color::BOLD << "\n1. " << Color::RESET << "View Available Movies" << endl;
        cout << Color::BOLD << "2. " << Color::RESET << "Book Cinema Tickets" << endl;
        cout << Color::BOLD << "3. " << Color::RESET << "View My Bookings" << endl;
        cout << Color::BOLD << "4. " << Color::RESET << "Search Booking" << endl;
        cout << Color::BOLD << "5. " << Color::RESET << "Sort Bookings" << endl;
        cout << Color::BOLD << "6. " << Color::RESET << "Cancel Booking" << endl;
        cout << Color::BOLD << "7. " << Color::RESET << "Export Receipt to PDF" << endl;
        cout << Color::BOLD << "0. " << Color::RESET << "Back to Main Menu" << endl;
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 7);
        
        switch (choice) {
            case 1:
                displayAvailableMovies();
                pauseScreen();
                break;
            case 2:
                bookCinemaTicket(bookings, nextId);
                break;
            case 3:
                viewCinemaBookings(bookings);
                break;
            case 4:
                searchCinemaBooking(bookings);
                break;
            case 5:
                sortCinemaBookings(bookings);
                break;
            case 6:
                cancelCinemaBooking(bookings);
                break;
            case 7: {
                clearScreen();
                printHeader("EXPORT RECEIPT TO PDF");
                int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
                string htmlPath = "receipts/cinema_ticket_" + to_string(bookingId) + ".html";
                
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
