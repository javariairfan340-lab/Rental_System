# Compiler
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -I./include/modules -I./include/utils -I./src

# Directories
SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/modules/car_rental.cpp \
          $(SRC_DIR)/modules/air_ticketing.cpp \
          $(SRC_DIR)/modules/bus_reservation.cpp \
          $(SRC_DIR)/modules/train_reservation.cpp \
          $(SRC_DIR)/modules/cinema_tickets.cpp \
          $(SRC_DIR)/utils/utils.cpp \
          $(SRC_DIR)/utils/receipt_generator.cpp

# Output
TARGET = $(BUILD_DIR)/reservation_system

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	@echo "🔨 Compiling Reservation System..."
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "✅ Compilation successful!"
	@echo "📦 Executable created: $(TARGET)"
	@echo ""
	@echo "To run the program, execute:"
	@echo "  $(TARGET)"

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build artifacts..."
	@rm -f $(BUILD_DIR)/reservation_system
	@echo "✅ Clean complete!"

# Run the program
run: $(TARGET)
	@$(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make run      - Build and run the program"
	@echo "  make help     - Show this help message"

.PHONY: all clean run help
