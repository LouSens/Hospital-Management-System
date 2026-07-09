#pragma once
#include "Person.h"
#include "AppointmentRecord.h"
#include <vector>
#include <string>

/**
 * Patient.h
 * Inherits from Person (ABC).
 * Demonstrates:
 *   - Inheritance: IS-A Person
 *   - Override of pure virtual displayRole()
 *   - STL vector for appointments collection
 */
class Patient : public Person {
private:
    std::string insuranceProvider;
    std::vector<AppointmentRecord> appointments; // STL collection
    static int patientCount;

public:
    // Constructor
    Patient(const std::string& id,
            const std::string& name,
            const std::string& insurance);

    // Destructor
    ~Patient() override;

    // Override pure virtual
    void displayRole() const override;

    // Return role type string
    std::string getRoleType() const override;

    // Getters
    std::string getInsuranceProvider() const;
    const std::vector<AppointmentRecord>& getAppointments() const;

    // Appointment operations
    void scheduleAppointment(const MedicalService& service);
    bool setAppointmentStatus(const std::string& serviceCode,
                              const std::string& status,
                              const std::string& modifier = "Standard");

    // Billing
    double calculateTotalMedicalExpenses() const;

    // Static
    static int getPatientCount();

    // Direct record injection (for file loader)
    void addAppointmentRecord(const AppointmentRecord& record);

    // File serialisation
    std::string toFileString() const;
};
