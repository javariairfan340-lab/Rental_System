#!/bin/bash
# Simple receipt viewer - opens HTML in browser for manual PDF conversion
# Usage: ./view_receipt.sh receipts/car_rental_1.html

if [ $# -eq 0 ]; then
    echo "Usage: $0 <html_file>"
    echo "Example: $0 receipts/car_rental_1.html"
    exit 1
fi

HTML_FILE="$1"

if [ ! -f "$HTML_FILE" ]; then
    echo "❌ Error: File not found: $HTML_FILE"
    exit 1
fi

echo "📄 Opening receipt in browser..."
echo "   File: $HTML_FILE"
echo ""
echo "To save as PDF:"
echo "   1. Press Cmd+P (Mac) or Ctrl+P (Windows/Linux)"
echo "   2. Select 'Save as PDF' as destination"
echo "   3. Click 'Save'"
echo ""

# Open in default browser
open "$HTML_FILE" 2>/dev/null || xdg-open "$HTML_FILE" 2>/dev/null || start "$HTML_FILE" 2>/dev/null

if [ $? -eq 0 ]; then
    echo "✅ Receipt opened in browser"
else
    echo "❌ Could not open browser"
    echo "   Please open manually: $HTML_FILE"
fi
