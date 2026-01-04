# PDF Export Feature - In-App Integration

## ✅ New Feature: Export Receipt to PDF (Menu Option 7)

Every reservation module now has a **built-in PDF export option**!

---

## 🎯 How to Use

### Step 1: Make a Booking
1. Go to any module (Car/Air/Bus/Train/Cinema)
2. Book a service
3. When prompted "Generate receipt? (y/n):", type `y`
4. HTML receipt is created

### Step 2: Export to PDF
1. In the same module menu, select option **7. Export Receipt to PDF**
2. Enter your booking ID
3. System converts HTML to PDF automatically
4. Choose whether to open the PDF

---

## 📋 Available in All Modules

### 🚗 Car Rental System
```
1. View Available Cars
2. Book a Car
3. View My Bookings
4. Search Bookings
5. Sort Bookings
6. Cancel Booking
7. Export Receipt to PDF  ← NEW!
0. Back to Main Menu
```

### ✈️ Air Ticketing System
```
7. Export Receipt to PDF  ← NEW!
```

### 🚌 Bus Ticket Reservation
```
7. Export Receipt to PDF  ← NEW!
```

### 🚆 Train Ticket Reservation
```
7. Export Receipt to PDF  ← NEW!
```

### 🎬 Cinema Tickets Booking
```
7. Export Receipt to PDF  ← NEW!
```

---

## 💡 Usage Example

```
╔═══════════════ CAR RENTAL SYSTEM ═══════════════╗
║                                                 ║
║  1. View Available Cars                        ║
║  2. Book a Car                                 ║
║  3. View My Bookings                           ║
║  4. Search Bookings                            ║
║  5. Sort Bookings                              ║
║  6. Cancel Booking                             ║
║  7. Export Receipt to PDF                      ║
║                                                 ║
║  0. Back to Main Menu                          ║
║                                                 ║
╚═════════════════════════════════════════════════╝

Enter your choice: 7

================================================================================
  EXPORT RECEIPT TO PDF
================================================================================
Enter Booking ID: 1

Converting to PDF...
✓ PDF created successfully!
ℹ PDF saved as: receipts/car_rental_1.pdf
Open PDF now? (y/n): y

[PDF opens automatically]
```

---

## 🔧 How It Works

### Behind the Scenes

1. **User selects option 7**
2. **Enters booking ID**
3. **System checks** if HTML receipt exists
4. **Calls conversion script** (`convert_single_receipt.sh`)
5. **Creates PDF** in same directory
6. **Optionally opens** the PDF

### File Naming Convention

| Module | HTML Receipt | PDF Receipt |
|--------|-------------|-------------|
| Car | `car_rental_1.html` | `car_rental_1.pdf` |
| Air | `air_ticket_2.html` | `air_ticket_2.pdf` |
| Bus | `bus_ticket_3.html` | `bus_ticket_3.pdf` |
| Train | `train_ticket_4.html` | `train_ticket_4.pdf` |
| Cinema | `cinema_ticket_5.html` | `cinema_ticket_5.pdf` |

---

## 📦 Prerequisites

### One-Time Setup

Install a PDF converter (choose one):

**Option 1: wkhtmltopdf** (Recommended)
```bash
brew install wkhtmltopdf
```

**Option 2: weasyprint**
```bash
pip3 install weasyprint
```

**Option 3: No installation** (Browser method)
- Just open the HTML file in browser
- Press Cmd+P → Save as PDF

---

## ⚠️ Error Handling

### If Receipt Not Found
```
✗ Receipt not found for booking ID: 123
ℹ Generate receipt first by booking and choosing 'y' for receipt generation.
```

**Solution:** Make a booking and generate the HTML receipt first.

### If PDF Converter Not Installed
```
⚠ PDF conversion requires wkhtmltopdf or weasyprint
ℹ Install with: brew install wkhtmltopdf
ℹ Or use browser: open receipts/car_rental_1.html
```

**Solution:** Install wkhtmltopdf or use browser method.

---

## 🎨 Features

✅ **Integrated** - Built into every module menu
✅ **Simple** - Just enter booking ID
✅ **Automatic** - Converts HTML to PDF instantly
✅ **Interactive** - Option to open PDF after creation
✅ **Error-Friendly** - Clear messages if something goes wrong
✅ **Consistent** - Same experience across all modules

---

## 🚀 Quick Workflow

### Complete Booking-to-PDF Flow

1. **Book** a service (option 2 in any module)
2. **Generate HTML** receipt (choose 'y' when prompted)
3. **Export to PDF** (option 7 in same module)
4. **Enter booking ID**
5. **Open PDF** (choose 'y' when prompted)

**Total time:** ~30 seconds!

---

## 📊 Comparison

| Method | Steps | Location | Auto-Open |
|--------|-------|----------|-----------|
| **In-App (Option 7)** | 2 | In menu | ✅ Yes |
| Python script | 1 | Terminal | ❌ No |
| Bash script | 1 | Terminal | ✅ Yes |
| Browser | 3 | Manual | ❌ No |

**Winner:** In-app option 7 for convenience!

---

## 💻 Technical Details

### Function Added to `utils.cpp`

```cpp
void convertReceiptToPDF(const string& htmlFilePath) {
    // Calls external conversion script
    // Handles errors gracefully
    // Offers to open PDF
}
```

### Integration in Each Module

```cpp
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
        printError("Receipt not found...");
    }
    pauseScreen();
    break;
}
```

---

## 📝 Summary

**What's New:**
- Menu option 7 in ALL modules
- One-click PDF export
- Automatic PDF opening
- Smart error handling

**Files Modified:**
- `utils.h` - Added function declaration
- `utils.cpp` - Added PDF conversion function
- `car_rental.cpp` - Added menu option 7
- `air_ticketing.cpp` - Added menu option 7
- `bus_reservation.cpp` - Added menu option 7
- `train_reservation.cpp` - Added menu option 7
- `cinema_tickets.cpp` - Added menu option 7

**Result:**
✨ **Professional PDF export integrated into every module!** ✨

---

**Enjoy your enhanced reservation system with built-in PDF export!** 🎉
