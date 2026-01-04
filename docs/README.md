# Complete C++ Reservation System

A comprehensive reservation management system built in C++ with a colorful terminal UI.

## Features

### 5 Reservation Modules
1. **🚗 Car Rental** - Rent various car models with flexible pricing
2. **✈️ Air Ticketing** - Book flights with multiple class options
3. **🚌 Bus Reservation** - Reserve bus tickets with seat selection
4. **🚆 Train Tickets** - Book train tickets with class preferences
5. **🎬 Cinema Tickets** - Book movie tickets with seat selection

### Programming Concepts Covered
- ✅ **Conditionals**: if/else and switch-case statements
- ✅ **Loops**: for and while loops
- ✅ **Functions**: Call by reference, call by value, function overloading
- ✅ **Arrays**: Fixed-size arrays for seat numbers
- ✅ **Vectors**: Dynamic storage for bookings
- ✅ **Structs**: Custom data structures for all reservation types
- ✅ **File Handling**: Persistent storage using text files
- ✅ **Sorting**: Bubble sort and selection sort algorithms
- ✅ **Searching**: Linear search with function overloading
- ✅ **Colorful Output**: ANSI color codes for enhanced UI

## Compilation

### Using the compile script (Quick):
```bash
chmod +x compile.sh
./compile.sh
```

### Using Makefile:
```bash
make
```

### Manual compilation:
```bash
g++ -std=c++11 -Wall -o reservation_system main.cpp utils.cpp car_rental.cpp air_ticketing.cpp bus_reservation.cpp train_reservation.cpp cinema_tickets.cpp
```

## Running the Program

```bash
./reservation_system
```

## File Structure

```
rental_C++/
├── main.cpp                 # Main application entry point
├── utils.h/cpp             # Utility functions and colors
├── structures.h            # All struct definitions
├── car_rental.h/cpp        # Car rental module
├── air_ticketing.h/cpp     # Air ticketing module
├── bus_reservation.h/cpp   # Bus reservation module
├── train_reservation.h/cpp # Train reservation module
├── cinema_tickets.h/cpp    # Cinema tickets module
├── Makefile                # Build configuration
├── compile.sh              # Quick compile script
└── README.md               # This file
```

## Data Files (Auto-generated)

The following files are created automatically when you make bookings:
- `car_rentals.txt` - Car rental bookings
- `air_tickets.txt` - Flight bookings
- `bus_tickets.txt` - Bus reservations
- `train_tickets.txt` - Train bookings
- `cinema_tickets.txt` - Cinema ticket bookings

## Features by Module

### Car Rental
- View 8 different car models
- Book cars with date selection
- View, search, sort, and cancel bookings
- Pricing based on rental duration

### Air Ticketing
- 6 international flight routes
- Multiple class options (Economy, Business, First)
- Multi-passenger booking support
- Search by destination or booking ID

### Bus Reservation
- 5 bus routes
- Seat number selection
- Express, Deluxe, and Standard options
- Route-based pricing

### Train Reservation
- 5 train routes
- Class selection (Sleeper, AC, First Class)
- Seat number assignment
- Long-distance routes

### Cinema Tickets
- 5 current movies
- Multiple showtimes per movie
- Multi-ticket booking (up to 10)
- Individual seat selection for each ticket

## Clean Build

To remove compiled files:
```bash
make clean
```

To remove data files:
```bash
make clean-data
```

To remove everything:
```bash
make clean-all
```

## Requirements

- C++ compiler with C++11 support (g++, clang++)
- Terminal with ANSI color support (macOS/Linux)
- Make (optional, for using Makefile)

## Author

Built as a comprehensive C++ programming project demonstrating:
- Object-oriented design with structs
- File I/O operations
- Algorithm implementation (sorting/searching)
- User input validation
- Modular code organization
- Terminal UI design

Enjoy using the Complete Reservation System! 🎉
