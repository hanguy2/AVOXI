# Makefile for httpsrv project

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -fPIC
INCLUDE_DIRS := -I. -I./httplib -I./json

# Libraries
LIBS := -lmaxminddb -lpthread
LDFLAGS := $(LIBS)

# Output executable
TARGET := httpsrv

# Source files
SOURCES := httpsrv.cc simple_logger.cc geo_ip_database.cc validate_country_ip.cc
HEADERS := simple_logger.h geo_ip_database.h validate_country_ip.h ip_validator.h countries_list.h

# Object files
OBJECTS := $(SOURCES:.cc=.o)

# Dependency files
DEPS := $(SOURCES:.cc=.d)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compile source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
	@echo "Clean complete"

# Clean all including executable
distclean: clean
	@echo "Distclean complete"

# Build and run
run: $(TARGET)
	./$(TARGET)

# Display help
help:
	@echo "Available targets:"
	@echo "  all       - Build the httpsrv executable (default)"
	@echo "  clean     - Remove object files and dependency files"
	@echo "  distclean - Remove object files, dependency files, and executable"
	@echo "  run       - Build and run the httpsrv executable"
	@echo "  help      - Display this help message"

# Phony targets
.PHONY: all clean distclean run help
