#include "utils.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <cstdlib>

using namespace std;

// Clear screen function
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Print colored header
void printHeader(const string& title) {
    printLine('=');
    cout << Color::BOLD << Color::CYAN << "  " << title << Color::RESET << endl;
    printLine('=');
}

// Print success message
void printSuccess(const string& message) {
    cout << Color::GREEN << "✓ " << message << Color::RESET << endl;
}

// Print error message
void printError(const string& message) {
    cout << Color::RED << "✗ " << message << Color::RESET << endl;
}

// Print info message
void printInfo(const string& message) {
    cout << Color::YELLOW << "ℹ " << message << Color::RESET << endl;
}

// Pause screen and wait for user input
void pauseScreen() {
    cout << Color::MAGENTA << "\nPress Enter to continue..." << Color::RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Get current date as string
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string day = to_string(ltm->tm_mday);
    string month = to_string(1 + ltm->tm_mon);
    string year = to_string(1900 + ltm->tm_year);
    
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;
    
    return day + "/" + month + "/" + year;
}

// Get current time as string
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    
    if (hour.length() == 1) hour = "0" + hour;
    if (min.length() == 1) min = "0" + min;
    
    return hour + ":" + min;
}

// Get validated integer input with range checking
int getValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << Color::CYAN << prompt << Color::RESET;
        
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            } else {
                printError("Please enter a value between " + to_string(min) + " and " + to_string(max));
            }
        } else {
            printError("Invalid input! Please enter a number.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Get validated double input with range checking
double getValidatedDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << Color::CYAN << prompt << Color::RESET;
        
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            } else {
                printError("Please enter a value between " + to_string(min) + " and " + to_string(max));
            }
        } else {
            printError("Invalid input! Please enter a number.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Get validated string input (non-empty)
string getValidatedString(const string& prompt) {
    string value;
    while (true) {
        cout << Color::CYAN << prompt << Color::RESET;
        getline(cin, value);
        
        if (!value.empty()) {
            return value;
        } else {
            printError("Input cannot be empty!");
        }
    }
}

// Print a line of characters
void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    cout << endl;
}

// Print separator
void printSeparator() {
    cout << Color::BLUE;
    printLine('-', 80);
    cout << Color::RESET;
}

// Print warning message
void printWarning(const string& message) {
    cout << Color::YELLOW << "⚠ " << message << Color::RESET << endl;
}

// Convert HTML receipt to PDF using external script
void convertReceiptToPDF(const string& htmlFilePath) {
    cout << "\n" << Color::CYAN << "Converting to PDF..." << Color::RESET << endl;
    
    // Build the command to run the conversion script
    string command = "./scripts/convert_single_receipt.sh \"" + htmlFilePath + "\" 2>&1";
    
    // Execute the command
    int result = system(command.c_str());
    
    if (result == 0) {
        printSuccess("PDF created successfully!");
        
        // Extract PDF filename
        string pdfPath = htmlFilePath;
        size_t pos = pdfPath.find(".html");
        if (pos != string::npos) {
            pdfPath.replace(pos, 5, ".pdf");
        }
        
        printInfo("PDF saved as: " + pdfPath);
        
        // Ask if user wants to open the PDF
        cout << Color::CYAN << "Open PDF now? (y/n): " << Color::RESET;
        char choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 'y' || choice == 'Y') {
            string openCmd = "open \"" + pdfPath + "\" 2>/dev/null || xdg-open \"" + pdfPath + "\" 2>/dev/null";
            system(openCmd.c_str());
        }
    } else {
        printWarning("PDF conversion requires wkhtmltopdf or weasyprint");
        printInfo("Install with: brew install wkhtmltopdf");
        printInfo("Or use browser: open " + htmlFilePath);
    }
}
