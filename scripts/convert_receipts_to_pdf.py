#!/usr/bin/python3
"""
HTML to PDF Converter for Reservation System Receipts
Converts all HTML receipts in the receipts/ directory to PDF format
"""

import os
import sys
import subprocess
from pathlib import Path

def check_dependencies():
    """Check if required tools are installed"""
    print("🔍 Checking dependencies...")
    
    # Check for wkhtmltopdf
    try:
        result = subprocess.run(['which', 'wkhtmltopdf'], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            print("✅ wkhtmltopdf found:", result.stdout.strip())
            return 'wkhtmltopdf'
    except:
        pass
    
    # Check for weasyprint
    try:
        result = subprocess.run(['which', 'weasyprint'], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            print("✅ weasyprint found:", result.stdout.strip())
            return 'weasyprint'
    except:
        pass
    
    print("\n❌ No PDF converter found!")
    print("\nPlease install one of the following:")
    print("\n📦 Option 1: wkhtmltopdf (Recommended)")
    print("   macOS:  brew install wkhtmltopdf")
    print("   Linux:  sudo apt-get install wkhtmltopdf")
    print("\n📦 Option 2: weasyprint")
    print("   pip3 install weasyprint")
    print("\n📦 Option 3: Use browser (Manual)")
    print("   Open HTML files in browser and print to PDF")
    
    return None

def convert_with_wkhtmltopdf(html_file, pdf_file):
    """Convert HTML to PDF using wkhtmltopdf"""
    try:
        subprocess.run([
            'wkhtmltopdf',
            '--enable-local-file-access',
            '--page-size', 'Letter',
            '--margin-top', '10mm',
            '--margin-bottom', '10mm',
            '--margin-left', '10mm',
            '--margin-right', '10mm',
            html_file,
            pdf_file
        ], check=True, capture_output=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"   ❌ Error: {e.stderr.decode()}")
        return False

def convert_with_weasyprint(html_file, pdf_file):
    """Convert HTML to PDF using weasyprint"""
    try:
        subprocess.run([
            'weasyprint',
            html_file,
            pdf_file
        ], check=True, capture_output=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"   ❌ Error: {e.stderr.decode()}")
        return False

def convert_receipts(converter_tool):
    """Convert all HTML receipts to PDF"""
    receipts_dir = Path('receipts')
    
    if not receipts_dir.exists():
        print("❌ Receipts directory not found!")
        print("   Make sure you're running this from the project directory.")
        return
    
    # Find all HTML files
    html_files = list(receipts_dir.glob('*.html'))
    
    if not html_files:
        print("📭 No HTML receipts found in receipts/ directory")
        return
    
    print(f"\n📄 Found {len(html_files)} HTML receipt(s)")
    print("🔄 Converting to PDF...\n")
    
    converted = 0
    failed = 0
    
    for html_file in html_files:
        pdf_file = html_file.with_suffix('.pdf')
        
        print(f"   Converting: {html_file.name} → {pdf_file.name}")
        
        if converter_tool == 'wkhtmltopdf':
            success = convert_with_wkhtmltopdf(str(html_file), str(pdf_file))
        else:  # weasyprint
            success = convert_with_weasyprint(str(html_file), str(pdf_file))
        
        if success:
            print(f"   ✅ Created: {pdf_file.name}")
            converted += 1
        else:
            failed += 1
    
    print(f"\n{'='*60}")
    print(f"✅ Successfully converted: {converted}")
    if failed > 0:
        print(f"❌ Failed: {failed}")
    print(f"{'='*60}")
    
    if converted > 0:
        print(f"\n📁 PDF receipts saved in: {receipts_dir.absolute()}")

def main():
    print("="*60)
    print("  HTML to PDF Converter - Reservation System")
    print("="*60)
    
    # Check dependencies
    converter = check_dependencies()
    
    if not converter:
        sys.exit(1)
    
    # Convert receipts
    convert_receipts(converter)
    
    print("\n✨ Done!\n")

if __name__ == "__main__":
    main()
