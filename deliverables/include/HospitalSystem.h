#pragma once
#include "Patient.h"
#include "Doctor.h"
#include "MedicalService.h"
#include "FileManager.h"
#include <vector>
#include <string>

/**
 * HospitalSystem.h
 * Central controller. Aggregates all entities.
 * Demonstrates:
 *   - vector<Person*> -- polymorphic container
 *   - dynamic_cast for safe downcasting
 */
class HospitalSystem {
private:
    std::vector<Person*> users;             // Polymorphic container
    std::vector<MedicalService> services;   // Service catalog

    // Helper: find patient by ID
    Patient* findPatient(const std::string& id);

    // Helper: find service by code
    const MedicalService* findService(const std::string& code) const;

public:
    HospitalSystem();
    ~HospitalSystem(); // Deletes all Person* to prevent memory leak

    // CRUD operations
    void addPatient(const std::string& id,
                    const std::string& name,
                    const std::string& insurance);

    void addDoctor(const std::string& id,
                   const std::string& name,
                   const std::string& specialization,
                   const std::string& clinicCode = "UNASSIGNED");

    void addMedicalService(const MedicalService& service);

    void scheduleAppointment(const std::string& patientId,
                             const std::string& serviceCode);

    void setAppointmentStatus(const std::string& patientId,
                              const std::string& serviceCode,
                              const std::string& status,
                              const std::string& modifier);

    // Display operations
    void viewAllUsers() const;
    void viewServicesCatalog() const;
    void viewPatientExpenses(const std::string& patientId) const;
    void viewSystemStats() const;      // Uses static counts

    // Persistence
    void saveAllData() const;
    void loadAllData();
};
