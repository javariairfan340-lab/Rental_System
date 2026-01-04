# Bus Seat Availability - Update

## ✅ Bus Reservation Now Includes Seat Tracking!

### 🚌 **Bus Seat Availability**

Each bus now shows real-time seat availability:

**Display Format:**
```
Seats Avail: 40/40
```
Means 40 seats available out of 40 total

**Bus Capacity:**
- **Express Buses**: 40-42 seats
- **Deluxe Buses**: 35-38 seats  
- **Standard Buses**: 45 seats
- **Luxury Buses**: 30-32 seats

### 📊 Bus Inventory

| Bus | Route | Type | Total Seats | Initially Available |
|-----|-------|------|-------------|---------------------|
| B101 | New York → Washington DC | Express | 40 | 40 |
| B202 | Los Angeles → San Francisco | Deluxe | 35 | 35 |
| B303 | Chicago → Detroit | Standard | 45 | 45 |
| B404 | Miami → Orlando | Express | 40 | 40 |
| B505 | Boston → New York | Luxury | 30 | 30 |
| B606 | Seattle → Portland | Express | 42 | 42 |
| B707 | Dallas → Houston | Deluxe | 38 | 38 |
| B808 | Philadelphia → Baltimore | Standard | 45 | 45 |
| B909 | San Diego → Los Angeles | Luxury | 32 | 32 |
| B010 | Phoenix → Las Vegas | Express | 40 | 40 |

### 🎯 How It Works

1. **View Available Buses** - See seat availability for each route
2. **Select Bus** - Choose your preferred bus
3. **System Checks Availability** - Validates seats are available
4. **If Available** → Booking confirmed & seat count decremented
5. **If Full** → Error message displayed

**Example Error:**
```
✗ Sorry, this bus is fully booked!
ℹ No seats available on B505 (Boston → New York)
```

### 📈 Complete Availability Tracking

Your reservation system now has availability tracking for:

✅ **Airline Seats** (Economy/Business/First Class)
✅ **Rental Cars** (15 different models)
✅ **Bus Seats** (10 different routes)

### 💡 Benefits

- **Prevents Overbooking**: Can't book seats that don't exist
- **Real-time Updates**: See exactly how many seats are left
- **Smart Validation**: System automatically checks before confirming
- **User-Friendly**: Clear messages when buses are full

### 🚀 Try It!

```bash
./reservation_system
```

1. Go to **Bus Reservation**
2. View available buses - notice the seat counts
3. Make a booking - watch the available seats decrease!
4. Try booking when a bus is nearly full

Enjoy your enhanced bus reservation system! 🎉
