#include "../include/AppointmentRecord.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

AppointmentRecord::AppointmentRecord(const MedicalService& svc,
                                     const std::string& doctorId,
                                     const std::string& doctorName,
                                     const std::string& status,
                                     const std::string& modifier)
    : service(svc), assignedDoctorId(doctorId), assignedDoctorName(doctorName), appointmentStatus(status), billingModifier(modifier) {}

std::string AppointmentRecord::getServiceCode() const {
    return service.getServiceCode();
}

std::string AppointmentRecord::getServiceName() const {
    return service.getServiceName();
}

std::string AppointmentRecord::getDoctorId() const {
    return assignedDoctorId;
}

std::string AppointmentRecord::getDoctorName() const {
    return assignedDoctorName;
}

std::string AppointmentRecord::getAppointmentStatus() const {
    return appointmentStatus;
}

std::string AppointmentRecord::getBillingModifier() const {
    return billingModifier;
}

MedicalService AppointmentRecord::getService() const { return service; }

void AppointmentRecord::setStatus(const std::string& status) {
    if (status != "Scheduled" && status != "Completed" &&
        status != "Cancelled" && status != "Emergency") {
        throw std::invalid_argument(
            "Invalid status. Use: Scheduled, Completed, Cancelled, Emergency.");
    }
    appointmentStatus = status;
}

void AppointmentRecord::setBillingModifier(const std::string& modifier) {
    if (modifier != "Standard" && modifier != "Insured" && modifier != "Emergency") {
        throw std::invalid_argument(
            "Invalid modifier. Use: Standard, Insured, Emergency.");
    }
    billingModifier = modifier;
}

double AppointmentRecord::calculateBillingAmount() const {
    double base = service.getBaseFee();
    if (appointmentStatus == "Cancelled")  return 0.0;
    if (billingModifier == "Insured")      return base * 0.8;  // 20% discount
    if (billingModifier == "Emergency" ||
        appointmentStatus == "Emergency")  return base * 1.5;  // 50% surcharge
    return base * 1.0; // Standard rate
}

void AppointmentRecord::displayAppointment() const {
    std::cout << "    [" << appointmentStatus << "] "
              << service.getServiceCode() << " -- "
              << service.getServiceName()
              << " | Dr: " << assignedDoctorName << " (" << assignedDoctorId << ")"
              << " | Modifier: " << billingModifier
              << " | Bill: RM " << std::fixed
              << std::setprecision(2) << calculateBillingAmount()
              << std::endl;
}

std::string AppointmentRecord::toFileString() const {
    return service.toFileString() + "|" + appointmentStatus + "|" + billingModifier + "|" + assignedDoctorId + "|" + assignedDoctorName;
}
