# Availability Tracking - New Features

## ✅ What's New

### ✈️ **Airline Seat Availability**

Each flight now shows available seats for all classes:
- **Economy Class**: 120-220 seats per flight
- **Business Class**: 20-60 seats per flight  
- **First Class**: 6-25 seats per flight

**Display Format:**
```
Seats (E/B/F): 150/30/10
```
Where E=Economy, B=Business, F=First Class

**Features:**
- Real-time seat availability checking
- Prevents overbooking
- Automatic seat deduction after booking
- Clear error messages when seats unavailable

**Example:**
```
Number of Passengers: 5

✗ Not enough seats available!
ℹ Available seats in Business: 3
```

### 🚗 **Car Rental Availability**

Each car model now shows inventory status:
- Total cars in fleet
- Currently available cars

**Display Format:**
```
Available: 8/10
```
Means 8 cars available out of 10 total

**Car Inventory:**
- Toyota Camry: 10 cars
- Honda Accord: 8 cars
- Ford Mustang: 5 cars
- Tesla Model 3: 7 cars
- BMW X5: 6 cars
- Mercedes-Benz C-Class: 4 cars
- Jeep Wrangler: 8 cars
- Chevrolet Suburban: 6 cars
- Audi A4: 5 cars
- Porsche 911: 3 cars (limited!)
- Tesla Model S: 5 cars
- Range Rover: 4 cars
- Nissan Altima: 12 cars
- Mazda CX-5: 9 cars
- Lexus ES: 5 cars

**Features:**
- Real-time car availability checking
- Prevents double-booking
- Automatic inventory deduction
- Clear messages when cars unavailable

**Example:**
```
✗ Sorry, this car is not available!
ℹ All Porsche 911 are currently rented.
```

## 🎯 How It Works

### Flight Booking Process
1. View available flights with seat counts
2. Select flight and class
3. Enter number of passengers
4. **System checks seat availability**
5. If enough seats → Booking confirmed & seats deducted
6. If not enough seats → Error message with available count

### Car Rental Process
1. View available cars with inventory counts
2. Select desired car model
3. **System checks car availability**
4. If car available → Booking confirmed & count decremented
5. If no cars available → Error message

## 📊 Availability Display

### In Flight Listings
```
No.  Flight  Airline            Route                Time      Economy    Seats (E/B/F)
1    AA101   American Airlines  New York-Los Angeles 08:00     $250.00    150/30/10
2    UA202   United Airlines    Chicago-Miami        10:15     $180.00    140/25/8
```

### In Car Listings
```
No.  Model                     Type       Price/Day    Available
1    Toyota Camry              Sedan      $50.00       10/10
2    Honda Accord              Sedan      $55.00       8/8
3    Ford Mustang              Sports     $120.00      5/5
```

## 🔄 Dynamic Updates

- **After Each Booking**: Available counts automatically decrease
- **Real-time Display**: Always shows current availability
- **Persistent**: Availability persists across program restarts (in memory)

## 💡 Benefits

1. **Prevents Overbooking**: Can't book more seats/cars than available
2. **Transparency**: Users see exactly what's available
3. **Better Planning**: Users can choose alternatives if preferred option is full
4. **Realistic Simulation**: Mimics real-world reservation systems

## 🚀 Try It Out!

1. Run the program: `./reservation_system`
2. Go to Air Ticketing or Car Rental
3. View available options - notice the availability counts
4. Make multiple bookings and watch the counts decrease!
5. Try to book when availability is low to see the validation

## 📝 Notes

- Availability resets when you restart the program (stored in memory)
- To make it persistent, would need to save/load availability data to files
- Current implementation is perfect for demonstrating the concept!

Enjoy the enhanced reservation system with smart availability tracking! 🎉
