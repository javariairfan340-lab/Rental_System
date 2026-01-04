#!/bin/bash

# Compilation script for Reservation System
# Updated for new directory structure

echo "🔨 Compiling Reservation System..."

# Create build directory if it doesn't exist
mkdir -p build

# Compile with clang++
clang++ -std=c++11 -Wall -Wextra \
    -I./include/modules \
    -I./include/utils \
    -I./src \
    src/main.cpp \
    src/modules/car_rental.cpp \
    src/modules/air_ticketing.cpp \
    src/modules/bus_reservation.cpp \
    src/modules/train_reservation.cpp \
    src/modules/cinema_tickets.cpp \
    src/utils/utils.cpp \
    src/utils/receipt_generator.cpp \
    -o build/reservation_system

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "📦 Executable created: build/reservation_system"
    echo ""
    echo "To run the program, execute:"
    echo "  ./build/reservation_system"
else
    echo "❌ Compilation failed!"
    exit 1
fi
