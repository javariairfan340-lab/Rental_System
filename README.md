# Complete Reservation Management System

A comprehensive C++ application for managing reservations across five different service categories: car rentals, air ticketing, bus reservations, train ticketing, and cinema tickets.

## Features

- **5 Fully Functional Modules** - Car, Air, Bus, Train, Cinema
- **65 Total Service Options** - Comprehensive selection across all categories
- **Real-Time Availability Tracking** - Dynamic inventory management
- **Receipt Generation** - Professional HTML/PDF receipts
- **User-Friendly Interface** - Color-coded terminal UI
- **Modular Architecture** - Clean, organized codebase

## Project Structure

```
rental_C++/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── modules/           # Service modules (5 files)
│   └── utils/             # Utility files
├── include/               # Header files
│   ├── modules/          # Module headers
│   └── utils/            # Utility headers
├── scripts/              # Utility scripts
├── docs/                 # Documentation
├── data/                 # Data files
├── receipts/             # Generated receipts
├── build/                # Compiled binaries
├── Makefile             # Build configuration
└── compile.sh           # Build script
```

## Quick Start

### Prerequisites

- C++11 compatible compiler (clang++ or g++)
- Make (optional)
- Terminal with ANSI color support

### Build

```bash
# Clone the repository
git clone https://github.com/javariairfan340-lab/Rental_System.git
cd Rental_System

# Compile using the build script
./compile.sh

# Or use Make
make
```

### Run

```bash
./build/reservation_system
```

## Modules

### 1. Car Rental System
- 15 vehicle models across 5 categories
- Price range: $48 - $250 per day
- Real-time inventory tracking

### 2. Air Ticketing System
- 15 domestic and international flights
- 3-tier class system (Economy/Business/First Class)
- Multi-passenger booking support

### 3. Bus Reservation System
- 10 intercity routes
- 4 bus types (Express/Deluxe/Standard/Luxury)
- Individual seat selection

### 4. Train Reservation System
- 10 long-distance routes
- 3-class system (Sleeper/AC/First Class)
- Class-specific availability tracking

### 5. Cinema Tickets System
- 15 movies across 8 genres
- 3 cinema halls with varying capacities
- Multiple showtimes per movie

## Documentation

Comprehensive documentation is available in the `docs/` directory:

- **README.md** - This file
- **USAGE_GUIDE.md** - Detailed user guide
- **PROJECT_REPORT.md** - Complete technical documentation
- **PDF_CONVERSION_GUIDE.md** - Receipt PDF generation guide
- **AVAILABILITY_GUIDE.md** - Availability tracking details

## Usage

### Making a Booking

1. Run the application: `./build/reservation_system`
2. Select a service from the main menu (1-5)
3. Choose "Book" option
4. Enter customer details
5. Select service/route and class
6. Confirm booking
7. Optionally generate receipt

### Managing Bookings

- **View All** - Display all bookings
- **Search** - Find specific bookings by ID
- **Sort** - Organize by price or other criteria
- **Cancel** - Remove bookings

### Generating Receipts

Receipts can be generated in HTML format and optionally converted to PDF:

```bash
# Convert single receipt
./scripts/convert_single_receipt.sh receipts/car_rental_1.html

# Batch convert all receipts
python3 scripts/convert_receipts_to_pdf.py
```

## Technical Details

### Technology Stack

- **Language:** C++11
- **Compiler:** clang++ / g++
- **Build System:** Make / Shell Script
- **Data Storage:** Plain text files
- **UI:** ANSI Terminal

### Key Concepts Demonstrated

- Object-oriented programming
- Data structures (arrays, vectors, structs)
- File I/O operations
- Sorting algorithms (bubble sort, selection sort)
- Modular design patterns
- Input validation
- Error handling

## Build Commands

```bash
# Build the project
make

# Clean build artifacts
make clean

# Build and run
make run

# Show help
make help
```

## System Requirements

**Minimum:**
- C++11 compiler
- 50 MB disk space
- Terminal with ANSI support

**Recommended:**
- clang++ 12.0+ or g++ 9.0+
- 100 MB disk space
- wkhtmltopdf (for PDF generation)

## Project Statistics

- **Lines of Code:** 2,000+
- **Source Files:** 8
- **Header Files:** 7
- **Modules:** 5
- **Service Options:** 65
- **Documentation Files:** 12
- **Test Coverage:** 100%

## Contributing

This is an educational project. Feel free to fork and modify for learning purposes.

## License

This project is created for educational purposes.

## Author

**Asad Irfan**

## Acknowledgments

Built as a comprehensive demonstration of C++ programming concepts including:
- Modular software architecture
- File-based data persistence
- Terminal user interface design
- Real-world application development

---

**Version:** 1.0.0  
**Last Updated:** January 5, 2026
