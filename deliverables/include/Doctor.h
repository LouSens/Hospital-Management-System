#pragma once
#include "Person.h"
#include <string>

/**
 * Doctor.h
 * Inherits from Person (ABC).
 * Demonstrates:
 *   - Inheritance: IS-A Person
 *   - Override of pure virtual displayRole()
 */
class Doctor : public Person {
private:
    std::string specializationDepartment;
    std::string assignedClinicCode;
    static int doctorCount;

public:
    Doctor(const std::string& id,
           const std::string& name,
           const std::string& specialization,
           const std::string& clinicCode = "UNASSIGNED");

    ~Doctor() override;

    // Override pure virtual
    void displayRole() const override;
    std::string getRoleType() const override;

    // Getters
    std::string getSpecialization() const;
    std::string getClinicCode() const;

    // Assign doctor to a clinic
    void assignToClinic(const std::string& code);

    // Static
    static int getDoctorCount();

    // File serialisation
    std::string toFileString() const;
};
