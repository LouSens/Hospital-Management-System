#include "../include/Patient.h"
#include <iostream>
#include <iomanip>
#include <algorithm> // std::find_if

int Patient::patientCount = 0;

Patient::Patient(const std::string& id,
                 const std::string& name,
                 const std::string& insurance)
    : Person(id, name), insuranceProvider(insurance) {
    patientCount++;
}

Patient::~Patient() {
    patientCount--;
}

void Patient::displayRole() const {
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  [PATIENT] ID: " << id
              << "  |  Name: " << name << std::endl;
    std::cout << "  Insurance: " << insuranceProvider
              << "  |  Appointments: " << appointments.size() << std::endl;
    if (!appointments.empty()) {
        std::cout << "  Appointment Records:" << std::endl;
        for (const auto& appt : appointments) {
            appt.displayAppointment();
        }
        std::cout << "  Total Expenses: RM " << std::fixed
                  << std::setprecision(2)
                  << calculateTotalMedicalExpenses() << std::endl;
    }
}

std::string Patient::getRoleType() const { return "Patient"; }

std::string Patient::getInsuranceProvider() const { return insuranceProvider; }

const std::vector<AppointmentRecord>& Patient::getAppointments() const {
    return appointments;
}

void Patient::scheduleAppointment(const MedicalService& service) {
    AppointmentRecord record(service); // Default status: "Scheduled"
    appointments.push_back(record);
    std::cout << "[OK] Appointment scheduled: "
              << service.getServiceCode() << " -- "
              << service.getServiceName() << std::endl;
}

bool Patient::setAppointmentStatus(const std::string& serviceCode,
                                   const std::string& status,
                                   const std::string& modifier) {
    auto it = std::find_if(appointments.begin(), appointments.end(),
        [&serviceCode](const AppointmentRecord& r) {
            return r.getServiceCode() == serviceCode;
        });

    if (it == appointments.end()) {
        return false; // Not found
    }
    it->setStatus(status);
    it->setBillingModifier(modifier);
    return true;
}

double Patient::calculateTotalMedicalExpenses() const {
    double total = 0.0;
    for (const auto& appt : appointments) {
        total += appt.calculateBillingAmount();
    }
    return total;
}

int Patient::getPatientCount() { return patientCount; }

void Patient::addAppointmentRecord(const AppointmentRecord& record) {
    appointments.push_back(record);
}

std::string Patient::toFileString() const {
    return "Patient|" + id + "|" + name + "|" + insuranceProvider;
}
