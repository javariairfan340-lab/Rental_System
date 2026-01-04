# Quick Start Guide - C++ Reservation System

## 🚀 Running the Application

```bash
cd /Users/asadirfan358/Documents/rental_C++
./reservation_system
```

## 📖 How to Use Each Module

### 1. 🚗 Car Rental
1. Select option `1` from main menu
2. Choose `2` to book a car
3. Enter customer details (name, email, phone)
4. Select a car from the list (1-8)
5. Enter pickup date, return date, and number of days
6. Receive booking confirmation with ID

**Available Cars**:
- Toyota Camry (Sedan) - $50/day
- Honda Accord (Sedan) - $55/day
- Ford Mustang (Sports) - $120/day
- Tesla Model 3 (Electric) - $100/day
- BMW X5 (SUV) - $150/day
- Mercedes-Benz C-Class (Luxury) - $180/day
- Jeep Wrangler (SUV) - $90/day
- Chevrolet Suburban (SUV) - $110/day

### 2. ✈️ Air Ticketing
1. Select option `2` from main menu
2. Choose `2` to book a flight
3. Enter passenger details
4. Select flight (1-6)
5. Enter departure date
6. Choose class (Economy/Business/First)
7. Enter number of passengers
8. Get booking confirmation

**Available Flights**:
- AA101: New York → Los Angeles
- UA202: Chicago → Miami
- DL303: Boston → Seattle
- SW404: Dallas → Denver
- BA505: London → New York
- EK606: Dubai → London

### 3. 🚌 Bus Reservation
1. Select option `3` from main menu
2. Choose `2` to book a ticket
3. Enter passenger details
4. Select bus route (1-5)
5. Enter travel date
6. Choose seat number
7. Receive confirmation

**Available Routes**:
- B101: New York → Washington DC
- B202: Los Angeles → San Francisco
- B303: Chicago → Detroit
- B404: Miami → Orlando
- B505: Boston → New York

### 4. 🚆 Train Reservation
1. Select option `4` from main menu
2. Choose `2` to book a ticket
3. Enter passenger details
4. Select train (1-5)
5. Enter travel date
6. Choose class (Sleeper/AC/First Class)
7. Select seat number (1-100)
8. Get confirmation

**Available Trains**:
- T101 Express Line: New York → Boston
- T202 Coast Runner: Los Angeles → San Diego
- T303 Midwest Express: Chicago → St. Louis
- T404 Southern Star: Atlanta → Miami
- T505 Northeast Corridor: Washington DC → New York

### 5. 🎬 Cinema Tickets
1. Select option `5` from main menu
2. Choose `2` to book tickets
3. Enter customer details
4. Select movie (1-5)
5. Enter show date
6. Choose showtime
7. Enter number of tickets (1-10)
8. Select seat numbers for each ticket
9. Receive confirmation

**Now Showing**:
- The Matrix Resurrections (Sci-Fi) - $15
- Dune: Part Two (Adventure) - $18
- Oppenheimer (Biography) - $16
- Barbie (Comedy) - $14
- Mission Impossible (Action) - $17

## 🔍 Common Operations

### View Bookings
- Select option `3` in any module menu
- See all your bookings with details and status

### Search Bookings
- Select option `4` in any module menu
- Search by booking ID or other criteria
- View specific booking details

### Sort Bookings
- Select option `5` in any module menu
- Sort by price, date, or booking ID
- View sorted results

### Cancel Booking
- Select option `6` in any module menu
- Enter booking ID to cancel
- Booking status changes to "Cancelled"

## 💾 Data Files

All bookings are automatically saved to:
- `car_rentals.txt` - Car bookings
- `air_tickets.txt` - Flight bookings
- `bus_tickets.txt` - Bus tickets
- `train_tickets.txt` - Train tickets
- `cinema_tickets.txt` - Movie tickets

**Data persists** between program runs!

## 🛠️ Rebuilding

If you need to recompile:

```bash
# Quick method
./compile.sh

# Using Makefile
make clean
make

# Manual
g++ -std=c++11 -Wall -o reservation_system main.cpp utils.cpp car_rental.cpp air_ticketing.cpp bus_reservation.cpp train_reservation.cpp cinema_tickets.cpp
```

## 🧹 Cleaning Up

Remove compiled files:
```bash
make clean
```

Remove all data files:
```bash
make clean-data
```

Remove everything:
```bash
make clean-all
```

## 💡 Tips

1. **Booking IDs**: Save your booking IDs for future reference
2. **Data Persistence**: All bookings are saved automatically
3. **Input Validation**: The system validates all inputs
4. **Colorful UI**: Enjoy the colorful terminal interface
5. **Multiple Bookings**: You can make multiple bookings in one session

## ❓ Troubleshooting

**Problem**: Colors not showing
- **Solution**: Use a terminal that supports ANSI colors (macOS Terminal, iTerm2, Linux terminals)

**Problem**: Compilation errors
- **Solution**: Ensure you have g++ with C++11 support installed

**Problem**: Data not persisting
- **Solution**: Check file permissions in the directory

**Problem**: Invalid input errors
- **Solution**: Follow the prompts carefully and enter values within the specified ranges

## 📞 Features Summary

✅ 5 Complete Reservation Systems
✅ Colorful Terminal UI
✅ File-Based Data Persistence
✅ Input Validation
✅ Sorting & Searching
✅ Booking Management (View/Cancel)
✅ Professional Confirmations
✅ User-Friendly Navigation

Enjoy using the Complete Reservation System! 🎉
