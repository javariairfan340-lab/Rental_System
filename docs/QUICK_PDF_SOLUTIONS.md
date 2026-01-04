# Quick PDF Solutions

## 🚀 You Have 3 Options

### Option 1: Install wkhtmltopdf (Recommended - One Time)
```bash
brew install wkhtmltopdf
```
After installation, the PDF export (option 7) will work automatically!

---

### Option 2: Use Browser (No Installation Required)

**Method A: From the program**
When you see the error message, it shows you the file path. Just run:
```bash
open receipts/car_rental_4.html
```
Then press `Cmd+P` → "Save as PDF"

**Method B: Use the viewer script**
```bash
./view_receipt.sh receipts/car_rental_4.html
```
This opens the receipt in your browser with instructions.

---

### Option 3: Python weasyprint
```bash
pip3 install weasyprint
```

---

## 💡 Recommended Workflow

**For now (without wkhtmltopdf):**
1. Generate HTML receipt when booking (choose 'y')
2. Note the booking ID
3. Open Terminal and run:
   ```bash
   open receipts/car_rental_4.html
   ```
4. Press `Cmd+P` → "Save as PDF"

**After installing wkhtmltopdf:**
1. Generate HTML receipt when booking
2. Use option 7 "Export Receipt to PDF"
3. Enter booking ID
4. PDF created automatically!

---

## 🎯 Quick Commands

```bash
# Install PDF converter (one-time)
brew install wkhtmltopdf

# View receipt in browser
open receipts/car_rental_4.html

# Or use the helper script
./view_receipt.sh receipts/car_rental_4.html

# Convert all receipts (after installing wkhtmltopdf)
python3 convert_receipts_to_pdf.py
```

---

## ✅ Best Solution

**Just run this once:**
```bash
brew install wkhtmltopdf
```

Then option 7 in the program will work perfectly! 🎉
