#include "car_rental.h"
#include "utils.h"
#include "receipt_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

const string CAR_FILE = "data/car_rentals.txt";

// Available cars array
struct AvailableCar {
    string model;
    string type;
    double pricePerDay;
    int totalCars;
    int availableCars;
};

AvailableCar availableCars[] = {
    {"Toyota Camry", "Sedan", 50.0, 10, 10},
    {"Honda Accord", "Sedan", 55.0, 8, 8},
    {"Ford Mustang", "Sports", 120.0, 5, 5},
    {"Tesla Model 3", "Electric", 100.0, 7, 7},
    {"BMW X5", "SUV", 150.0, 6, 6},
    {"Mercedes-Benz C-Class", "Luxury", 180.0, 4, 4},
    {"Jeep Wrangler", "SUV", 90.0, 8, 8},
    {"Chevrolet Suburban", "SUV", 110.0, 6, 6},
    {"Audi A4", "Luxury", 160.0, 5, 5},
    {"Porsche 911", "Sports", 250.0, 3, 3},
    {"Tesla Model S", "Electric", 140.0, 5, 5},
    {"Range Rover", "SUV", 200.0, 4, 4},
    {"Nissan Altima", "Sedan", 48.0, 12, 12},
    {"Mazda CX-5", "SUV", 85.0, 9, 9},
    {"Lexus ES", "Luxury", 170.0, 5, 5}
};

const int NUM_CARS = 15;

// Display available cars
void displayAvailableCars() {
    clearScreen();
    printHeader("AVAILABLE CARS FOR RENT");
    
    cout << Color::BOLD << left << setw(5) << "No." << setw(25) << "Model" 
         << setw(15) << "Type" << setw(15) << "Price/Day" << setw(12) << "Available" << Color::RESET << endl;
    printSeparator();
    
    for (int i = 0; i < NUM_CARS; i++) {
        cout << Color::YELLOW << left << setw(5) << (i + 1) 
             << Color::WHITE << setw(25) << availableCars[i].model
             << Color::CYAN << setw(15) << availableCars[i].type
             << Color::GREEN << "$" << setw(13) << fixed << setprecision(2) << availableCars[i].pricePerDay
             << Color::YELLOW << availableCars[i].availableCars << "/" << availableCars[i].totalCars
             << Color::RESET << endl;
    }
    printSeparator();
}

// Book a car (call by reference to modify bookings vector)
void bookCar(vector<CarRental>& bookings, int& nextId) {
    displayAvailableCars();
    
    CarRental newBooking;
    newBooking.bookingId = nextId++;
    
    cout << endl;
    printInfo("Enter customer details:");
    newBooking.customer.name = getValidatedString("Customer Name: ");
    newBooking.customer.email = getValidatedString("Email: ");
    newBooking.customer.phone = getValidatedString("Phone: ");
    
    int carChoice = getValidatedInt("\nSelect car (1-" + to_string(NUM_CARS) + "): ", 1, NUM_CARS);
    
    // Check car availability
    if (availableCars[carChoice - 1].availableCars <= 0) {
        clearScreen();
        printError("Sorry, this car is not available!");
        printInfo("All " + availableCars[carChoice - 1].model + " are currently rented.");
        pauseScreen();
        return;
    }
    
    newBooking.carModel = availableCars[carChoice - 1].model;
    newBooking.carType = availableCars[carChoice - 1].type;
    newBooking.pricePerDay = availableCars[carChoice - 1].pricePerDay;
    
    newBooking.pickupDate = getValidatedString("Pickup Date (DD/MM/YYYY): ");
    newBooking.returnDate = getValidatedString("Return Date (DD/MM/YYYY): ");
    newBooking.days = getValidatedInt("Number of Days: ", 1, 365);
    
    newBooking.totalPrice = newBooking.pricePerDay * newBooking.days;
    newBooking.status = "Active";
    
    // Deduct one car from available inventory
    availableCars[carChoice - 1].availableCars--;
    
    bookings.push_back(newBooking);
    saveCarBookings(bookings);
    
    clearScreen();
    printSuccess("Car booked successfully!");
    cout << Color::BOLD << "\n--- BOOKING CONFIRMATION ---" << Color::RESET << endl;
    cout << "Booking ID: " << Color::YELLOW << newBooking.bookingId << Color::RESET << endl;
    cout << "Customer: " << Color::CYAN << newBooking.customer.name << Color::RESET << endl;
    cout << "Car: " << Color::GREEN << newBooking.carModel << Color::RESET << endl;
    cout << "Total Price: " << Color::GREEN << "$" << fixed << setprecision(2) 
         << newBooking.totalPrice << Color::RESET << endl;
    
    cout << "\n" << Color::CYAN << "Generate receipt? (y/n): " << Color::RESET;
    char receiptChoice;
    cin >> receiptChoice;
    cin.ignore();
    
    if (receiptChoice == 'y' || receiptChoice == 'Y') {
        generateCarRentalReceipt(newBooking);
    }
    
    pauseScreen();
}

// View all car bookings
void viewCarBookings(const vector<CarRental>& bookings) {
    clearScreen();
    printHeader("CAR RENTAL BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings found.");
        pauseScreen();
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const CarRental& b = bookings[i];
        
        cout << Color::BOLD << "\nBooking #" << b.bookingId << Color::RESET;
        if (b.status == "Active") {
            cout << Color::GREEN << " [" << b.status << "]" << Color::RESET << endl;
        } else if (b.status == "Cancelled") {
            cout << Color::RED << " [" << b.status << "]" << Color::RESET << endl;
        } else {
            cout << Color::BLUE << " [" << b.status << "]" << Color::RESET << endl;
        }
        
        printSeparator();
        cout << "Customer: " << b.customer.name << " | " << b.customer.phone << endl;
        cout << "Car: " << b.carModel << " (" << b.carType << ")" << endl;
        cout << "Period: " << b.pickupDate << " to " << b.returnDate << " (" << b.days << " days)" << endl;
        cout << "Total: $" << fixed << setprecision(2) << b.totalPrice << endl;
    }
    
    pauseScreen();
}

// Cancel car booking (call by reference)
void cancelCarBooking(vector<CarRental>& bookings) {
    clearScreen();
    printHeader("CANCEL CAR BOOKING");
    
    if (bookings.empty()) {
        printInfo("No bookings to cancel.");
        pauseScreen();
        return;
    }
    
    int bookingId = getValidatedInt("Enter Booking ID to cancel: ", 1, 999999);
    
    bool found = false;
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingId == bookingId && bookings[i].status == "Active") {
            bookings[i].status = "Cancelled";
            saveCarBookings(bookings);
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

// Function overloading - Search by model (call by value)
void searchCarByModel(const vector<CarRental>& bookings, const string& model) {
    bool found = false;
    
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].carModel.find(model) != string::npos) {
            if (!found) {
                cout << Color::BOLD << "\nSearch Results:" << Color::RESET << endl;
                printSeparator();
                found = true;
            }
            
            cout << "Booking ID: " << bookings[i].bookingId << " | "
                 << bookings[i].customer.name << " | "
                 << bookings[i].carModel << " | "
                 << bookings[i].status << endl;
        }
    }
    
    if (!found) {
        printInfo("No bookings found for model: " + model);
    }
}

// Function overloading - Search by ID
void searchCarById(const vector<CarRental>& bookings, int id) {
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingId == id) {
            cout << Color::BOLD << "\nBooking Found:" << Color::RESET << endl;
            printSeparator();
            cout << "Booking ID: " << bookings[i].bookingId << endl;
            cout << "Customer: " << bookings[i].customer.name << endl;
            cout << "Car: " << bookings[i].carModel << endl;
            cout << "Status: " << bookings[i].status << endl;
            cout << "Total: $" << fixed << setprecision(2) << bookings[i].totalPrice << endl;
            return;
        }
    }
    
    printInfo("No booking found with ID: " + to_string(id));
}

// Search car bookings
void searchCarBooking(const vector<CarRental>& bookings) {
    clearScreen();
    printHeader("SEARCH CAR BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to search.");
        pauseScreen();
        return;
    }
    
    cout << "\n1. Search by Booking ID" << endl;
    cout << "2. Search by Car Model" << endl;
    
    int choice = getValidatedInt("\nEnter choice: ", 1, 2);
    
    if (choice == 1) {
        int id = getValidatedInt("Enter Booking ID: ", 1, 999999);
        searchCarById(bookings, id);
    } else {
        string model = getValidatedString("Enter Car Model: ");
        searchCarByModel(bookings, model);
    }
    
    pauseScreen();
}

// Bubble sort for car bookings by total price
void sortCarBookings(vector<CarRental>& bookings) {
    clearScreen();
    printHeader("SORT CAR BOOKINGS");
    
    if (bookings.empty()) {
        printInfo("No bookings to sort.");
        pauseScreen();
        return;
    }
    
    cout << "\n1. Sort by Price (Low to High)" << endl;
    cout << "2. Sort by Price (High to Low)" << endl;
    cout << "3. Sort by Booking ID" << endl;
    
    int choice = getValidatedInt("\nEnter choice: ", 1, 3);
    
    // Bubble sort implementation
    int n = bookings.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool swap = false;
            
            if (choice == 1 && bookings[j].totalPrice > bookings[j + 1].totalPrice) {
                swap = true;
            } else if (choice == 2 && bookings[j].totalPrice < bookings[j + 1].totalPrice) {
                swap = true;
            } else if (choice == 3 && bookings[j].bookingId > bookings[j + 1].bookingId) {
                swap = true;
            }
            
            if (swap) {
                CarRental temp = bookings[j];
                bookings[j] = bookings[j + 1];
                bookings[j + 1] = temp;
            }
        }
    }
    
    printSuccess("Bookings sorted successfully!");
    viewCarBookings(bookings);
}

// Load car bookings from file
void loadCarBookings(vector<CarRental>& bookings, int& nextId) {
    ifstream file(CAR_FILE);
    
    if (!file.is_open()) {
        nextId = 1;
        return;
    }
    
    CarRental booking;
    int maxId = 0;
    
    while (file >> booking.bookingId) {
        file.ignore();
        getline(file, booking.customer.name);
        getline(file, booking.customer.email);
        getline(file, booking.customer.phone);
        getline(file, booking.carModel);
        getline(file, booking.carType);
        getline(file, booking.pickupDate);
        getline(file, booking.returnDate);
        file >> booking.days >> booking.pricePerDay >> booking.totalPrice;
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

// Save car bookings to file
void saveCarBookings(const vector<CarRental>& bookings) {
    ofstream file(CAR_FILE);
    
    if (!file.is_open()) {
        printError("Error saving bookings to file!");
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); i++) {
        const CarRental& b = bookings[i];
        file << b.bookingId << endl;
        file << b.customer.name << endl;
        file << b.customer.email << endl;
        file << b.customer.phone << endl;
        file << b.carModel << endl;
        file << b.carType << endl;
        file << b.pickupDate << endl;
        file << b.returnDate << endl;
        file << b.days << " " << b.pricePerDay << " " << b.totalPrice << endl;
        file << b.status << endl;
    }
    
    file.close();
}

// Car rental menu
void carRentalMenu() {
    static vector<CarRental> bookings;
    static int nextId = 1;
    static bool loaded = false;
    
    if (!loaded) {
        loadCarBookings(bookings, nextId);
        loaded = true;
    }
    
    while (true) {
        clearScreen();
        printHeader("CAR RENTAL SYSTEM");
        
        cout << Color::BOLD << "\n1. " << Color::RESET << "View Available Cars" << endl;
        cout << Color::BOLD << "2. " << Color::RESET << "Book a Car" << endl;
        cout << Color::BOLD << "3. " << Color::RESET << "View My Bookings" << endl;
        cout << Color::BOLD << "4. " << Color::RESET << "Search Bookings" << endl;
        cout << Color::BOLD << "5. " << Color::RESET << "Sort Bookings" << endl;
        cout << Color::BOLD << "6. " << Color::RESET << "Cancel Booking" << endl;
        cout << Color::BOLD << "7. " << Color::RESET << "Export Receipt to PDF" << endl;
        cout << Color::BOLD << "0. " << Color::RESET << "Back to Main Menu" << endl;
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 7);
        
        switch (choice) {
            case 1:
                displayAvailableCars();
                pauseScreen();
                break;
            case 2:
                bookCar(bookings, nextId);
                break;
            case 3:
                viewCarBookings(bookings);
                break;
            case 4:
                searchCarBooking(bookings);
                break;
            case 5:
                sortCarBookings(bookings);
                break;
            case 6:
                cancelCarBooking(bookings);
                break;
            case 7: {
                clearScreen();
                printHeader("EXPORT RECEIPT TO PDF");
                int bookingId = getValidatedInt("Enter Booking ID: ", 1, 999999);
                string htmlPath = "receipts/car_rental_" + to_string(bookingId) + ".html";
                
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
