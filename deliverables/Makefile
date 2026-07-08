# Makefile
# Hospital Patient & Appointment Management System
# CST209 -- Object-Oriented Programming C++

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRCS = src/Person.cpp \
       src/MedicalService.cpp \
       src/AppointmentRecord.cpp \
       src/Patient.cpp \
       src/Doctor.cpp \
       src/FileManager.cpp \
       src/HospitalSystem.cpp \
       src/main.cpp

TARGET = hospital_system

# Default rule: build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Create data directory if it doesn't exist, then build
setup:
	mkdir -p data
	$(MAKE) $(TARGET)

# Remove compiled binary
clean:
	rm -f $(TARGET)

.PHONY: clean setup
