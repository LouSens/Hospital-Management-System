#pragma once
#include "MedicalService.h"
#include <string>

/**
 * AppointmentRecord.h
 * Represents a single appointment between a patient and a medical service.
 * Demonstrates: COMPOSITION — AppointmentRecord HAS-A MedicalService
 *
 * Billing Modifiers:
 *   "Cancelled"  -> 0.00
 *   "Scheduled"  -> baseFee x 1.0
 *   "Completed"  -> baseFee x 0.8 (insured discount)
 *   "Emergency"  -> baseFee x 1.5 (surcharge)
 */
class AppointmentRecord {
private:
    MedicalService service;        // COMPOSITION: has-a relationship
    std::string assignedDoctorId;
    std::string assignedDoctorName;
    std::string appointmentStatus; // "Scheduled", "Completed", "Cancelled", "Emergency"
    std::string billingModifier;   // "Standard", "Insured", "Emergency"

public:
    // Constructor: creates an appointment with default status "Scheduled"
    AppointmentRecord(const MedicalService& svc,
                      const std::string& doctorId = "None",
                      const std::string& doctorName = "None",
                      const std::string& status = "Scheduled",
                      const std::string& modifier = "Standard");

    // Getters
    std::string getServiceCode() const;
    std::string getServiceName() const;
    std::string getDoctorId() const;
    std::string getDoctorName() const;
    std::string getAppointmentStatus() const;
    std::string getBillingModifier() const;
    MedicalService getService() const;

    // Setters
    void setStatus(const std::string& status);
    void setBillingModifier(const std::string& modifier);

    // Calculate billing based on status and modifier
    double calculateBillingAmount() const;

    // Display full appointment detail
    void displayAppointment() const;

    // Serialise for file storage
    std::string toFileString() const;
};
