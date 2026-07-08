#pragma once
#include <string>
#include <iostream>
#include <iomanip>

/**
 * MedicalService.h
 * Represents a medical service or clinic offering in the hospital.
 * Demonstrates: Constructor Overloading (Compile-time Polymorphism)
 */
class MedicalService {
private:
    std::string serviceCode;
    std::string serviceName;
    double baseFee;

public:
    // Constructor 1: All parameters provided
    MedicalService(const std::string& code, const std::string& name, double fee);

    // Constructor 2: Default baseFee = 50.0 (overloaded constructor)
    MedicalService(const std::string& code, const std::string& name);

    // Default constructor for file loading
    MedicalService();

    // Getters
    std::string getServiceCode() const;
    std::string getServiceName() const;
    double getBaseFee() const;

    // Setters
    void setBaseFee(double fee);

    // Display service details
    void displayService() const;

    // Serialise to string for file storage
    std::string toFileString() const;
};
