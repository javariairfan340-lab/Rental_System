# Train & Cinema Updates

## 🚆 Train Seat Availability - 3 Classes!

### New Features
Train reservations now include **three-class seat tracking**:
- **Sleeper Class** (Normal) - Budget-friendly
- **AC Class** (Premium) - Comfortable
- **First Class** - Luxury

### Display Format
```
Seats (S/A/F): 100/50/20
```
Where:
- **S** = Sleeper seats
- **A** = AC seats  
- **F** = First Class seats

### Seat Capacity by Train

| Train | Route | Sleeper | AC | First Class |
|-------|-------|---------|-----|-------------|
| T101 Express Line | NY → Boston | 100 | 50 | 20 |
| T202 Coast Runner | LA → San Diego | 120 | 40 | 15 |
| T303 Midwest Express | Chicago → St. Louis | 110 | 45 | 18 |
| T404 Southern Star | Atlanta → Miami | 90 | 55 | 22 |
| T505 Northeast Corridor | DC → NY | 105 | 48 | 20 |
| T606 Pacific Express | Seattle → SF | 95 | 60 | 25 |
| T707 Texas Star | Dallas → San Antonio | 115 | 42 | 16 |
| T808 Mountain Line | Denver → Salt Lake | 100 | 52 | 21 |
| T909 Sunshine Express | Tampa → Orlando | 125 | 38 | 14 |
| T010 Capital Corridor | Philly → DC | 108 | 46 | 19 |

### How It Works

1. **View Trains** - See seat availability for all classes
2. **Select Train** - Choose your route
3. **Select Class** - Pick Sleeper/AC/First Class
4. **System Validates** - Checks if seats available in chosen class
5. **If Available** → Booking confirmed & seat deducted
6. **If Full** → Error message with suggestion

**Example Error:**
```
✗ Sorry, no seats available in First Class!
ℹ Please choose a different class or train.
```

### Pricing Structure
- **Sleeper**: $35-$70 (Most affordable)
- **AC**: $70-$140 (Mid-range comfort)
- **First Class**: $130-$250 (Premium luxury)

---

## 🎬 Cinema - 5 More Movies Added!

### Expanded Selection
Cinema now features **15 movies** (up from 10)!

### New Additions
11. **Interstellar** (Sci-Fi) - $16
12. **Inception** (Thriller) - $15
13. **The Dark Knight** (Action) - $17
14. **Avengers: Endgame** (Action) - $19
15. **Joker** (Drama) - $16

### Complete Movie List

| # | Movie | Genre | Price | Showtimes |
|---|-------|-------|-------|-----------|
| 1 | The Matrix Resurrections | Sci-Fi | $15 | 4 shows |
| 2 | Dune: Part Two | Adventure | $18 | 4 shows |
| 3 | Oppenheimer | Biography | $16 | 3 shows |
| 4 | Barbie | Comedy | $14 | 3 shows |
| 5 | Mission Impossible | Action | $17 | 4 shows |
| 6 | Avatar: The Way of Water | Sci-Fi | $19 | 4 shows |
| 7 | Guardians of the Galaxy 3 | Action | $16 | 3 shows |
| 8 | Spider-Man: Spider-Verse | Animation | $15 | 4 shows |
| 9 | The Batman | Action | $17 | 3 shows |
| 10 | Top Gun: Maverick | Action | $18 | 4 shows |
| 11 | **Interstellar** | **Sci-Fi** | **$16** | **3 shows** |
| 12 | **Inception** | **Thriller** | **$15** | **4 shows** |
| 13 | **The Dark Knight** | **Action** | **$17** | **3 shows** |
| 14 | **Avengers: Endgame** | **Action** | **$19** | **4 shows** |
| 15 | **Joker** | **Drama** | **$16** | **4 shows** |

### Genre Variety
- **Action**: 7 movies
- **Sci-Fi**: 4 movies
- **Drama/Thriller**: 2 movies
- **Adventure/Animation/Comedy/Biography**: 1 each

---

## 📊 Complete System Status

### Availability Tracking Summary

| Service | Items | Availability Tracking | Status |
|---------|-------|----------------------|--------|
| ✈️ Airlines | 15 flights | 3 classes (E/B/F) | ✅ Complete |
| 🚗 Cars | 15 models | Per vehicle | ✅ Complete |
| 🚌 Buses | 10 routes | Per seat | ✅ Complete |
| 🚆 **Trains** | 10 routes | **3 classes (S/A/F)** | ✅ **NEW!** |
| 🎬 **Cinema** | **15 movies** | Not tracked | ✅ **Expanded!** |

---

## 🎯 What's New

### Train Improvements
✅ **3-Class System**: Sleeper, AC, First Class
✅ **Seat Tracking**: Real-time availability per class
✅ **Smart Validation**: Prevents booking unavailable classes
✅ **Auto-Deduction**: Updates inventory after booking
✅ **Clear Display**: Shows seats for all classes (S/A/F)

### Cinema Improvements
✅ **50% More Movies**: 15 total (was 10)
✅ **Classic Blockbusters**: Interstellar, Inception, Dark Knight
✅ **Recent Hits**: Avengers Endgame, Joker
✅ **Genre Diversity**: Added Thriller and Drama
✅ **More Showtimes**: Multiple daily screenings

---

## 🚀 Try It Out!

```bash
./reservation_system
```

### Test Train Seats:
1. Go to **Train Reservation**
2. View trains - see the 3-class seat counts
3. Book a First Class ticket
4. View trains again - see First Class count reduced!
5. Try booking when a class is full

### Explore New Movies:
1. Go to **Cinema Tickets**
2. Browse 15 movies
3. Check out classics like Inception & Interstellar
4. Book tickets for your favorite!

---

## 💡 Programming Concepts

### Train Seat Tracking
```cpp
struct AvailableTrain {
    // ... other fields ...
    int totalSleeperSeats;
    int availableSleeperSeats;
    int totalACSeats;
    int availableACSeats;
    int totalFirstClassSeats;
    int availableFirstClassSeats;
};
```

### Validation Logic
```cpp
if (availableSeats <= 0) {
    printError("Sorry, no seats available in " + className + "!");
    return;
}
```

### Inventory Update
```cpp
if (classChoice == 1) {
    availableTrains[choice].availableSleeperSeats--;
} // Similar for AC and First Class
```

---

## 🌟 System Highlights

**Total Inventory:**
- 15 Flights (3 classes each)
- 15 Car Models
- 10 Bus Routes
- 10 Train Routes (3 classes each)
- 15 Movies

**Availability Tracking:**
- Airlines: ✅ Yes (3 classes)
- Cars: ✅ Yes (per vehicle)
- Buses: ✅ Yes (per seat)
- Trains: ✅ **Yes (3 classes)** 🆕
- Cinema: ❌ No (unlimited seats)

**Total Options:** **65 different services** to choose from!

---

## 📝 Quick Reference

### Train Class Names
- **User sees**: "Sleeper", "AC", "First Class"
- **Display shows**: S/A/F format
- **Prices**: Sleeper < AC < First Class

### Movie Genres
- Action (7), Sci-Fi (4), Drama (1), Thriller (1)
- Comedy (1), Biography (1), Adventure (1), Animation (1)

---

**Enjoy your enhanced reservation system with train seat tracking and more movies!** 🎉
