#include "utils.h"
#include "car_rental.h"
#include "air_ticketing.h"
#include "bus_reservation.h"
#include "train_reservation.h"
#include "cinema_tickets.h"
#include <iostream>

using namespace std;

void displayWelcomeScreen() {
    clearScreen();
    
    cout << Color::BOLD << Color::CYAN;
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                                  ║\n";
    cout << "  ║        " << Color::YELLOW << "COMPLETE RESERVATION MANAGEMENT SYSTEM" << Color::CYAN << "              ║\n";
    cout << "  ║                                                                  ║\n";
    cout << "  ║        " << Color::GREEN << "Your One-Stop Solution for All Bookings" << Color::CYAN << "              ║\n";
    cout << "  ║                                                                  ║\n";
    cout << "  ╚══════════════════════════════════════════════════════════════════╝\n";
    cout << Color::RESET << endl;
    
    cout << Color::MAGENTA << "  Powered by C++ | File-Based Database | Colorful Terminal UI\n" << Color::RESET;
    printLine('=');
}

void displayMainMenu() {
    cout << Color::BOLD << Color::CYAN << "\n╔═══════════════ MAIN MENU ═══════════════╗" << Color::RESET << endl;
    cout << Color::BOLD << Color::CYAN << "║                                         ║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::YELLOW << "1. " << Color::WHITE 
         << "🚗 Car Rental System              " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::YELLOW << "2. " << Color::WHITE 
         << "✈️  Air Ticketing System           " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::YELLOW << "3. " << Color::WHITE 
         << "🚌 Bus Ticket Reservation         " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::YELLOW << "4. " << Color::WHITE 
         << "🚆 Train Ticket Reservation       " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::YELLOW << "5. " << Color::WHITE 
         << "🎬 Cinema Tickets Booking         " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║                                         ║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║  " << Color::RED << "0. " << Color::WHITE 
         << "Exit Application                  " << Color::CYAN << "║" << Color::RESET << endl;
    
    cout << Color::BOLD << Color::CYAN << "║                                         ║" << Color::RESET << endl;
    cout << Color::BOLD << Color::CYAN << "╚═════════════════════════════════════════╝" << Color::RESET << endl;
}

int main() {
    bool running = true;
    
    displayWelcomeScreen();
    pauseScreen();
    
    while (running) {
        clearScreen();
        displayWelcomeScreen();
        displayMainMenu();
        
        int choice = getValidatedInt("\nEnter your choice: ", 0, 5);
        
        switch (choice) {
            case 1:
                carRentalMenu();
                break;
            case 2:
                airTicketingMenu();
                break;
            case 3:
                busReservationMenu();
                break;
            case 4:
                trainReservationMenu();
                break;
            case 5:
                cinemaTicketsMenu();
                break;
            case 0:
                clearScreen();
                printHeader("THANK YOU!");
                cout << Color::GREEN << "\n  Thank you for using our Reservation System!" << Color::RESET << endl;
                cout << Color::CYAN << "  All your bookings have been saved." << Color::RESET << endl;
                cout << Color::YELLOW << "\n  Goodbye! 👋\n" << Color::RESET << endl;
                printLine('=');
                running = false;
                break;
            default:
                printError("Invalid choice! Please try again.");
                pauseScreen();
        }
    }
    
    return 0;
}
