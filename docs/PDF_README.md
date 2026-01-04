# PDF Conversion Tools - Quick Reference

## 🎯 Convert HTML Receipts to PDF

### Option 1: Batch Convert (All Receipts)
```bash
python3 convert_receipts_to_pdf.py
```

### Option 2: Single Receipt
```bash
./convert_single_receipt.sh receipts/car_rental_1.html
```

### Option 3: Browser (No Installation)
```bash
open receipts/car_rental_1.html
# Then: Cmd+P → Save as PDF
```

---

## 📦 Installation (One-Time Setup)

### macOS (Recommended):
```bash
brew install wkhtmltopdf
```

### Alternative (Python):
```bash
pip3 install weasyprint
```

---

## ✨ Features

✅ **Batch processing** - Convert all receipts at once
✅ **Auto-detection** - Finds available PDF converter
✅ **Progress tracking** - See conversion status
✅ **Error handling** - Clear, helpful messages
✅ **Auto-open** - Opens PDF after conversion (single mode)

---

## 📁 Files

- `convert_receipts_to_pdf.py` - Python batch converter
- `convert_single_receipt.sh` - Bash single file converter  
- `PDF_CONVERSION_GUIDE.md` - Complete documentation

---

## 🚀 Quick Start

1. **Install converter** (one-time):
   ```bash
   brew install wkhtmltopdf
   ```

2. **Generate receipts** in your C++ program

3. **Convert to PDF**:
   ```bash
   python3 convert_receipts_to_pdf.py
   ```

4. **Find PDFs** in `receipts/` folder!

---

**For detailed instructions, see:** `PDF_CONVERSION_GUIDE.md`
