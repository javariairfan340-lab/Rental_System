# PDF Conversion Guide

## 📄 Converting HTML Receipts to PDF

Your reservation system generates HTML receipts. This guide shows you how to convert them to PDF format.

---

## 🚀 Quick Start

### Method 1: Batch Convert All Receipts (Python Script)

Convert all HTML receipts at once:

```bash
python3 convert_receipts_to_pdf.py
```

**What it does:**
- Finds all `.html` files in `receipts/` directory
- Converts each to PDF with the same name
- Shows progress and summary

**Output:**
```
receipts/
├── car_rental_1.html
├── car_rental_1.pdf      ← Created!
├── air_ticket_2.html
├── air_ticket_2.pdf      ← Created!
└── ...
```

---

### Method 2: Convert Single Receipt (Bash Script)

Convert one specific receipt:

```bash
./convert_single_receipt.sh receipts/car_rental_1.html
```

**Features:**
- Converts specified HTML file to PDF
- Automatically opens the PDF after conversion
- Shows clear error messages

---

### Method 3: Browser (Manual - No Installation)

1. Open the HTML file in any browser:
   ```bash
   open receipts/car_rental_1.html
   ```

2. Print to PDF:
   - **Mac**: Press `Cmd+P` → Select "Save as PDF"
   - **Windows/Linux**: Press `Ctrl+P` → Select "Save as PDF"

3. Save in the `receipts/` folder

---

## 📦 Installation

### Prerequisites

You need a PDF converter tool. Choose one:

#### Option 1: wkhtmltopdf (Recommended)

**macOS:**
```bash
brew install wkhtmltopdf
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install wkhtmltopdf
```

**Verify installation:**
```bash
which wkhtmltopdf
```

#### Option 2: weasyprint

**Any OS (requires Python):**
```bash
pip3 install weasyprint
```

**Verify installation:**
```bash
which weasyprint
```

---

## 🎯 Usage Examples

### Example 1: Convert All Receipts

```bash
# Navigate to project directory
cd /Users/asadirfan358/Documents/rental_C++

# Run batch converter
python3 convert_receipts_to_pdf.py
```

**Output:**
```
============================================================
  HTML to PDF Converter - Reservation System
============================================================
🔍 Checking dependencies...
✅ wkhtmltopdf found: /usr/local/bin/wkhtmltopdf

📄 Found 5 HTML receipt(s)
🔄 Converting to PDF...

   Converting: car_rental_1.html → car_rental_1.pdf
   ✅ Created: car_rental_1.pdf
   Converting: air_ticket_2.html → air_ticket_2.pdf
   ✅ Created: air_ticket_2.pdf
   ...

============================================================
✅ Successfully converted: 5
============================================================

📁 PDF receipts saved in: /Users/.../receipts
```

### Example 2: Convert One Receipt

```bash
# Convert specific receipt
./convert_single_receipt.sh receipts/car_rental_3.html
```

**Output:**
```
🔄 Converting HTML to PDF...
   Input:  receipts/car_rental_3.html
   Output: receipts/car_rental_3.pdf

📦 Using wkhtmltopdf...
✅ PDF created successfully: receipts/car_rental_3.pdf

📂 Opening PDF...
```

### Example 3: Using Browser

```bash
# Open in default browser
open receipts/car_rental_1.html

# Or specify browser
google-chrome receipts/car_rental_1.html
firefox receipts/car_rental_1.html
```

Then: `Cmd+P` (Mac) or `Ctrl+P` (Windows/Linux) → "Save as PDF"

---

## 🛠️ Script Features

### Python Script (`convert_receipts_to_pdf.py`)

✅ **Auto-detects** available PDF converter
✅ **Batch processes** all HTML files
✅ **Progress tracking** with colored output
✅ **Error handling** with helpful messages
✅ **Summary report** of conversions

### Bash Script (`convert_single_receipt.sh`)

✅ **Single file** conversion
✅ **Auto-opens** PDF after creation
✅ **Fallback** to multiple converters
✅ **Clear error** messages

---

## 📋 Conversion Options

### wkhtmltopdf Settings

The scripts use these optimized settings:

```bash
wkhtmltopdf \
    --enable-local-file-access \  # Allow local files
    --page-size Letter \           # US Letter size
    --margin-top 10mm \            # Top margin
    --margin-bottom 10mm \         # Bottom margin
    --margin-left 10mm \           # Left margin
    --margin-right 10mm \          # Right margin
    input.html output.pdf
```

### Custom Conversion

For custom settings, use wkhtmltopdf directly:

```bash
# A4 size with larger margins
wkhtmltopdf \
    --enable-local-file-access \
    --page-size A4 \
    --margin-top 20mm \
    --margin-bottom 20mm \
    receipts/car_rental_1.html \
    receipts/car_rental_1.pdf
```

---

## 🔧 Troubleshooting

### Problem: "Command not found"

**Solution:** Install a PDF converter (see Installation section)

### Problem: "Permission denied"

**Solution:** Make scripts executable:
```bash
chmod +x convert_receipts_to_pdf.py
chmod +x convert_single_receipt.sh
```

### Problem: "No receipts found"

**Solution:** 
1. Make sure you're in the project directory
2. Generate some receipts first by making bookings
3. Check if `receipts/` folder exists

### Problem: PDF looks different from HTML

**Solution:** 
- Use browser method for pixel-perfect conversion
- Or adjust wkhtmltopdf margins/settings

### Problem: Python script doesn't run

**Solution:**
```bash
# Make sure Python 3 is installed
python3 --version

# Run with full path
python3 /full/path/to/convert_receipts_to_pdf.py
```

---

## 💡 Tips & Best Practices

1. **Keep HTML files**: Don't delete HTML after converting - you might want to regenerate PDFs with different settings

2. **Organize by date**: Consider adding dates to filenames:
   ```
   car_rental_1_2026-01-05.pdf
   ```

3. **Batch convert regularly**: Run the Python script after generating multiple receipts

4. **Check PDF quality**: Open a few PDFs to verify they look good before deleting HTMLs

5. **Backup important receipts**: Keep both HTML and PDF versions for important bookings

---

## 📊 Comparison

| Method | Speed | Quality | Ease | Installation |
|--------|-------|---------|------|--------------|
| Python Script | ⚡⚡⚡ Fast | ⭐⭐⭐ Good | 🟢 Easy | Required |
| Bash Script | ⚡⚡ Medium | ⭐⭐⭐ Good | 🟢 Easy | Required |
| Browser | ⚡ Slow | ⭐⭐⭐⭐ Best | 🟢 Easy | None |

**Recommendation:**
- **For multiple receipts**: Use Python script
- **For one receipt**: Use Bash script or browser
- **Best quality**: Use browser method

---

## 🎓 Advanced Usage

### Convert and Email

Combine with email:
```bash
# Convert receipt
python3 convert_receipts_to_pdf.py

# Email it (macOS)
echo "Your receipt" | mail -s "Receipt" -a receipts/car_rental_1.pdf user@example.com
```

### Automated Workflow

Add to your workflow:
```bash
#!/bin/bash
# After generating receipt in C++ program
python3 convert_receipts_to_pdf.py
echo "✅ Receipts converted to PDF"
```

### Custom Python Script

Modify `convert_receipts_to_pdf.py` to:
- Add watermarks
- Compress PDFs
- Organize by date
- Auto-email receipts

---

## 📝 Summary

**Quick Commands:**
```bash
# Convert all receipts
python3 convert_receipts_to_pdf.py

# Convert one receipt
./convert_single_receipt.sh receipts/car_rental_1.html

# Manual (browser)
open receipts/car_rental_1.html
# Then Cmd+P → Save as PDF
```

**Files Created:**
- `convert_receipts_to_pdf.py` - Batch converter
- `convert_single_receipt.sh` - Single file converter
- `PDF_CONVERSION_GUIDE.md` - This guide

---

**Need help?** Check the troubleshooting section or use the browser method! 🎉
