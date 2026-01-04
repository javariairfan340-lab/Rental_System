# Enhanced Features - Receipt Generation Guide

## 📄 HTML Receipt Generation

After making a booking in any module, you'll be prompted:
```
Generate receipt? (y/n):
```

Type `y` or `Y` to generate a professional HTML receipt.

## 📁 Receipt Location

All receipts are saved in the `receipts/` directory with the following naming convention:
- Car Rental: `receipts/car_rental_<booking_id>.html`
- Air Ticketing: `receipts/air_ticket_<booking_id>.html`
- Bus Tickets: `receipts/bus_ticket_<booking_id>.html`
- Train Tickets: `receipts/train_ticket_<booking_id>.html`
- Cinema Tickets: `receipts/cinema_ticket_<booking_id>.html`

## 🖨️ Converting to PDF

### Method 1: Using a Web Browser (Recommended)
1. Open the HTML receipt file in any web browser (Chrome, Safari, Firefox, etc.)
2. Press `Cmd+P` (Mac) or `Ctrl+P` (Windows/Linux)
3. Select "Save as PDF" as the destination
4. Click "Save"

### Method 2: Using Command Line (Mac)
```bash
# Navigate to receipts directory
cd receipts

# Convert HTML to PDF using built-in tools
cupsfilter car_rental_1.html > car_rental_1.pdf
```

### Method 3: Using wkhtmltopdf (All platforms)
```bash
# Install wkhtmltopdf first
# Mac: brew install wkhtmltopdf
# Linux: sudo apt-get install wkhtmltopdf

# Convert HTML to PDF
wkhtmltopdf receipts/air_ticket_1.html receipts/air_ticket_1.pdf
```

## 🎨 Receipt Features

Each receipt includes:
- **Professional Styling**: Color-coded by service type
- **Complete Booking Details**: All relevant information
- **Customer Information**: Name, email, phone
- **Service Details**: Specific to each booking type
- **Pricing Breakdown**: Clear cost information
- **Timestamp**: Generation date and time
- **Booking Status**: Active/Confirmed/Cancelled

### Receipt Color Themes
- 🚗 **Car Rental**: Blue theme
- ✈️ **Air Ticketing**: Purple gradient
- 🚌 **Bus Tickets**: Orange theme
- 🚆 **Train Tickets**: Teal theme
- 🎬 **Cinema Tickets**: Dark theme with red accents

## 📊 Expanded Inventory

### 🚗 Car Rental (15 vehicles)
- Sedans: Toyota Camry, Honda Accord, Nissan Altima
- Sports: Ford Mustang, Porsche 911
- Electric: Tesla Model 3, Tesla Model S
- SUVs: BMW X5, Jeep Wrangler, Chevrolet Suburban, Range Rover, Mazda CX-5
- Luxury: Mercedes-Benz C-Class, Audi A4, Lexus ES

### ✈️ Air Ticketing (15 flights)
**Domestic Routes:**
- New York ↔ Los Angeles (AA101, AA107)
- Chicago → Miami (UA202)
- Boston → Seattle (DL303)
- Dallas → Denver (SW404)
- Houston → Los Angeles (UA208)
- Atlanta → Seattle (DL309)

**International Routes:**
- London ↔ New York (BA505, LH510)
- Dubai → London (EK606)
- Frankfurt → New York (LH510)
- Paris → Los Angeles (AF611)
- Doha → London (QR712)
- Singapore → San Francisco (SQ813)
- Tokyo → Los Angeles (JL914)
- Hong Kong → New York (CX015)

### 🚌 Bus Reservation (10 routes)
- New York → Washington DC
- Los Angeles → San Francisco
- Chicago → Detroit
- Miami → Orlando
- Boston → New York
- Seattle → Portland
- Dallas → Houston
- Philadelphia → Baltimore
- San Diego → Los Angeles
- Phoenix → Las Vegas

### 🚆 Train Reservation (10 routes)
- New York → Boston
- Los Angeles → San Diego
- Chicago → St. Louis
- Atlanta → Miami
- Washington DC → New York
- Seattle → San Francisco
- Dallas → San Antonio
- Denver → Salt Lake City
- Tampa → Orlando
- Philadelphia → Washington DC

### 🎬 Cinema Tickets (10 movies)
- The Matrix Resurrections (Sci-Fi)
- Dune: Part Two (Adventure)
- Oppenheimer (Biography)
- Barbie (Comedy)
- Mission Impossible (Action)
- Avatar: The Way of Water (Sci-Fi)
- Guardians of the Galaxy 3 (Action)
- Spider-Man: Across the Spider-Verse (Animation)
- The Batman (Action)
- Top Gun: Maverick (Action)

## 💡 Tips

1. **Automatic Directory Creation**: The `receipts/` folder is created automatically when you generate your first receipt
2. **Browser Compatibility**: HTML receipts work in all modern browsers
3. **Print-Friendly**: Receipts are optimized for printing
4. **Responsive Design**: Receipts look good on all screen sizes
5. **Professional Format**: Suitable for record-keeping and reimbursement

## 🔧 Troubleshooting

**Receipt not generating?**
- Check if you have write permissions in the project directory
- Ensure the `receipts/` directory can be created

**Can't open HTML file?**
- Right-click the file and select "Open With" → Your preferred browser
- Or drag and drop the file into an open browser window

**PDF conversion issues?**
- Use the browser print-to-PDF method (most reliable)
- Ensure wkhtmltopdf is properly installed if using command line

Enjoy your professional receipts! 🎉
