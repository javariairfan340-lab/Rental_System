#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

// ANSI Color Codes for colorful terminal output
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_RED = "\033[41m";
}

// Utility function declarations
void clearScreen();
void printHeader(const std::string& title);
void printSuccess(const std::string& message);
void printError(const std::string& message);
void printInfo(const std::string& message);
void pauseScreen();
std::string getCurrentDate();
std::string getCurrentTime();
int getValidatedInt(const std::string& prompt, int min, int max);
double getValidatedDouble(const std::string& prompt, double min, double max);
std::string getValidatedString(const std::string& prompt);
void printLine(char ch = '=', int length = 80);
void printSeparator();
void printWarning(const std::string& message);

// PDF conversion function
void convertReceiptToPDF(const std::string& htmlFilePath);

#endif
