#include "../include/Doctor.h"
#include <iostream>

int Doctor::doctorCount = 0;

Doctor::Doctor(const std::string& id,
               const std::string& name,
               const std::string& specialization,
               const std::string& clinicCode)
    : Person(id, name),
      specializationDepartment(specialization),
      assignedClinicCode(clinicCode) {
    doctorCount++;
}

Doctor::~Doctor() {
    doctorCount--;
}

void Doctor::displayRole() const {
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  [DOCTOR]  ID: " << id
              << "  |  Name: " << name << std::endl;
    std::cout << "  Specialization: " << specializationDepartment
              << "  |  Clinic: " << assignedClinicCode << std::endl;
}

std::string Doctor::getRoleType() const { return "Doctor"; }

std::string Doctor::getSpecialization() const {
    return specializationDepartment;
}

std::string Doctor::getClinicCode() const { return assignedClinicCode; }

void Doctor::assignToClinic(const std::string& code) {
    assignedClinicCode = code;
    std::cout << "[OK] Doctor " << name
              << " assigned to clinic: " << code << std::endl;
}

int Doctor::getDoctorCount() { return doctorCount; }

std::string Doctor::toFileString() const {
    return id + "|" + name + "|" + specializationDepartment + "|" + assignedClinicCode;
}
