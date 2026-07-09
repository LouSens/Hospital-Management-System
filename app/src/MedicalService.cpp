#include "../include/MedicalService.h"
#include <stdexcept>

// Constructor 1: Full parameters
MedicalService::MedicalService(const std::string& code,
                               const std::string& name,
                               double fee)
    : serviceCode(code), serviceName(name), baseFee(fee) {
    if (fee < 0)
        throw std::invalid_argument("Base fee cannot be negative.");
}

// Constructor 2: Default fee = 50.0 (overloaded)
MedicalService::MedicalService(const std::string& code,
                               const std::string& name)
    : serviceCode(code), serviceName(name), baseFee(50.0) {}

// Default constructor
MedicalService::MedicalService()
    : serviceCode(""), serviceName(""), baseFee(50.0) {}

std::string MedicalService::getServiceCode() const { return serviceCode; }
std::string MedicalService::getServiceName() const { return serviceName; }
double MedicalService::getBaseFee() const { return baseFee; }

void MedicalService::setBaseFee(double fee) {
    if (fee < 0) throw std::invalid_argument("Fee cannot be negative.");
    baseFee = fee;
}

void MedicalService::displayService() const {
    std::cout << std::left
              << "  Code: " << std::setw(12) << serviceCode
              << "| Name: " << std::setw(25) << serviceName
              << "| Base Fee: RM " << std::fixed
              << std::setprecision(2) << baseFee << std::endl;
}

std::string MedicalService::toFileString() const {
    return serviceCode + "|" + serviceName + "|" + std::to_string(baseFee);
}
