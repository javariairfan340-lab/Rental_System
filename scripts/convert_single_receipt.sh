#!/bin/bash
# Convert a single HTML receipt to PDF
# Usage: ./convert_single_receipt.sh receipts/car_rental_1.html

if [ $# -eq 0 ]; then
    echo "❌ Error: No HTML file specified"
    echo ""
    echo "Usage: $0 <html_file>"
    echo "Example: $0 receipts/car_rental_1.html"
    exit 1
fi

HTML_FILE="$1"

if [ ! -f "$HTML_FILE" ]; then
    echo "❌ Error: File not found: $HTML_FILE"
    exit 1
fi

# Get the PDF filename (same name, different extension)
PDF_FILE="${HTML_FILE%.html}.pdf"

echo "🔄 Converting HTML to PDF..."
echo "   Input:  $HTML_FILE"
echo "   Output: $PDF_FILE"
echo ""

# Try wkhtmltopdf first
if command -v wkhtmltopdf &> /dev/null; then
    echo "📦 Using wkhtmltopdf..."
    wkhtmltopdf \
        --enable-local-file-access \
        --page-size Letter \
        --margin-top 10mm \
        --margin-bottom 10mm \
        --margin-left 10mm \
        --margin-right 10mm \
        "$HTML_FILE" "$PDF_FILE" 2>/dev/null
    
    if [ $? -eq 0 ]; then
        echo "✅ PDF created successfully: $PDF_FILE"
        echo ""
        echo "📂 Opening PDF..."
        open "$PDF_FILE" 2>/dev/null || xdg-open "$PDF_FILE" 2>/dev/null
        exit 0
    fi
fi

# Try weasyprint
if command -v weasyprint &> /dev/null; then
    echo "📦 Using weasyprint..."
    weasyprint "$HTML_FILE" "$PDF_FILE" 2>/dev/null
    
    if [ $? -eq 0 ]; then
        echo "✅ PDF created successfully: $PDF_FILE"
        echo ""
        echo "📂 Opening PDF..."
        open "$PDF_FILE" 2>/dev/null || xdg-open "$PDF_FILE" 2>/dev/null
        exit 0
    fi
fi

# No converter found
echo "❌ No PDF converter found!"
echo ""
echo "Please install one of the following:"
echo ""
echo "📦 Option 1: wkhtmltopdf (Recommended)"
echo "   macOS:  brew install wkhtmltopdf"
echo "   Linux:  sudo apt-get install wkhtmltopdf"
echo ""
echo "📦 Option 2: weasyprint"
echo "   pip3 install weasyprint"
echo ""
echo "📦 Option 3: Use browser (Manual)"
echo "   1. Open $HTML_FILE in your browser"
echo "   2. Press Cmd+P (Mac) or Ctrl+P (Windows/Linux)"
echo "   3. Select 'Save as PDF'"
echo ""

exit 1
